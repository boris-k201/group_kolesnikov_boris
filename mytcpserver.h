#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include "singleton.h"

class MyTcpServer : public QObject, public Singleton<MyTcpServer>
{
    Q_OBJECT
public:
    friend class Singleton<MyTcpServer>;
    void writeSocket(int socketCode, QString message);
    void disconnectSocket(int socketCode);
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    ~MyTcpServer();
    explicit MyTcpServer(QObject *parent = nullptr);
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket*> mTcpSocket;
    int serverStatus;
    int currentConnections;
};
#endif // MYTCPSERVER_H







