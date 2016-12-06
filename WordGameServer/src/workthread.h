#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include<QThread>
#include"Types.h"
class QTcpSocket;
class WorkThread : public QThread
{
public:
    WorkThread();
    void init(QTcpSocket * socket);
    void run();
private:
    void DoWork(const QByteArray& buffer);
    void Login(const QJsonObject& msg);
private:
    QTcpSocket * m_socket;
    QTcpSocket * tmpSocket;
    bool m_stop;
    int m_index;
};

#endif // WORKTHREAD_H
