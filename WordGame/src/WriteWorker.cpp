#include "WriteWorker.h"
#include"Types.h"


#define QT_SOCKET
#ifdef QT_SOCKET
#else
#include<boost/asio.hpp>
boost::asio::io_service service;
boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 777);
boost::asio::ip::tcp::socket sock(service);
#endif
WriteWorker::WriteWorker(QObject *parent) :
    QThread(parent)
{
    m_stop = true;
    m_socket=NULL;
}
void WriteWorker::init(Model* model)
{

    m_model = model;
}
void WriteWorker::run()
{

#ifdef QT_SOCKET
    if(m_socket==NULL)
    {
        m_socket = new QTcpSocket();

    }
    QString host = "127.0.0.1";
    while(true)
    {
        m_socket->connectToHost(host,777);
        if( m_socket->waitForConnected(1000))
        {
            qDebug()<<"connected";
            connect(m_socket,SIGNAL(readyRead()),this,SLOT(DoWork()));
            //connect(m_socket,SIGNAL(disconnected()),this,SLOT(RestartThread()),Qt::UniqueConnection);
            break;
        }
        else
        {
            qDebug()<<"connecting to "<<host;
        }
        QThread::msleep(1000);
    }
    m_stop=false;
    while(!m_stop)
    {
        if(!m_queue.isEmpty())
        {
            QJsonObject obj = m_queue.dequeue();
            QJsonDocument doc(obj);
            qDebug()<<doc.toJson(QJsonDocument::Compact);
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
    emit Stoped();
#else
    sock.connect(ep);
//    sock.write_some(boost::asio::buffer("hello",5));
//    while(true)
//    {
//        char data[512];
//        size_t len = sock.read_some(boost::asio::buffer(data));
//        if ( len > 0)
//            sock.write_some(boost::asio::buffer("ok", 2));
//    }
#endif
}
void WriteWorker::StopThread()
{
    m_stop = true;
}

void WriteWorker::AddMsg(QJsonObject obj)
{
    m_queue.enqueue(obj);
}
void WriteWorker::DoWork()
{
    QByteArray buffer = m_socket->readAll();
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
void WriteWorker::RestartThread()
{
    qDebug()<<"Restart thread";
    emit Restart();
}

void WriteWorker::GetLogin(const QJsonObject &obj)
{
    m_model->setLogin(obj.value("result").toInt()==1 ? true:false);
}
