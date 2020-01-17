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
    form = new Addform();
    maplst = NULL;
//    QQuickWidget *view = ui->miniw;             // Здесь мы подключаем наш виджет
//    view->setSource(QUrl("qrc:/test.qml"));     // Здесь задаем QML файл
//    object = view->rootObject();                // Присваевыем объект, что в классе
    whot = object->findChild<QObject*>("text1");//Здесь мы находим объект дочерний в qml
    map = ui->mpv;
    map->setSource(QUrl("qrc:/map.qml"));
    mapobj = map->rootObject();
    mapchange = mapobj->findChild<QObject*>("map1");
    map->setResizeMode(QQuickWidget::SizeRootObjectToView);
    QObject::connect(&myclass, SIGNAL(updatemap(QVariant)), mapobj, SLOT(search(QVariant))); //Подключение сигнала из класса к слоту(функции) в qml. Причем изначально надо подключить к движку qml.
    QObject::connect(&myclass, SIGNAL(clearmap()), mapobj, SLOT(clear()));
    QObject::connect(mapobj, SIGNAL(geocodecheck(int)), this, SLOT(geocodechecker(int)));
    QObject::connect(mapobj, SIGNAL(addfavorit(double,double)), this, SLOT(addfavorit(double, double)));
    QObject::connect(form, SIGNAL(sendtext(QString)), this, SLOT(gettext(QString)));
//    object->setProperty("text",QVariant("Change you text here..."));
}

void MainWindow::geocodechecker(int error)
{
    if (error == 1)
        ui->statusbar->showMessage("No geocode requests have been issued or reset has been called.", 3000);
    if (error == 2)
        ui->statusbar->showMessage("Ready", 3000);
    if (error == 3)
        ui->statusbar->showMessage("Loading", 3000);
    if (error == 4)
        ui->statusbar->showMessage("Error", 3000);
    return;
}

void addlist(double x, double y, maplist *tmp)
{
    tmp->lat = x;
    tmp->lon = y;

}

void MainWindow::addfavorit(double x, double y)
{
    form->x = x;
    form->y = y;
    form->show();
}

void MainWindow::gettext(QString str)
{
    maplist *tmp;
    if (maplst == NULL)
    {
        maplst = new maplist;
        maplst->next = NULL;
        maplst->lat = form->x;
        maplst->lon = form->y;
        maplst->text = str;
    }
    else
    {
        tmp = maplst;
        while (tmp->next != NULL)
        {
            if (tmp->next == NULL)
                break;
            tmp = tmp->next;
        }
        tmp->next = new maplist;
        tmp = tmp->next;
        tmp->next = NULL;
        tmp->lat = form->x;
        tmp->lon = form->y;
        tmp->text = str;
    }
    ui->listWidget->addItem(str);

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

maplist *searchlst(QString text, maplist *lst)
{
    maplist *tmp;
    tmp = lst;
    if (text == tmp->text)
        return (tmp);
    while (tmp != NULL)
    {
        if (text == tmp->text)
            return (tmp);
        else
            tmp = tmp->next;
    }
    return (NULL);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "Status: !!!";
    maplist *cur;
    cur = searchlst(item->text(), this->maplst);
    if (cur == NULL)
        ui->statusbar->showMessage("Error!!!!!!!!!!!!!!!!!!!!!!!!!!", 5000);
    else
    {
         mapchange->setProperty("center", QVariant::fromValue(QGeoCoordinate(cur->lat,cur->lon)));
         mapchange->setProperty("zoomLevel", 15);
    }
}
