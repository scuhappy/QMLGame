#include "Client.h"

Client::Client()
{
    init();
}
void Client::run()
{
    m_socket->connectToHost("127.0.0.1",777);
    if(m_socket->waitForConnected())
    {
        qDebug()<<"connected to 127.0.0.1 !";
    }
    while(!m_stop)
    {
        if(m_socket->waitForReadyRead())
        {
            QByteArray buffer = m_socket->readAll();
            qDebug()<<"read buffer : "<<buffer;
        }
        QThread::msleep(100);
    }
}
void Client::init()
{
    m_stop = false;
    m_socket = new QTcpSocket();

}
