#ifndef WRITEWORKER_H
#define WRITEWORKER_H

#include <QThread>
#include<QTcpSocket>
#include"Model.h"
#include<QQueue>
#include<QJsonObject>
#include<QJsonDocument>
class WriteWorker : public QThread
{
    Q_OBJECT
public:
    explicit WriteWorker(QObject *parent = 0);
    void init(Model* model);
    void AddMsg(QJsonObject obj);
protected:
    void run();
private:

    void GetLogin(const QJsonObject &obj);

    QTcpSocket* m_socket;
    Model* m_model;
    bool m_stop;
    QQueue<QJsonObject> m_queue;
signals:

public slots:
    void DoWork();
};

#endif // WRITEWORKER_H
