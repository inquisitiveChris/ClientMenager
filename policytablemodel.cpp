#include "policytablemodel.h"


PolicyTableModel::PolicyTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

PolicyTableModel::PolicyTableModel(QList<Policy> policies, QObject* parent)
    : QAbstractTableModel (parent)
    , policies(policies)
{
}

int PolicyTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return policies.size();
}
int PolicyTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
}
QVariant PolicyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= policies.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &policy = policies.at(index.row());

        if (index.column() == 0)
            return policy.type;
        else if (index.column() == 1)
            return policy.company;
        else if (index.column() == 2)
            return policy.num;
        else if (index.column() == 3)
            return policy.period_from;
        else if (index.column() == 4)
            return policy.period_to;
        else if (index.column() == 5)
            return policy.client_id;
        else if (index.column() == 6)
            return policy.payment_from;
    }
    return QVariant();
}
QVariant PolicyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Rodzaj ubezpieczenia:");

        case 1:
            return tr("Firma ubezpieczeniowa:");

        case 2:
            return tr("Nr polisy:");

        case 3:
            return tr("Okres ochrony od:");

        case 4:
            return tr("Okres ochrony do:");

        case 5:
            return tr("Identyfikator klienta:");

        case 6:
            return tr("Zapłacono:");

            default:
                return QVariant();
        }
    }
    return QVariant();
}
bool PolicyTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        policies.removeAt(position);

    endRemoveRows();
    return true;
}
bool PolicyTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
       policies.insert(position, { QString(),QString(), QString(), QString(),
                                   QString(), QString(), QString()});

    endInsertRows();
    return true;
}
bool PolicyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto policy = policies.value(row);

        if (index.column() == 0)
            policy.type = value.toString();
        else if (index.column() == 1)
            policy.company = value.toString();
        else if (index.column() == 2)
            policy.num = value.toString();
        else if (index.column() == 3)
            policy.period_from = value.toString();
        else if (index.column() == 4)
            policy.period_to = value.toString();
        else if (index.column() == 5)
            policy.client_id = value.toString();
        else if (index.column() == 6)
            policy.payment_from = value.toString();
        else
            return false;

        policies.replace(row, policy);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}
QList<Policy> PolicyTableModel::getPolicies() const
{
    return policies;
}
