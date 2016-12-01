#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include<QQmlComponent>
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
    engine.rootContext()->setContextProperty("logical",&logicalObj);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));


    logicalObj.init(&model);
    if(!logicalObj.StarClient())
    {
        return -1;
    }

    return app.exec();
}
