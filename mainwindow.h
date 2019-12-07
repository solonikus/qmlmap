#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoRoute>
#include <QQuickWidget>
#include <QQuickView>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchbutton_clicked();

private:
    Ui::MainWindow *ui;
    QQuickWidget *map;
    QObject *mapobj;
    QObject *mapchange;
    QObject *object;
    QObject *whot;
};
#endif // MAINWINDOW_H
