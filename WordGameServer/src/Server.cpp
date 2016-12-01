#include "Server.h"
#include<QDebug>
#include<QTcpSocket>
Server::Server(QObject *parent) : QObject(parent)
{
    init();
}
void Server::init()
{
    m_tcpServer = new QTcpServer();
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(NewConnection()));
}
int Server::StartServer()
{
   int ret =  m_tcpServer->listen(QHostAddress::Any,777);
   qDebug()<<"Server is running ,listen port 777";
   return ret;
}
void Server::NewConnection()
{
    qDebug()<<"new connect received";
    QTcpSocket * socket = m_tcpServer->nextPendingConnection();
    WorkThread* worker = new WorkThread();
    worker->init(socket);
    worker->start();
    m_threadList.append(worker);
}
void Server::DoRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer =  socket->readAll();
    qDebug()<<"read buffer"<<buffer;
}
void Server::SendInitInfo(QTcpSocket* socket)
{
    QByteArray message;
    message="please input user info";
    socket->write(message);
}
