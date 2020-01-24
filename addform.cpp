#include "addform.h"
#include "ui_addform.h"
#include <QMessageBox>

Addform::Addform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addform)
{
    ui->setupUi(this);
}

Addform::~Addform()
{
    delete ui;
}

void Addform::on_pushButton_2_clicked()
{
    this->close();
}

void Addform::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "")
    {
        QMessageBox::information(nullptr, "Внимание", "Введите навзание вкладки");
        return;
    }
    emit sendtext(ui->lineEdit->text());
    this->close();
    ui->pushButton->setText("Добавить");
    ui->lineEdit->clear();
}

void Addform::editer(QString text)
{
    ui->lineEdit->setText(text);
    ui->pushButton->setText("Изменить");
    flag = 1;
}
