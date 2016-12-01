#ifndef TOOLS_H
#define TOOLS_H

#include<QObject>
#include<QVariantMap>
class Tools : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QVariantMap wordMap READ wordMap WRITE setWordMap NOTIFY wordMapChanged)
    Q_PROPERTY(QMap<int,QString> testmap READ testmap WRITE setTestmap NOTIFY testmapChanged)
    explicit Tools(QObject *parent = 0);
    //age
    int m_age;
    int age(){return m_age;}
    void setAge(int age)
    {
        m_age= age;
    }
    QVariantMap m_wordMap;
    QVariantMap wordMap(){
        return m_wordMap;
    }
    void setWordMap(QVariantMap map)
    {
        m_wordMap = map;
    }

    QMap<int,QString> m_testmap;
    QMap<int,QString> testmap(){return m_testmap;}
    void setTestmap(QMap<int,QString> map){m_testmap = map;}
signals:
    void ageChanged();
    void wordMapChanged();
    void testmapChanged();
public slots:
};

#endif // TOOLS_H
