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

const int number_of_players = 2;

class Game : public Singleton<Game>
{
    friend class Singleton<Game>;
public:
    void parse(int playerCode, QString message);
    void login(int playerCode, QString playerLogin);
    void logout(int playerCode);
    void set_answer(int playerCode, int value);
    void check_for_endgame();
    void stats(int playerCode);
    void syntax_error(int playerCode, QString command);
private:
    Game();
    Game(const Game& ) = delete;
    Game& operator = (Game &) = delete;

    QMap<int, QString> players;
    QMap<int, int> playerAnswers;
};

#endif // GAME_H
