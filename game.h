#ifndef GAME_H
#define GAME_H

#include <QMap>
#include <QDebug>
#include <QStringList>
#include <QRegularExpression>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "singleton.h"
#include "database.h"

///
/// \brief number_of_players Число игроков
///
const int number_of_players = 2;

///
/// \brief The Game class Основной класс, реализующий логику игры
///
class Game : public Singleton<Game>
{
    friend class Singleton<Game>;
public:
    ///
    /// \brief parse Парсит сообщение от игрока и вызывает соответствующие методы
    /// \param playerCode socketDescriptor игрока
    /// \param message Сообщение, отправленное игроком
    ///
    void parse(int playerCode, QString message);
    ///
    /// \brief login Авторизует игрока в игре
    /// \param playerCode socketDescriptor игрока
    /// \param playerLogin Логин игрока
    ///
    void login(int playerCode, QString playerLogin);
    ///
    /// \brief logout Отключает игрока от игры
    /// \param playerCode socketDescriptor игрока
    ///
    void logout(int playerCode);
    ///
    /// \brief set_answer Устанавливает число игрока. Работает только когда подключилось нужное число игроков
    /// \param playerCode socketDescriptor игрока
    /// \param value Число, выбранное игроком
    ///
    void set_answer(int playerCode, int value);
    ///
    /// \brief check_for_endgame Проверяет, все ли игроки выбрали свое число
    ///
    void check_for_endgame();
    ///
    /// \brief stats Выводит список всех игроков
    /// \param playerCode socketDescriptor игрока
    ///
    void stats(int playerCode);
    ///
    /// \brief syntax_error Вызывается, если игрок ввел неверную комманду
    /// \param playerCode socketDescriptor игрока
    /// \param command Неверно введенная игроком команда
    ///
    void syntax_error(int playerCode, QString command);
private:
    ///
    /// \brief Game Конструктор класса
    ///
    Game();
    ///
    /// \brief Game Конструктор копирования класса (удаляется)
    ///
    Game(const Game& ) = delete;
    ///
    /// \brief operator = Оператор присваивания (удаляется)
    /// \return
    ///
    Game& operator = (Game &) = delete;
    ///
    /// \brief players Список игроков и их имен
    ///
    QMap<int, QString> players;
    ///
    /// \brief playerAnswers Список ответов от игроков
    ///
    QMap<int, int> playerAnswers;
};

#endif // GAME_H
