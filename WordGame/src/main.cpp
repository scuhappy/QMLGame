#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include<QQmlComponent>
#include<QThread>
#include<QTimer>
#include"Tools.h"
#include"Logical.h"
#include"Model.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Model model;
    engine.rootContext()->setContextProperty("clientmodel",&model);
    Logical logicalObj;
    QThread *thread =new QThread();
    logicalObj.moveToThread(thread);
    thread->start();
    engine.rootContext()->setContextProperty("logical",&logicalObj);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    qDebug()<<QThread::currentThreadId();
    logicalObj.init(&model);
    logicalObj.Start();


    return app.exec();
}
