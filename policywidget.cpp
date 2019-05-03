#include "addpolicydialog.h"
#include "policywidget.h"

#include <QtWidgets>

PolicyWidget::PolicyWidget(QWidget *parent)
    : QTabWidget (parent)
{
    table = new PolicyTableModel(this);
    setupTabs();
}
void PolicyWidget::showAddEntryDialog()
{
    AddPolicyDialog aDialog;

    if (aDialog.exec()) {
        QString type = aDialog.typeText->text();
        QString company = aDialog.companyText->text();
        QString num = aDialog.numText->text();
        QString period = aDialog.periodText->text();


        addEntry(type, company, num, period);
    }
}
void PolicyWidget::addEntry(QString type, QString company, QString num, QString period)
{
    if (!table->getPolicies().contains({ type, company, num, period })) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, type, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, company, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, num, Qt::EditRole);
        index = table->index(0, 3, QModelIndex());
        table->setData(index, period, Qt::EditRole);
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
    QString period;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varType = table->data(nameIndex, Qt::DisplayRole);
        type = varType.toString();

        QModelIndex peselIndex = table->index(row, 1, QModelIndex());
        QVariant varCompany = table->data(peselIndex, Qt::DisplayRole);
        company = varCompany.toString();

        QModelIndex addressIndex = table->index(row, 2, QModelIndex());
        QVariant varNum = table->data(addressIndex, Qt::DisplayRole);
        num = varNum.toString();

        QModelIndex telefonIndex = table->index(row, 3, QModelIndex());
        QVariant varPeriod = table->data(telefonIndex, Qt::DisplayRole);
        period = varPeriod.toString();
    }
//! [4a]

//! [4b]
    AddPolicyDialog aDialog;
    aDialog.setWindowTitle(tr("Edytuj polise"));

    aDialog.typeText->setText(type);
    aDialog.companyText->setText(company);
    aDialog.numText->setText(num);
    aDialog.periodText->setText(period);

    if (aDialog.exec()) {
        QString newType = aDialog.typeText->text();
        if (newType != type) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newType, Qt::EditRole);
        }
        QString newCompany = aDialog.companyText->text();
        if (newCompany != company) {
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newCompany, Qt::EditRole);
        }
        QString newNum = aDialog.numText->text();
        if (newNum != num) {
            QModelIndex index = table->index(row, 2, QModelIndex());
            table->setData(index, newNum, Qt::EditRole);
        }
        QString newPeriod = aDialog.periodText->text();
        if (newPeriod != period) {
            QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newPeriod, Qt::EditRole);
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
