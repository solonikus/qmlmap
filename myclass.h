#ifndef MYCLASS_H
#define MYCLASS_H

#include <QGeoRoute>
#include <QQuickWidget>
#include <QQuickView>
#include <string>
using namespace std;

class Myclass : public QObject
{
    Q_OBJECT
//public:
//    explicit Myclass();

//signals:
//    // Сигнал для передачи данных в qml-интерфейс
//    void sendToQml(int count);

//public slots:
//    // Слот для приёма данных из qml-интерфейса
//    void receiveFromQml();

private:
    string x; // Счетчик, которым будем оперировать
};

#endif // MYCLASS_H
