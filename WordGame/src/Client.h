#ifndef CLIENT_H
#define CLIENT_H

#include<QThread>
#include<QTcpSocket>
class Client : public QThread
{
public:
    Client();
    void init();
protected:
    void run();
private:
    QTcpSocket* m_socket;
    bool m_stop;
};

#endif // CLIENT_H
