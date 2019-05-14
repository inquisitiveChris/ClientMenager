#ifndef POLICYWIDGET_H
#define POLICYWIDGET_H

#include "newpolicytab.h"
#include "policytablemodel.h"

#include <QItemSelection>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

class PolicyWidget:public QTabWidget
{
    Q_OBJECT

public:
    PolicyWidget(QWidget *parent = nullptr);
    ~PolicyWidget();
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(QString type, QString company, QString num, QString period_from, QString period_to);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void setupTabs();

    PolicyTableModel *table;
    NewPolicyTab *newPolicyTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // POLICYWIDGET_H
