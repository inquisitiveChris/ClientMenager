#ifndef POLICYTABLEMODEL_H
#define POLICYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

struct Policy
{
    QString type;
    QString company;
    QString num;
    QString period;

    bool operator==(const Policy &other) const
    {
        return type == other.type && company == other.company && num == other.num && period == other.period;
    }
};

class PolicyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PolicyTableModel(QObject* parent = nullptr);
    PolicyTableModel(QList<Policy> policies, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Policy> getPolicies() const;

private:
    QList<Policy> policies;
};

#endif // POLICYTABLEMODEL_H
