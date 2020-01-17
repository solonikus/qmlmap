#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>
#include <string>
using namespace std;

namespace Ui {
class Addform;
}

class Addform : public QWidget
{
    Q_OBJECT

public:
    double x;
    double y;

public:
    explicit Addform(QWidget *parent = nullptr);
    ~Addform();

signals:
    void sendtext(QString str);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Addform *ui;
};

#endif // ADDFORM_H
