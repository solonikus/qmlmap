#include "addform.h"
#include "ui_addform.h"

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
    emit sendtext(ui->lineEdit->text());
    this->close();
    ui->lineEdit->clear();
}
