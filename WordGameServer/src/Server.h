#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include<QTcpServer>
#include"workthread.h"
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void init();
    int StartServer();
private:
    QTcpServer* m_tcpServer;
    QList<WorkThread*> m_threadList;
    int m_index;
private:
    void SendInitInfo(QTcpSocket* socket);
    void Login(QTcpSocket* socket,const QJsonObject& msg);
signals:

public slots:
    void NewConnection();
    void DoRead();
};

#endif // SERVER_H
