#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "singleton.h"

class DataBase : public Singleton<DataBase>
{
    friend class Singleton<DataBase>;
private:
    ///
    /// \brief DataBase Конструктор класса
    ///
    DataBase();
    ///
    /// \brief Game Конструктор копирования класса (удаляется)
    ///
    DataBase(const DataBase& ) = delete;
    ///
    /// \brief operator = Оператор присваивания (удаляется)
    /// \return
    ///
    DataBase& operator = (DataBase &) = delete;
    ///
    /// \brief ~DataBase Деструктор класса, закрытие БД
    ///
    ~DataBase();
    QSqlDatabase db;
    bool db_created();
    void create_db();
public:
    void printTable(const QVector<QMap<QString, QString>>& table);
    QVector<QMap<QString, QString>> db_request(QString request);
    bool does_player_exist(QString login);
    void add_player(QString login);
    void add_victory(QString login);
    void add_loss(QString login);
};

#endif // DATABASE_H
