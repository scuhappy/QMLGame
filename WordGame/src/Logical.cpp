#include "Logical.h"
#include<QDebug>

#include<QThread>
#include"Types.h"
Logical::Logical(QObject *parent) :
    QObject(parent)
{
    m_index= 0;
    m_host = "127.0.0.1";
    m_port = 777;
    num2=0;
    //qRegisterMetaType<QJsonObject>("QJsonObject");
    connect(this,SIGNAL(m_signal_SendMsg(QJsonObject)),this,SLOT(SendMsg(QJsonObject)));
    connect(this,SIGNAL(m_signal_start()),this,SLOT(StarClient()));
}

int Logical::init(Model* model)
{
    if(model==NULL)
    {
        return -1;
    }
    m_model = model;
    return 0;
}
void Logical::sendLogin(QVariant name, QVariant psw)
{
    m_index++;
    QJsonObject obj;
    obj.insert("Index",m_index);
    obj.insert("Type",LOGIN);
    obj.insert("name",name.toString());
    obj.insert("psd",psw.toString());
    emit m_signal_SendMsg(obj);
}
void Logical::SendMsg(QJsonObject obj)
{
    qDebug()<<"send message";
    m_socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

int Logical::StarClient()
{
    qDebug()<<QThread::currentThreadId();
    m_socket =new QTcpSocket();
    m_socket->connectToHost(m_host,m_port);
    while(!m_socket->waitForConnected())
    {
        qDebug()<<"connect to server";
        m_socket->connectToHost(m_host,m_port);
        QThread::msleep(1000);
    }
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(DoWork()));
    connect(m_socket,SIGNAL(disconnected()),m_socket,SLOT(deleteLater()));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(ReConnect()));
    return 0;
}
void Logical::DoWork()
{
    qDebug()<<QThread::currentThreadId();
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer = socket->readAll();
    qDebug()<<"Read buffer : "<<buffer;
    QList<QByteArray> bufList =  buffer.split('^');
    for(int i=0;i<bufList.count()-1;i++)//last is empty
    {
        QJsonDocument doc = QJsonDocument::fromJson(bufList.at(i));
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

}
void Logical::ReConnect()
{
    m_socket->connectToHost(m_host,m_port);
    while(!m_socket->waitForConnected())
    {
        qDebug()<<"reconnect to server";
        m_socket->connectToHost(m_host,m_port);
        QThread::msleep(1000);
    }
}
void Logical::Start()
{
    emit m_signal_start();
}

void Logical::GetLogin(const QJsonObject &obj)
{
    m_model->setLogin(obj.value("result").toInt()==1 ? true:false);
}
