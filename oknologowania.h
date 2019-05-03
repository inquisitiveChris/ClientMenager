#ifndef OKNOLOGOWANIA_H
#define OKNOLOGOWANIA_H

#include <QDialog>

namespace Ui {
class OknoLogowania;
}

class OknoLogowania : public QDialog
{
    Q_OBJECT

public:
    explicit OknoLogowania(QWidget *parent = nullptr);
    ~OknoLogowania();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::OknoLogowania *ui;
};

#endif // OKNOLOGOWANIA_H
