#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include<QVariant>
//#define PROPERTY(type,name) public:\
//    type m_##name;\
//    void set##name(type value){m_##name = value;}\
//    type name(){return m_##name;}
////    signals:\
////    void name##Changed();


class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool Login READ Login WRITE setLogin NOTIFY LoginChanged)
public:
    explicit Model(QObject *parent = 0);

    bool m_Login;
    bool Login(){return m_Login;}
    void setLogin(bool login){m_Login = login; emit LoginChanged();}

signals:
    void PropertyChanged(QVariant);
    void LoginChanged();
public slots:

};

#endif // MODEL_H
