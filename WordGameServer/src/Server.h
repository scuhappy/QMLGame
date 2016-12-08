#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include<QTcpServer>
#include<QSqlTableModel>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void init();
    int StartServer();
private:
    QTcpServer* m_tcpServer;
    int m_index;
    QSqlDatabase m_db;
private:
    void SendInitInfo(QTcpSocket* socket);
    void Login(QTcpSocket* socket,const QJsonObject& msg);
signals:

public slots:
    void NewConnection();
    void DoRead();
    void m_slot_disconnect();
};

#endif // SERVER_H
