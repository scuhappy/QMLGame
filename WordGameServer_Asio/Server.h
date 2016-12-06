#ifndef SERVER_H
#define SERVER_H

#include <QThread>

class Server : public QThread
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
protected:
    void run();
signals:

public slots:

};

#endif // SERVER_H
