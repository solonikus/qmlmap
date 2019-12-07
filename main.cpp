#include "mainwindow.h"
#include "myclass.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QObject>
#include <QQuickItem>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QQmlEngine engine;
//    QQmlComponent component(&engine, "qrc:/hello.qml");
//    w.object = component.create();
//    w.object->setProperty("width", 500);
//    QQuickView view;
//    view.setSource(QUrl("qrc:/map.qml"));
//    view.show();
//    QObject *object = view.rootObject();
    w.show();
//    object->setProperty("textText",QVariant("Change you text here..."));
    return a.exec();
}
