#ifndef LOGICAL_H
#define LOGICAL_H

#include <QObject>
#include<QTcpSocket>
#include"Model.h"
class Logical : public QObject
{
    Q_OBJECT
public:
    explicit Logical(QObject *parent = 0);

    int init(Model* model);
    int StarClient();
    Q_INVOKABLE void sendLogin(QVariant name,QVariant psw);
    void GetLogin(const QJsonObject &obj);
private:
    QTcpSocket* m_socket;
    Model* m_model;
    int m_index;
signals:

public slots:
    void DoWork();

};

#endif // LOGICAL_H
