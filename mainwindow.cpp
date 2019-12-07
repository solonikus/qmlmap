#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGeoRoute>
#include <QGeoCoordinate>
#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include <string>
#include <QQmlComponent>
#include <QQmlEngine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QQuickWidget *view = ui->miniw;             // Здесь мы подключаем наш виджет
    view->setSource(QUrl("qrc:/test.qml"));     // Здесь задаем QML файл
    object = view->rootObject();                // Присваевыем объект, что в классе
    whot = object->findChild<QObject*>("text1");//Здесь мы находим объект дочерний в qml
    map = ui->mpv;
    map->setSource(QUrl("qrc:/map.qml"));
    mapobj = map->rootObject();
    mapchange = mapobj->findChild<QObject*>("map1");
    map->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    object->setProperty("text",QVariant("Change you text here..."));
}

MainWindow::~MainWindow()
{
    delete ui;
    exit(0);
}

void MainWindow::on_searchbutton_clicked()
{
    ui->statusbar->showMessage(whot->property("text").toString()); //Получить свойства в статус бар
    whot->setProperty("text","Change you text here...");  //И меняем атрибуты
    mapchange->setProperty("center", QVariant::fromValue(QGeoCoordinate(32,25))); //передача координат в QML движок
}
