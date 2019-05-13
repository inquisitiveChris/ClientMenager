#include "oknologowania.h"
#include "ui_oknologowania.h"
#include <QPixmap>

OknoLogowania::OknoLogowania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoLogowania)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/Logo.png");
    ui->label_pic->setPixmap(pix.scaled(380,90));
}

OknoLogowania::~OknoLogowania()
{
    delete ui;
}

void OknoLogowania::on_LoginButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username != "admin" || password != "admin") {

          ui->lineEdit_username->setText("admin");
          ui->lineEdit_password->setText("admin");

        ui->label_info->setText("nieprawidłowa nazwa uzytkownika lub hasło");
    }
    else {
        hide();
        mainWindow.showMaximized();
    }
}
