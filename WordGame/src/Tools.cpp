#include "Tools.h"

Tools::Tools(QObject *parent) : QObject(parent)
{
    m_age= 3000;
    m_wordMap.insert("ychen",2312);
    m_wordMap.insert("aaa",34);
    m_wordMap.insert("bbb",17);
    m_wordMap.insert("ccc",56);


    m_testmap.insert(20,"aaaaa");
}
