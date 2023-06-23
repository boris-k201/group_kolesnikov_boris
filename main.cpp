#include <QCoreApplication>
#include "mytcpserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer::getInstance();
    DataBase::getInstance()->add_loss("petya");
    DataBase::getInstance()->add_victory("lyosha");
    return a.exec();
}
