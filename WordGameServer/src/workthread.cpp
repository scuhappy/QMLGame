#include "workthread.h"
#include<QTcpSocket>
#include<QJsonObject>
#include<QJsonDocument>
WorkThread::WorkThread()
{
    m_stop=false;
    m_socket = NULL;
}
void WorkThread::init(QTcpSocket *socket)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(socket->socketDescriptor());
}
void WorkThread::run()
{
    if(!m_socket)
    {
        return;
    }
    while(!m_stop)
    {
        if(m_socket->waitForReadyRead())
        {
            QByteArray buffer =  m_socket->readAll();
            qDebug()<<"Read buffer: "<<buffer;
            DoWork(buffer);
        }
        else{
            QThread::msleep(500);
        }
    }
}
void WorkThread::DoWork(const QByteArray &buffer)
{
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    QJsonObject obj = doc.object();
    MESSAGE_TYPE type = (MESSAGE_TYPE)obj.value("Type").toInt();

    switch (type) {
    case LOGIN:
    {
         qDebug()<<obj.value("name").toString()<<"password  : "<<obj.value("psd").toString();
        Login(obj);
        break;
    }
    default:
        break;
    }
}
void WorkThread::Login(const QJsonObject& msg)
{
    QJsonObject obj;
    obj.insert("Type",GET_LOGIN);
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
    m_socket->write(ary);
    m_socket->waitForBytesWritten();
}
