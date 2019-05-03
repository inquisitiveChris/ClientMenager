/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "adddialog.h"
#include "addresswidget.h"

#include <QtWidgets>

//! [0]
AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    auto* tabpointer = table;
    setupTabs();
    autoOpenFile();

    QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(autoSave()));
       timer->start(300000);
}
//! [0]

//! [2]
void AddressWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString pesel = aDialog.peselText->text();
        QString address = aDialog.addressText->toPlainText();
        QString telefon = aDialog.telefonText->text();
        QString email = aDialog.emailText->text();
        QString nip = aDialog.nipText->text();
        QString regon = aDialog.regonText->text();

        addEntry(name, pesel,  address,  telefon,  email, nip, regon);
    }
}
//! [2]

//! [3]
void AddressWidget::addEntry(QString name, QString pesel, QString address, QString telefon, QString email, QString nip, QString regon)
{
    if (!table->getContacts().contains({ name, pesel, address, telefon, email, nip, regon })) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, pesel, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, address, Qt::EditRole);
        index = table->index(0, 3, QModelIndex());
        table->setData(index, telefon, Qt::EditRole);
        index = table->index(0, 4, QModelIndex());
        table->setData(index, email, Qt::EditRole);
        index = table->index(0, 5, QModelIndex());
        table->setData(index, nip, Qt::EditRole);
        index = table->index(0, 6, QModelIndex());
        table->setData(index, regon, Qt::EditRole);
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}
//! [3]

//! [4a]
void AddressWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString pesel;
    QString address;
    QString telefon;
    QString email;
    QString nip;
    QString regon;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex peselIndex = table->index(row, 1, QModelIndex());
        QVariant varPesel = table->data(peselIndex, Qt::DisplayRole);
        pesel = varPesel.toString();

        QModelIndex addressIndex = table->index(row, 2, QModelIndex());
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();

        QModelIndex telefonIndex = table->index(row, 3, QModelIndex());
        QVariant varTelefon = table->data(telefonIndex, Qt::DisplayRole);
        telefon = varTelefon.toString();

        QModelIndex emailIndex = table->index(row, 4, QModelIndex());
        QVariant varEmail = table->data(emailIndex, Qt::DisplayRole);
        email = varEmail.toString();

        QModelIndex nipIndex = table->index(row, 5, QModelIndex());
        QVariant varNip = table->data(nipIndex, Qt::DisplayRole);
        nip = varNip.toString();

        QModelIndex regonIndex = table->index(row, 6, QModelIndex());
        QVariant varRegon = table->data(regonIndex, Qt::DisplayRole);
        regon = varRegon.toString();
    }
//! [4a]

//! [4b]
    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edytuj klienta"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.peselText->setText(pesel);
    aDialog.addressText->setText(address);
    aDialog.telefonText->setText(telefon);
    aDialog.emailText->setText(email);
    aDialog.nipText->setText(nip);
    aDialog.regonText->setText(regon);

    if (aDialog.exec()) {
        QString newPesel = aDialog.peselText->text();
        if (newPesel != pesel) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newPesel, Qt::EditRole);
        }
        QString newAddress = aDialog.addressText->toPlainText();
        if (newAddress != address) {
            QModelIndex index = table->index(row, 2, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
        QString newTelefon = aDialog.telefonText->text();
        if (newTelefon != telefon) {
            QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newTelefon, Qt::EditRole);
        }
        QString newEmail = aDialog.emailText->text();
        if (newEmail != email) {
            QModelIndex index = table->index(row, 4, QModelIndex());
            table->setData(index, newEmail, Qt::EditRole);
        }
        QString newNip = aDialog.nipText->text();
        if (newNip != nip) {
            QModelIndex index = table->index(row, 5, QModelIndex());
            table->setData(index, newNip, Qt::EditRole);
        }
        QString newRegon = aDialog.regonText->text();
        if (newRegon != regon) {
            QModelIndex index = table->index(row, 6, QModelIndex());
            table->setData(index, newRegon, Qt::EditRole);
        }
    }
}
//! [4b]

//! [5]
void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }
}
//! [5]

//! [1]
void AddressWidget::setupTabs()
{
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);
        QString regExp = QString("^[%1].*").arg(str);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &AddressWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
            auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
            if (tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}
//! [1]

//! [7]
void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
            file.errorString());
        return;
    }

    QList<Contact> contacts;
    QDataStream in(&file);
    in >> contacts;

    if (contacts.isEmpty()) {
        QMessageBox::information(this, tr("Brak kontaktów w pliku"),
                                 tr("Plik który próbujesz otworzyć nie zawiera kontaktów."));
    } else {
        for (const auto &contact: qAsConst(contacts))
            addEntry(contact.name, contact.pesel, contact.address, contact.telefon, contact.email, contact.nip, contact.regon);
    }
}
//! [7]

//! [6]
void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getContacts();
}
//! [6]
//! [8]
void AddressWidget::autoOpenFile()
{
    QFile file("db.abk");

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
            file.errorString());
        return;
     }

        QList<Contact> contacts;
        QDataStream in(&file);
        in >> contacts;

        if (contacts.isEmpty()) {
            QMessageBox::information(this, tr("Brak kontaktów w pliku"),
                                     tr("Plik który próbujesz otworzyć nie zawiera kontaktów."));
        } else {
            for (const auto &contact: qAsConst(contacts))
                addEntry(contact.name, contact.pesel, contact.address, contact.telefon, contact.email, contact.nip, contact.regon);
        }
    file.close();
}
//! [8]
//! [9]
void AddressWidget::autoSave()
{
    QFile file("dbautosave.abk");

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getContacts();

}
//! [9]

