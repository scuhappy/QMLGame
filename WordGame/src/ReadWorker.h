#ifndef READWORKER_H
#define READWORKER_H

#include <QThread>
#include<QTcpSocket>
#include<QQueue>
#include<QJsonObject>
class Model;
class ReadWorker : public QThread
{
    Q_OBJECT
public:
    explicit ReadWorker(QObject *parent = 0);
    void init(const QTcpSocket* socket,Model* model);
protected:
    void run();

private:
    void DoWork(const QByteArray& buffer);
    void DoWork(const QJsonObject& obj);

    void GetLogin(const QJsonObject& obj);
    QTcpSocket* m_socket;
    Model* m_model;
    bool m_stop;
    QQueue<QJsonObject> m_readQueque;
signals:

public slots:
    void AddReadBuffer();
};

#endif // READWORKER_H
