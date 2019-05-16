#ifndef POLICYTABLEMODEL_H
#define POLICYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "cypher.h"

struct Policy
{
    QString type;
    QString company;
    QString num;
    QString period_from;
    QString period_to;
    QString client_id;
    QString payment_from;

    bool operator==(const Policy &other) const
    {
        return type == other.type && company == other.company
               && num == other.num && period_from == other.period_from
               && period_to == other.period_to && client_id == other.client_id
               && payment_from == other.payment_from;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Policy &policy)
{
    return stream << enc(policy.type) << enc(policy.company)
                  << enc(policy.num) << enc(policy.period_from) << enc(policy.period_to)
                  << enc(policy.client_id)<< enc(policy.payment_from);
}

inline QDataStream &operator>>(QDataStream &stream, Policy &policy)
{

    struct Policy epolicy;

    QDataStream &st =
        stream >> epolicy.type >> epolicy.company >>
                  epolicy.num >> epolicy.period_from >>
                  epolicy.period_to >> epolicy.client_id >>
                  epolicy.payment_from;

    policy.type = dec(epolicy.type);
    policy.company = dec(epolicy.company);
    policy.num = dec(epolicy.num);
    policy.period_from = dec(epolicy.period_from);
    policy.period_to = dec(epolicy.period_to);
    policy.client_id = dec(epolicy.client_id);
    policy.payment_from = dec(epolicy.payment_from);
    return st;
 }


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
