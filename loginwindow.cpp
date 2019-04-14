#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "admin" && password == "admin"){
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        mainWindow = new MainWindow();
        mainWindow->show();
    }
    else{
    QMessageBox::warning(this, "Login", "Username and password is not correct");
    }
}

