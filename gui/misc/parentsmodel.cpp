#include "parentsmodel.h"
#include <iostream>

namespace Misc
{

ParentsModel::ParentsModel(QObject* parent) : QAbstractListModel(parent) {
    //addParentItem("1", "Parent 1");
    //addParentItem("2", "Parent 2");

}

void ParentsModel::setParents(const QList<ParentItem>& parents)
{
    beginResetModel();
    m_parents = parents;
    endResetModel();
    emit countChanged(); // Emit countChanged signal when the model is updated
}

void ParentsModel::addParentItem(const QString& nodeId, const QString& displayText)
{
    std::cout << "ParentsModel::addParentItem addParentItem: " << nodeId.toStdString() << std::endl;
    beginInsertRows(QModelIndex(), m_parents.size(), m_parents.size());
    m_parents.append({nodeId, displayText});
    endInsertRows();
    emit countChanged(); // Emit countChanged signal when a new item is added
}

/*void ParentsModel::deleteParentItem(const QString& nodeId)
{
    for (int i = 0; i < m_parents.size(); ++i)
    {
        if (m_parents[i].nodeId == nodeId)
        {
            beginRemoveRows(QModelIndex(), i, i);
            m_parents.removeAt(i);
            endRemoveRows();
            emit countChanged(); // Emit countChanged signal when an item is deleted
            break; // No need to continue searching once the item is found and removed
        }
    }
}*/


int ParentsModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_parents.count();
}


QVariant ParentsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_parents.size())
        return QVariant();

    std::cout << "m_parents.size(): " << m_parents.size() << std::endl;
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

int ParentsModel::count() const
{
    return rowCount();
}

}
