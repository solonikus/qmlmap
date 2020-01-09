#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
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
    QObject::connect(&myclass, SIGNAL(updatemap(QVariant)), mapobj, SLOT(search(QVariant))); //Подключение сигнала из класса к слоту(функции) в qml. Причем изначально надо подключить к движку qml.
    QObject::connect(&myclass, SIGNAL(clearmap()), mapobj, SLOT(clear()));
    QObject::connect(mapobj, SIGNAL(geocodecheck(int)), &myclass, SLOT(geocodechecker(int)));
//    object->setProperty("text",QVariant("Change you text here..."));
}

void MyClass::geocodechecker(int error)
{
    qDebug() << "Status: " << error;
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
    exit(0);
}

void MainWindow::on_searchbutton_clicked()
{
    double lon = 181;
    double lat = 181;
    if (ui->lineEdit->text() == "." || ui->lineEdit_2->text() == ".")
    {
        ui->statusbar->showMessage("Error, empty coordinate", 5000);
        return;
    }
    lat = std::stod(ui->lineEdit->text().toStdString());
    lon = std::stod(ui->lineEdit_2->text().toStdString());
    if ((lat > 90.0 || lat < -90.0) || (lon > 180.0 || lon < -180.0))
    {
        ui->statusbar->showMessage("Error, wrong coordinate", 5000);
        return;
    }
//    ui->statusbar->showMessage(mapchange->property("center").toString()); //Получить свойства в статус бар
//    whot->setProperty("text","Change you text here...");  //И меняем атрибуты
    mapchange->setProperty("center", QVariant::fromValue(QGeoCoordinate(lat,lon))); //передача координат в QML движок
    ui->statusbar->showMessage("Complete", 5000);
}



void MainWindow::on_pushButton_clicked()
{
    QString str1 = ui->lineEdit_3->text();
    QVariant qv(str1);
    qDebug() << "Str1:" << str1;
    if (ui->lineEdit_3->text() == "")
    {
        ui->statusbar->showMessage("Error, empty search line", 5000);
        return;
    }
    emit myclass.updatemap(qv);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_3->clear();
    emit myclass.clearmap();
}
