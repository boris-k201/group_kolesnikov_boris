#include "mytcpserver.h"
#include "game.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    for (QTcpSocket* s : mTcpSocket)
            s->close();
    mTcpServer->close();
    serverStatus=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);
    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        serverStatus=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    if(serverStatus==1){
        socket->write("connected\r\n");
        connect(socket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(socket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
    mTcpSocket.insert(socket->socketDescriptor(), socket);
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    QString data;
    QByteArray response;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readLine());
    }
    if (data.size() > 0 && data.back() == '\n') {
        QStringList datas;
        if (data.contains('\r'))
            datas = data.split("\r\n");
        else
            datas = data.split("\n");
        datas.pop_back();
        for (int i = 0; i < datas.size(); i++) {
            Game::getInstance()->parse(socket->socketDescriptor(), datas[i]);
        }
    }
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->close();
}

void MyTcpServer::writeSocket(int socketCode, QString message) {
    mTcpSocket[socketCode]->write((message+"\r\n").toUtf8());
}

void MyTcpServer::disconnectSocket(int socketCode) {
    mTcpSocket[socketCode]->close();
}
