#include "addpolicydialog.h"
#include "policywidget.h"
#include "mainwindow.h"

#include <QtWidgets>
#include <QHeaderView>




extern MainWindow * getMainWindow();

PolicyWidget::PolicyWidget(QWidget *parent)
    : QTabWidget (parent)
{

    table = new PolicyTableModel(this);
    setupTabs();
    readFromFile("dbp.abk");

}

PolicyWidget::~PolicyWidget()
{
    this->writeToFile("dbp.abk");
}

void PolicyWidget::showAddEntryDialog()
{
    AddPolicyDialog aDialog;

    TableModel *table = getMainWindow()->getAddressWidget()->getTable();
    QList<Contact> contacts = table->getContacts();
    //QMessageBox::information(this, tr("tast uchwytu kontaktow"),
        //tr("liczba kotaktow \"%1\" wynosi").arg(contacts.count()));

    foreach(Contact con, contacts) {
        aDialog.clientId->addItem(con.name,con.pesel);
    }

    if (aDialog.exec()) {
        QString type = aDialog.typeText->text();
        QString company = aDialog.companyText->text();
        QString num = aDialog.numText->text();
        // get PESEL attached to selected name
        QString client_id = aDialog.clientId->currentData().toString();
        QString period_from = aDialog.periodBeginDate->date().toString("dd.MM.yyyy");
        QString period_to = aDialog.periodEndDate->date().toString("dd.MM.yyyy");
        QString payment = aDialog.paymentBox->currentData().toString();

    if(type.length() > 0)
        addEntry(type, company, num, period_from, period_to, client_id, payment);
    }
}
void PolicyWidget::addEntry(QString type, QString company, QString num, QString period_from, QString period_to,
                            QString client_id, QString payment_from)
{
    if (!table->getPolicies().contains({ type, company, num, period_from, period_to,
                                         client_id, payment_from})) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, type, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, company, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, num, Qt::EditRole);
        index = table->index(0, 3, QModelIndex());
        table->setData(index, period_from, Qt::EditRole);
        index = table->index(0, 4, QModelIndex());
        table->setData(index, period_to, Qt::EditRole);
        index = table->index(0, 5, QModelIndex());
        table->setData(index, client_id, Qt::EditRole);
        index = table->index(0, 6, QModelIndex());
        table->setData(index, payment_from, Qt::EditRole);
        /* poinformuj MainWindow że dane zostały zmienione */
        getMainWindow()->setModified(true);
    } else {
        QMessageBox::information(this, tr("Duplicate Number"),
            tr("The number \"%1\" already exists.").arg(num));
    }
}
void PolicyWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

   // get access to contacts
    TableModel *tableC = getMainWindow()->getAddressWidget()->getTable();
    QList<Contact> contacts = tableC->getContacts();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString type;
    QString company;
    QString num;
    QString period_from;
    QString period_to;
    QString client_id;
    QString payment_from;

    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex typeIndex = table->index(row, 0, QModelIndex());
        QVariant varType = table->data(typeIndex, Qt::DisplayRole);
        type = varType.toString();

        QModelIndex companyIndex = table->index(row, 1, QModelIndex());
        QVariant varCompany = table->data(companyIndex, Qt::DisplayRole);
        company = varCompany.toString();

        QModelIndex numIndex = table->index(row, 2, QModelIndex());
        QVariant varNum = table->data(numIndex, Qt::DisplayRole);
        num = varNum.toString();

        QModelIndex period_fromIndex = table->index(row, 3, QModelIndex());
        QVariant varPeriod_from = table->data(period_fromIndex, Qt::DisplayRole);
        period_from = varPeriod_from.toString();

        QModelIndex period_toIndex = table->index(row, 4, QModelIndex());
        QVariant varPeriod_to = table->data(period_toIndex, Qt::DisplayRole);
        period_to = varPeriod_to.toString();

        QModelIndex client_idIndex = table->index(row, 5, QModelIndex());
        QVariant varClient_id = table->data(client_idIndex, Qt::DisplayRole);
        client_id = varClient_id.toString();

        QModelIndex payment_fromIndex = table->index(row, 6, QModelIndex());
        QVariant varPayment_from = table->data(payment_fromIndex, Qt::DisplayRole);
        payment_from = varPayment_from.toString();
    }
