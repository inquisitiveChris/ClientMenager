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

#include "mainwindow.h"
#include <QAction>
#include <QDialog>
#include <QFileDialog>
#include <QSaveFile>
#include <QMenuBar>
#include <QtWidgets>

//! [0]
MainWindow::MainWindow()
{
    centralArea = new QMdiArea;
    policyWidget = new PolicyWidget;
    addressWidget = new AddressWidget;
    textEdit = new QTextEdit;
    setModified(false);
    centralArea->setViewMode(QMdiArea::TabbedView);
    setCentralWidget(centralArea);
    addressWidget->setWindowTitle("Klienci");
    policyWidget->setWindowTitle("Polisy");
    centralArea->addSubWindow(addressWidget);
    centralArea->addSubWindow(policyWidget);
    createMenus();
    setWindowTitle(tr("Polisman 1.0"));
}
//! [0]
void MainWindow::setModified(bool bModified)
{
    data_modified = bModified;
}

bool MainWindow::getModified()
{
    return data_modified;
}
//! [1a]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Plik"));

    openAct = new QAction(tr("&Otwórz..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
//! [1a]

    saveAct = new QAction(tr("&Zapisz jako..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Wyjdź"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Klienci"));

    addAct = new QAction(tr("&Dodaj klienta..."), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, addressWidget, &AddressWidget::showAddEntryDialog);

//! [1b]
    editAct = new QAction(tr("&Edytuj klienta..."), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, addressWidget, &AddressWidget::editEntry);

    toolMenu->addSeparator();

    removeAct = new QAction(tr("&Usuń klienta"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, addressWidget, &AddressWidget::removeEntry);

    toolMenu = menuBar()->addMenu(tr("&Polisy"));

    addPolicyAct = new QAction(tr("&Dodaj polise..."), this);
    toolMenu->addAction(addPolicyAct);
    connect(addPolicyAct, &QAction::triggered, policyWidget, &PolicyWidget::showAddEntryDialog);

    editPolicyAct = new QAction(tr("&Edytuj polise..."), this);
    editPolicyAct->setEnabled(false);
    toolMenu->addAction(editPolicyAct);
    connect(editPolicyAct, &QAction::triggered, policyWidget, &PolicyWidget::editEntry);

    toolMenu->addSeparator();

    removePolicyAct = new QAction(tr("&Usuń polise"), this);
    removePolicyAct->setEnabled(false);
    toolMenu->addAction(removePolicyAct);
    connect(removePolicyAct, &QAction::triggered, policyWidget, &PolicyWidget::removeEntry);

    connect(addressWidget, &AddressWidget::selectionChanged,
        this, &MainWindow::updateActions);
    connect(policyWidget, &PolicyWidget::selectionChanged,
        this, &MainWindow::updateActions);
}
//! [1b]

//! [2]
void MainWindow::openFile()
{
    if(getModified()){
        /* TODO: change to question and take appropriate action */
        QMessageBox::warning(this,"Uwaga", "wszystkie zmiany w pliku zostaną utracone");
    } else {
        QString fileName =
                QFileDialog::getOpenFileName(this,
                                             tr("Open Address Book"), "db",
                                             tr("Address Book (*.abk);;All Files (*)"));
        if (!fileName.isEmpty()) {
            addressWidget->readFromFile(fileName);
            setModified(false);
        }
    }
}
//! [2]

//! [3]
void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Address Book"), "db",
           tr("Address Book (*.abk);;All Files (*)"));
    if (!fileName.isEmpty()) {
        addressWidget->writeToFile(fileName);
        setModified(false);
    }
}
//! [3]

//! [4]
void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if (!indexes.isEmpty()) {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}
//! [4]

//! [5]

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(getModified()) {
        int answer = QMessageBox::question(this, "Dane klientów zostały zmienione", "Czy chcesz zapisać zmiany?");
        if (answer == QMessageBox::Yes) {
            QString fileName = QFileDialog::getSaveFileName(this,
                   tr("Save Address Book"), "db.abk",
                   tr("Address Book (*.abk);;All Files (*)"));
            if (!fileName.isEmpty())
                addressWidget->writeToFile(fileName);
        }
    }
    QMainWindow::closeEvent(event);
}

//! [5]


