#include "addpolicydialog.h"

#include <QtWidgets>
#include <QComboBox>

AddPolicyDialog::AddPolicyDialog(QWidget *parent)
    : QDialog(parent)
{
    typeLabel = new QLabel("Rodzaj ubezpieczenia:");
    companyLabel = new QLabel("Firma ubezpieczeniowa:");
    numLabel = new QLabel("Numer polisy:");
    periodLabelBegin = new QLabel("Ochrona od:");
    periodLabelEnd = new QLabel("Ochrona do:");
    clientLabelid = new QLabel ("Identyfikator klienta:");
    paymentLabelFrom = new QLabel ("Zapłacono:");

    clientId = new QComboBox;
    typeText = new QLineEdit;
    companyText = new QLineEdit;
    numText = new QLineEdit;
    payment_fromText = new QLineEdit;
    periodBeginDate = new QDateEdit;
    periodEndDate = new QDateEdit;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    QGridLayout *gLayout = new QGridLayout;


    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(clientLabelid, 0,0);
    gLayout->addWidget(clientId, 0,1);

    gLayout->addWidget(typeLabel, 1, 0);
    gLayout->addWidget(typeText, 1, 1);

    gLayout->addWidget(companyLabel, 2, 0);
    gLayout->addWidget(companyText, 2, 1);

    gLayout->addWidget(numLabel, 3, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(numText, 3, 1, Qt::AlignLeft);

    gLayout->addWidget(periodLabelBegin, 4, 0);
    gLayout->addWidget(periodBeginDate, 4, 1);
    gLayout->addWidget(periodLabelEnd, 5, 0);
    gLayout->addWidget(periodEndDate, 5, 1);

    gLayout->addWidget(paymentLabelFrom, 6, 0);
    gLayout->addWidget(payment_fromText, 6, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 8, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Dodaj polisę"));
}
