#include "ReadWorker.h"
#include<QJsonDocument>
#include"Types.h"
#include"Model.h"
ReadWorker::ReadWorker(QObject *parent) :
    QThread(parent)
{
    m_stop = true;
}
void ReadWorker::init(const QTcpSocket *socket,Model* model)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(socket->socketDescriptor());
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(AddReadBuffer()));
    m_model = model;
}
void ReadWorker::run()
{
    m_stop=false;
    while(!m_stop)
    {
        if(!m_readQueque.isEmpty())
        {
            QJsonObject obj = m_readQueque.dequeue();
            DoWork(obj);
        }
//        if(m_socket->waitForReadyRead())
//        {
//            QByteArray buffer = m_socket->readAll();
//            qDebug()<<"read buffer : "<<buffer;
//            DoWork(buffer);
//        }
        QThread::msleep(100);
    }
}
void ReadWorker::AddReadBuffer()
{
    QByteArray buffer = m_socket->readAll();
     qDebug()<<"read buffer : "<<buffer;
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    m_readQueque.enqueue(doc.object());
}

void ReadWorker::DoWork(const QJsonObject &obj)
{
    MESSAGE_TYPE type = (MESSAGE_TYPE)obj.value("Type").toInt();
    switch (type) {
    case GET_LOGIN:
    {
        qDebug()<<obj.value("result").toInt();
        GetLogin(obj);
        break;
    }
    default:
        break;
    }
}

void ReadWorker::DoWork(const QByteArray &buffer)
{
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    QJsonObject obj= doc.object();
    MESSAGE_TYPE type = (MESSAGE_TYPE)obj.value("Type").toInt();
    switch (type) {
    case GET_LOGIN:
    {
        qDebug()<<obj.value("result").toInt();
        GetLogin(obj);
        break;
    }
    default:
        break;
    }
}
void ReadWorker::GetLogin(const QJsonObject &obj)
{
    m_model->setLogin(obj.value("result").toInt()==1 ? true:false);
}
