#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include "singleton.h"

///
/// \brief The MyTcpServer class Класс, работающий с обменом сообщениями с игроками
///
class MyTcpServer : public QObject, public Singleton<MyTcpServer>
{
    Q_OBJECT
public:
    friend class Singleton<MyTcpServer>;
    ///
    /// \brief writeSocket Отправляет сообщение игроку
    /// \param socketCode socketDescriptor игрока
    /// \param message Сообщение, отправляемое игроку
    ///
    void writeSocket(int socketCode, QString message);
    ///
    /// \brief disconnectSocket Обрывает связь с игроком
    /// \param socketCode socketDescriptor игрока
    ///
    void disconnectSocket(int socketCode);
public slots:
    ///
    /// \brief slotNewConnection Вызывается при подключении игрока к серверу
    ///
    void slotNewConnection();
    ///
    /// \brief slotClientDisconnected Вызывается при отключении игрока от сервера
    ///
    void slotClientDisconnected();
    ///
    /// \brief slotServerRead Вызывается при получении сообщения от игрока
    ///
    void slotServerRead();
private:
    ///
    /// \brief MyTcpServer Деструктор класса
    ///
    ~MyTcpServer();
    ///
    /// \brief MyTcpServer Конструктор класса
    /// \param parent
    ///
    explicit MyTcpServer(QObject *parent = nullptr);
    ///
    /// \brief mTcpServer Поле, общающееся с игроками
    ///
    QTcpServer * mTcpServer;
    ///
    /// \brief mTcpSocket Подключившиеся игроки
    ///
    QMap<int, QTcpSocket*> mTcpSocket;
    ///
    /// \brief serverStatus Состояние сервера
    ///
    int serverStatus;
};
#endif // MYTCPSERVER_H







