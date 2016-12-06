#include "Logical.h"
#include<QDebug>
#include<QJsonObject>
#include"Types.h"
Logical::Logical(QObject *parent) :
    QObject(parent)
{
    m_index= 0;
}
int Logical::init(Model* model)
{
    if(model==NULL)
    {
        return -1;
    }
    else
    {
        m_model = model;
        m_writer = new WriteWorker();
        connect(m_writer,SIGNAL(Restart()),this,SLOT(RestartWriter()));
        connect(m_writer,SIGNAL(Stoped()),m_writer,SLOT(start()));//restart the writer when stopped
    }

}
void Logical::sendLogin(QVariant name, QVariant psw)
{
    m_index++;
    QJsonObject obj;
    obj.insert("Index",m_index);
    obj.insert("Type",LOGIN);
    obj.insert("name",name.toString());
    obj.insert("psd",psw.toString());
//    m_writer->AddMsg(obj);
    m_socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

int Logical::StarClient()
{
//    m_writer->init(m_model);
//    m_writer->start();
    m_socket =new QTcpSocket(this);
    m_socket->connectToHost("127.0.0.1",777);
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(DoWork()));
    connect(m_socket,SIGNAL(disconnected()),m_socket,SLOT(deleteLater()));
    return 0;
}
void Logical::DoWork()
{
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
           // GetLogin(obj);
            break;
        }
        default:
            break;
        }
    }

}
void Logical::RestartWriter()
{
    m_writer->StopThread();
}
