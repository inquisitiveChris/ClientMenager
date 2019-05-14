#include "addpolicydialog.h"
#include "policywidget.h"
#include "mainwindow.h"

#include <QtWidgets>

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

    if (aDialog.exec()) {
        QString type = aDialog.typeText->text();
        QString company = aDialog.companyText->text();
        QString num = aDialog.numText->text();
        QString period_from = aDialog.periodBeginDate->date().toString();
        QString period_to = aDialog.periodEndDate->date().toString();

    if(type.length() > 0)
        addEntry(type, company, num, period_from, period_to);
    }
}
void PolicyWidget::addEntry(QString type, QString company, QString num, QString period_from, QString period_to)
{
    if (!table->getPolicies().contains({ type, company, num, period_from, period_to })) {
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

    QModelIndexList indexes = selectionModel->selectedRows();
    QString type;
    QString company;
    QString num;
    QString period_from;
    QString period_to;

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
    }
//! [4a]

//! [4b]
    AddPolicyDialog aDialog;
    aDialog.setWindowTitle(tr("Edytuj polisę"));

    aDialog.typeText->setText(type);
    aDialog.companyText->setText(company);
    aDialog.numText->setText(num);
    QDate date = QDate::currentDate();
    aDialog.periodBeginDate->setDate(/*period_from*/ date);
    aDialog.periodEndDate->setDate(/*period_to*/ date);



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
        QString newPeriod_from = aDialog.periodBeginDate->date().toString();
        if (newPeriod_from != period_from) {
             policyModified = true;
            QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newPeriod_from, Qt::EditRole);
        }
        QString newPeriod_to = aDialog.periodEndDate->date().toString();
        if (newPeriod_to != period_to) {
             policyModified = true;
            QModelIndex index = table->index(row, 4, QModelIndex());
            table->setData(index, newPeriod_to, Qt::EditRole);
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

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
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
            addEntry(policy.type, policy.company, policy.num, policy.period_from, policy.period_to);
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
