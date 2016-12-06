#include "Server.h"
#include<QDebug>
#include<QTcpSocket>
#include<QJsonDocument>
#include<QJsonObject>
Server::Server(QObject *parent) : QObject(parent)
{
    m_index=0;
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
    connect(socket,SIGNAL(readyRead()),this,SLOT(DoRead()));
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
//    WorkThread* worker = new WorkThread();
//    worker->init(socket);
//    worker->start();
//    m_threadList.append(worker);
}
void Server::DoRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer =  socket->readAll();
    qDebug()<<"read buffer"<<buffer;
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    QJsonObject obj = doc.object();
    MESSAGE_TYPE type = (MESSAGE_TYPE)obj.value("Type").toInt();

    switch (type) {
    case LOGIN:
    {
         qDebug()<<obj.value("name").toString()<<"password  : "<<obj.value("psd").toString();
        Login(socket,obj);
        break;
    }
    default:
        break;
    }
}
void Server::Login(QTcpSocket* socket,const QJsonObject& msg)
{
    for(int i =0;i<10;i++)
    {
    m_index++;
    QJsonObject obj;
    obj.insert("Type",GET_LOGIN);
    obj.insert("Index",m_index);
    if(msg.value("name").toString()=="ychen" && msg.value("psd").toString()=="123")
    {
        obj.insert("result",1);
    }
    else
    {
        obj.insert("result",0);
    }
    QJsonDocument doc(obj);
    QByteArray ary = doc.toJson(QJsonDocument::Compact);
    qDebug()<<"write buffer "<<ary;
    socket->write(ary+'^');
    socket->waitForBytesWritten();
    }
}
