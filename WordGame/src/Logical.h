#ifndef LOGICAL_H
#define LOGICAL_H

#include <QObject>
#include<QTcpSocket>
#include<QJsonObject>
#include<QJsonDocument>
#include"Model.h"
class Logical : public QObject
{
    Q_OBJECT
public:
    explicit Logical(QObject *parent = 0);

    int init(Model* model);

    Q_INVOKABLE void sendLogin(QVariant name,QVariant psw);
    void GetLogin(const QJsonObject &obj);
    void Start();
private:
    QTcpSocket* m_socket;
    Model* m_model;
    int m_index;
    QString m_host;
    unsigned short m_port;
    int num1;
    int num2;
signals:
    void m_signal_SendMsg(QJsonObject);
    void m_signal_start();
public slots:
    void DoWork();
    void ReConnect();
    int StarClient();
    void SendMsg(QJsonObject obj);
};

#endif // LOGICAL_H
