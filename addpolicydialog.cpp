#include "addpolicydialog.h"

#include <QtWidgets>

AddPolicyDialog::AddPolicyDialog(QWidget *parent)
    : QDialog(parent)
{
    typeLabel = new QLabel("Rodzaj ubezpieczenia");
    companyLabel = new QLabel("Firma ubezpieczeniowa");
    numLabel = new QLabel("Numer polisy");
    periodLabel = new QLabel("Okres ochrony");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    typeText = new QLineEdit;
    companyText = new QLineEdit;
    numText = new QLineEdit;
    periodText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(typeLabel, 0, 0);
    gLayout->addWidget(typeText, 0, 1);

    gLayout->addWidget(companyLabel, 1, 0);
    gLayout->addWidget(companyText, 1, 1);

    gLayout->addWidget(numLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(numText, 2, 1, Qt::AlignLeft);

    gLayout->addWidget(periodLabel, 3, 0);
    gLayout->addWidget(periodText, 3, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Dodaj polisę"));
}
