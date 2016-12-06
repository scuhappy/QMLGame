#ifndef LOGICAL_H
#define LOGICAL_H

#include <QObject>
#include"Client.h"
#include<QTcpSocket>
#include"ReadWorker.h"
#include"WriteWorker.h"
#include"Model.h"
class Logical : public QObject
{
    Q_OBJECT
public:
    explicit Logical(QObject *parent = 0);

    int init(Model* model);
    int StarClient();
    Q_INVOKABLE void sendLogin(QVariant name,QVariant psw);

private:
    Client* m_client;
    QTcpSocket* m_socket;
    ReadWorker* m_reader;
    WriteWorker* m_writer;
    Model* m_model;
    int m_index;
signals:

public slots:
    void RestartWriter();

    void DoWork();

};

#endif // LOGICAL_H
