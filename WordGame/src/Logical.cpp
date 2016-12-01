#include "Logical.h"
#include<QDebug>
#include<QJsonObject>
#include"Types.h"
Logical::Logical(QObject *parent) :
    QObject(parent)
{
}
int Logical::init(Model* model)
{
    if(model==NULL)
    {
        return -1;
    }
    else
    {
        m_model = model;
        m_writer = new WriteWorker();
    }

}
void Logical::sendLogin(QVariant name, QVariant psw)
{
    QJsonObject obj;
    obj.insert("Type",LOGIN);
    obj.insert("name",name.toString());
    obj.insert("psd",psw.toString());
    m_writer->AddMsg(obj);

}

int Logical::StarClient()
{
    m_writer->init(m_model);
    m_writer->start();
}
