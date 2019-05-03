#ifndef ADDPOLICYDIALOG_H
#define ADDPOLICYDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE

class AddPolicyDialog : public QDialog
{
    Q_OBJECT
public:
    AddPolicyDialog(QWidget *parent = nullptr);
    QLineEdit *typeText;
    QLineEdit *companyText;
    QLineEdit *numText;
    QLineEdit *periodText;

private:
    QLabel *typeLabel;
    QLabel *companyLabel;
    QLabel *numLabel;
    QLabel *periodLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDPOLICYDIALOG_H
