#include "database.h"

bool DataBase::db_created()
{
    return this->db.tables() == QStringList{"STATS"};
}

void DataBase::create_db()
{
    QSqlQuery query(this->db);

    query.exec("CREATE TABLE STATS("
           "login TEXT NOT NULL PRIMARY KEY, "
           "victories INT8 NOT NULL, "
           "losses INT8 NOT NULL "
           ")");
}


DataBase::DataBase()
{
    // Инициализируем базу данных из файла database.sqlite
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("database.sqlite");

    // Выводим ошибки, если они есть, в консоль
    if (!(this->db.open()))
        qDebug()<<db.lastError().text();

    // Если нет таблиц Users, Tasks, UserGroups, то создаем их
    if (!this->db_created())
        this->create_db();
}

DataBase::~DataBase()
{
    // Закрываем базу данных
    db.close();
}

QVector<QMap<QString, QString>> DataBase::db_request(QString request) {
    QSqlQuery query(this->db);
    query.exec(request);            // исполняем запрос

    QVector<QMap<QString, QString>> result; // таблица с запрашиваемыми данными

    if (query.lastError().isValid()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return result;
    }

    QSqlRecord record = query.record();
    QVector<QString> columns;       // хранит столбцы возвращаемой таблицы

    for (int i = 0; i < record.count(); i++) {
        QString columnName = record.fieldName(i);
        columns.append(columnName);
    }

    while (query.next()) {
        QMap<QString, QString> row;
        for (int i = 0; i < columns.count(); i++) {
            // строки таблицы заполняются, каждая строка - хэшмап, ключ - название столбца, значение - то, что в ячейке
            QString columnName = query.record().fieldName(i);
            QString value = query.value(i).toString();
            row.insert(columnName, value);
        }
        result.append(row);
    }
    return result;
}

void DataBase::printTable(const QList<QMap<QString, QString>>& table)
{
    const int columnWidth = 15;

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);

    // выводим заголовки столбцов
    QString header;
    for (auto& column : table.first().keys()) {
        header += QString("| %1 ").arg(column.leftJustified(columnWidth, ' '), Qt::AlignHCenter);
    }
    qDebug().noquote() << header << "|";

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);

    // выводим строки таблицы
    for (auto& row : table) {
        QString rowStr;
        for (auto& value : row.values()) {
            rowStr += QString("| %1 ").arg(value.leftJustified(columnWidth, ' '), Qt::AlignHCenter);
        }
        qDebug().noquote() << rowStr << "|";
    }

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);
}

void DataBase::add_loss(QString login) {
    if (!does_player_exist(login))
        add_player(login);
    QVector<QMap<QString, QString>> result = db_request(QString("UPDATE STATS SET losses += 1 WHERE LOGIN = '%1'").arg(login));
    printTable(result);
}
void DataBase::add_victory(QString login) {
    if (!does_player_exist(login))
        add_player(login);
    QSqlQuery query(this->db);
    query.exec(QString("UPDATE STATS SET victories += 1 WHERE LOGIN = '%1';").arg(login));
}

void DataBase::add_player(QString login) {
    QSqlQuery query(this->db);
    query.exec(QString("INSERT INTO STATS VALUES ('%1', 0, 0);").arg(login));
}

bool DataBase::does_player_exist(QString login) {
    QVector<QMap<QString, QString>> result = db_request(QString("SELECT COUNT(*) FROM STATS WHERE LOGIN = '%1'").arg(login));
    return result[0]["COUNT(*)"] != "0";
}
