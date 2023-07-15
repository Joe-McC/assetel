#include "parentsmodel.h"

namespace Misc
{

ParentsModel::ParentsModel(QObject* parent) : QAbstractListModel(parent) {}

void ParentsModel::setParents(const QList<ParentItem>& parents)
{
    beginResetModel();
    m_parents = parents;
    endResetModel();
}

void ParentsModel::addParentItem(const QString& nodeId, const QString& displayText)
{
    beginInsertRows(QModelIndex(), m_parents.size(), m_parents.size());
    m_parents.append({nodeId, displayText});
    endInsertRows();
}

int ParentsModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_parents.size();
}

QVariant ParentsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_parents.size())
        return QVariant();

    const ParentItem& parent = m_parents[index.row()];

    if (role == NodeIdRole)
        return parent.nodeId;
    else if (role == DisplayTextRole)
        return parent.displayText;

    return QVariant();
}

QHash<int, QByteArray> ParentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NodeIdRole] = "nodeId";
    roles[DisplayTextRole] = "displayText";
    return roles;
}
}
