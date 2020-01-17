#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoRoute>
#include <QQuickWidget>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QListWidgetItem>
#include <string>
#include <addform.h>
using namespace std;

class MyClass : public QObject
{
    Q_OBJECT

    int error = 0;
signals:
    void updatemap(QVariant);
    void clearmap();
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct maplist
{
    QString text;
    double lon;
    double lat;
    maplist *next;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MyClass myclass;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchbutton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void geocodechecker(int error);

    void addfavorit(double x, double y);

    void gettext(QString str);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QQuickWidget *map;
    QObject *mapobj;
    QObject *mapchange;
    QObject *object;
    QObject *whot;
    QObject *test;
    Addform *form;
public:
    maplist *maplst;
};

#endif // MAINWINDOW_H
