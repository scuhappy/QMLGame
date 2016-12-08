#include "Server.h"
#include<QDebug>
#include<QTcpSocket>
#include<QJsonDocument>
#include<QJsonObject>
#include<QSqlQuery>
#include<QSqlError>
#include"Types.h"
Server::Server(QObject *parent) : QObject(parent)
{
    m_index=0;
    init();
}
void Server::init()
{
    m_tcpServer = new QTcpServer();
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(NewConnection()));

    //database
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("WordGame");
    m_db.setDatabaseName("UserDB");
    m_db.setUserName("ychen");
    m_db.setPassword("654321");
    bool ok = m_db.open();
    QSqlQuery query;
    if(query.exec("CREATE TABLE Persons"\
               "("\
               "UserName varchar(255),"\
               "Password varchar(255)"\
               ");"))
    {
        qDebug()<<"Create table success!";
    }
    else
    {
        qDebug()<<query.lastError().text();
    }

}
int Server::StartServer()
{
   int ret =  m_tcpServer->listen(QHostAddress::Any,777);
   qDebug()<<"Server is running ,listen port 777";
   return ret;
}
void Server::NewConnection()
{

    QTcpSocket * socket = m_tcpServer->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(DoRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(m_slot_disconnect()));
    qDebug()<<"new connect received IP address : "<<socket->peerAddress().toString()\
           <<" port : "<<socket->localPort();
}
void Server::m_slot_disconnect()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    qDebug()<<"Disconnected IP address : "<<socket->peerAddress().toString()\
           <<" port : "<<socket->localPort();
    socket->deleteLater();
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
    m_index++;
    QJsonObject obj;
    obj.insert("Type",GET_LOGIN);
    obj.insert("Index",m_index);
    QSqlQuery query;
    query.exec("");
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
