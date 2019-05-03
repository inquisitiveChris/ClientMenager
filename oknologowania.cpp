#include "oknologowania.h"
#include "ui_oknologowania.h"
#include <QMessageBox>
#include <QKeyEvent>

OknoLogowania::OknoLogowania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoLogowania)
{
    ui->setupUi(this);
}

OknoLogowania::~OknoLogowania()
{
    delete ui;
}

void OknoLogowania::on_LoginButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username != "admin" || password != "admin")
    {
        ui->lineEdit_username->setText("admin");
        ui->lineEdit_password->setText("admin");
        /* TODO: Na oknie logowania dodać kontrolkę tekstową i poinformować o błedzie*/
        ui->label_info->setText("nieprawidłowa nazwa uzytkownika lub hasło");
    }
    else
        accept();
}
