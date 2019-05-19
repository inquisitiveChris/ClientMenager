#ifndef ADDPOLICYDIALOG_H
#define ADDPOLICYDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
class QDateEdit;
class QPalette;
class QComboBox;
QT_END_NAMESPACE

class AddPolicyDialog : public QDialog
{
    Q_OBJECT
public:
    AddPolicyDialog(QWidget *parent = nullptr);
    QLineEdit *typeText;
    QLineEdit *companyText;
    QLineEdit *numText;
    QString   clientIdBox;
    QComboBox *clientId;
    QLineEdit *payment_fromText;
    QDateEdit *periodEndDate;
    QDateEdit *periodBeginDate;

private:
    QLabel *typeLabel;
    QLabel *companyLabel;
    QLabel *numLabel;
    QLabel *periodLabelBegin;
    QLabel *periodLabelEnd;
    QLabel *clientLabelid;
    QLabel *paymentLabelFrom;

    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDPOLICYDIALOG_H
