#include "game.h"
#include "mytcpserver.h"

Game::Game() {
}

void Game::login(int playerCode, QString playerName) {
    if (this->players.size() >= number_of_players) {
        MyTcpServer::getInstance()->writeSocket(playerCode, "error already_"+QString::number(number_of_players)+"_players");
        return;
    }
    MyTcpServer::getInstance()->writeSocket(playerCode, "waiting "+playerName);
    this->players.insert(playerCode, playerName);
    if (this->players.size() >= number_of_players) {
        for (int playerCode : players.keys())
            MyTcpServer::getInstance()->writeSocket(playerCode, "make_move "+playerName);
    }
}

void Game::logout(int playerCode) {
    MyTcpServer::getInstance()->writeSocket(playerCode, "logout");
    this->players.remove(playerCode);
    MyTcpServer::getInstance()->disconnectSocket(playerCode);
}

void Game::set_answer(int playerCode, int value) {
    if (players.size() != number_of_players) {
        MyTcpServer::getInstance()->writeSocket(playerCode, "error not_"+QString::number(number_of_players)+"_players");
        return;
    }
    this->playerAnswers.insert(playerCode, value);
    MyTcpServer::getInstance()->writeSocket(playerCode, "choice_set "+QString::number(value));
    this->check_for_endgame();
}

void Game::stats(int playerCode) {
    QString answer = "["+QString::number(players.size())+"]:\r\n";
    for (QString name : players.values())
        answer += name + " ";
    MyTcpServer::getInstance()->writeSocket(playerCode, answer);
}

void Game::syntax_error(int playerCode, QString command) {
    MyTcpServer::getInstance()->writeSocket(playerCode, "error "+command);
}

void Game::check_for_endgame() {
    if (playerAnswers.size() == number_of_players) {
        QList<int> maxKeys;
        int maxValue = -999999;
        for (int playerCode : playerAnswers.keys()) {
            if (playerAnswers[playerCode] > maxValue) {
                maxKeys.clear();
                maxKeys.append(playerCode);
                maxValue = playerAnswers[playerCode];
            } else if (playerAnswers[playerCode] == maxValue)
                maxKeys.append(playerCode);
        }
        for (int playerCode : players.keys()) {
            if (maxKeys.indexOf(playerCode) != -1)
                MyTcpServer::getInstance()->writeSocket(playerCode, "win");
            else
                MyTcpServer::getInstance()->writeSocket(playerCode, "lost");
            logout(playerCode);
        }
        QString filename = "results.txt";
        QFile file(filename);
        if (file.open(QIODevice::Append)) {
            QTextStream stream(&file);
            stream << QDateTime::currentDateTime().toLocalTime().toString() << ": ";
            for (int playerCode : maxKeys)
                stream << players[playerCode] << " ";
            stream << "\n";
        }
        playerAnswers.clear();
    }
}

void Game::parse(int playerCode, QString message) {
    qDebug() << playerCode << " " << message << "\n";
    QStringList words = message.split("$");
    if (words.size() == 2 & words[0] == "start")
        login(playerCode, words[1]);
    else if (words.size() == 1 && words[0] == "break")
        logout(playerCode);
    else if (words.size() == 1 && words[0] == "stats")
        stats(playerCode);
    else if (words.size() == 2 && words[0] == "choice") {
        QRegularExpression reg("\\d*");
        if (reg.match(words[1]).hasMatch())
            set_answer(playerCode, words[1].toInt());
    } else {
        syntax_error(playerCode, message);
    }
}