//! [4a]

//! [4b]
    AddPolicyDialog aDialog;

    int clientIndex = 0;
    int ci = 0;
    QDate date;


    aDialog.setWindowTitle(tr("Edytuj polisę"));

    aDialog.clientId->clear();
    foreach(Contact con, contacts) {
        aDialog.clientId->addItem(con.name,con.pesel);
        if(con.pesel == client_id)
            clientIndex = ci;
        ci++;
    }
    aDialog.clientId->setCurrentIndex(clientIndex);

    aDialog.typeText->setText(type);
    aDialog.companyText->setText(company);
    aDialog.numText->setText(num);
    //QMessageBox::information(this, period_from,period_to);
    date = QDate::fromString(period_from,"dd.MM.yyyy");
    aDialog.periodBeginDate->setDate(date);
    //QString da = date.toString();
    date = QDate::fromString(period_to,"dd.MM.yyyy");
    aDialog.periodEndDate->setDate(date);
    //QString db = date.toString();
    //QMessageBox::information(this, da,db);
    //aDialog.payment->setText(payment_from);

    if (aDialog.exec()) {
        bool policyModified = false;
        QString newType = aDialog.typeText->text();
        if (newType != type) {
            policyModified = true;
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newType, Qt::EditRole);
        }
        QString newCompany = aDialog.companyText->text();
        if (newCompany != company) {
            policyModified = true;
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newCompany, Qt::EditRole);
        }
        QString newNum = aDialog.numText->text();
        if (newNum != num) {
            policyModified = true;
            QModelIndex index = table->index(row, 2, QModelIndex());
            table->setData(index, newNum, Qt::EditRole);
        }
        QString newPeriod_from = aDialog.periodBeginDate->date().toString("dd.MM.yyyy");
        if (newPeriod_from != period_from) {
             policyModified = true;
            QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newPeriod_from, Qt::EditRole);
        }
        QString newPeriod_to = aDialog.periodEndDate->date().toString("dd.MM.yyyy");
        if (newPeriod_to != period_to) {
             policyModified = true;
            QModelIndex index = table->index(row, 4, QModelIndex());
            table->setData(index, newPeriod_to, Qt::EditRole);
         }
        QString newClient_id = aDialog.clientId->currentData().toString();
        if (newClient_id != client_id) {
             policyModified = true;
            QModelIndex index = table->index(row, 5, QModelIndex());
            table->setData(index, newClient_id, Qt::EditRole);
         }
        QString newPayment = aDialog.paymentBox->currentData().toString();
        if (newPayment != payment_from) {
             policyModified = true;
            QModelIndex index = table->index(row, 6, QModelIndex());
            table->setData(index, newPayment, Qt::EditRole);
         }

         if(policyModified == true) {
               /* poinformuj MainWindow że dane zostały zmienione */
               getMainWindow()->setModified(true);
         }
    }
}
//! [4b]

//! [5]
void PolicyWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }
    /* poinformuj MainWindow że dane zostały zmienione */
   getMainWindow()->setModified(true);
}
void PolicyWidget::setupTabs()
{
    QStringList groups;
    groups << "Twoje polisy";

    //tableView->setUpdatesEnabled(false);

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);
        tableView->setAlternatingRowColors(true);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        //QListWidgetItem* item = tableView->itemDelegateForColumn(i);

        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &PolicyWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
            auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
            if (tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}

void PolicyWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku polis"),
            file.errorString());
        return;
    }

    QList<Policy> policies;
    QDataStream in(&file);
    in >> policies;

    if (policies.isEmpty()) {
        QMessageBox::information(this, tr("Brak polis w pliku"),
                                 tr("Plik który próbujesz otworzyć nie zawiera polis."));
    } else {
        for (const auto &policy: qAsConst(policies))
            addEntry(policy.type, policy.company, policy.num, policy.period_from, policy.period_to, policy.client_id, policy.payment_from);
    }
}

void PolicyWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Nie można otworzyć pliku polis"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getPolicies();

}
