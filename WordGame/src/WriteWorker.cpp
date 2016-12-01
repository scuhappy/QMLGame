#include "WriteWorker.h"
#include"Types.h"
WriteWorker::WriteWorker(QObject *parent) :
    QThread(parent)
{
    m_stop = true;
}
void WriteWorker::init(Model* model)
{
    m_socket = new QTcpSocket();
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(DoWork()));
    m_model = model;
}
void WriteWorker::run()
{
    while(!m_socket->isOpen())
    {
        QString host = "127.0.0.1";
        qDebug()<<"Connect to host"<<host;
        m_socket->connectToHost(host,777);
        QThread::msleep(100);
    }
    m_stop=false;
    while(!m_stop)
    {
        if(!m_queue.isEmpty())
        {
            QJsonObject obj = m_queue.dequeue();
            QJsonDocument doc(obj);
            m_socket->write(doc.toJson(QJsonDocument::Compact));
            if( !m_socket->waitForBytesWritten())
            {
                return ;//write error
            }
        }
        else
        {
            QThread::msleep(1000);
        }
    }
}
void WriteWorker::AddMsg(QJsonObject obj)
{
    m_queue.enqueue(obj);
}
void WriteWorker::DoWork()
{
    QByteArray buffer = m_socket->readAll();
    qDebug()<<"Read buffer : "<<buffer;
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
void WriteWorker::GetLogin(const QJsonObject &obj)
{
    m_model->setLogin(obj.value("result").toInt()==1 ? true:false);
}
