#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoRoute>
#include <QQuickWidget>
#include <QQuickView>
#include <string>
using namespace std;

class MyClass : public QObject
{
    Q_OBJECT

    int error = 0;
public slots:
    void geocodechecker(int error);
signals:
    void updatemap(QVariant);
    void clearmap();
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    QQuickWidget *map;
    QObject *mapobj;
    QObject *mapchange;
    QObject *object;
    QObject *whot;
    QObject *test;
};

#endif // MAINWINDOW_H
