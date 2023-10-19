#include "nodelistmodel.h"
#include "xmlprocessor.h"

namespace Misc
{

NodeListModel::NodeListModel(QObject *parent, MyDocument *myDocument)
    : QAbstractListModel(parent)
{
    connect(myDocument, &MyDocument::nodeListUpdated, this, &NodeListModel::handleNodeListUpdated);
}

int NodeListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_nodes.count();
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_nodes.count())
        return QVariant();

    XMLNode i = m_nodes.at(index.row());

    switch(role){

    case ROLE_NODE_TITLE: return i.getNodeTitle();
    case ROLE_NODE_TEXT: return i.getNodeText();
    case ROLE_PARENT_ID: return i.getNodeParentID();
    case ROLE_NODE_UID: return i.getNodeUID();
    case ROLE_NODE_X_POSITION: return i.getNodeXPosition();
    case ROLE_NODE_Y_POSITION: return i.getNodeYPosition();

    }

    return QVariant();
}

QHash<int, QByteArray> NodeListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLE_NODE_TITLE] = "role_nodeTitle";
    roles[ROLE_NODE_TEXT] = "role_nodeText";
    roles[ROLE_PARENT_ID] = "role_parentID";
    roles[ROLE_NODE_UID] = "role_nodeUID";
    roles[ROLE_NODE_X_POSITION] = "role_nodeXPos";
    roles[ROLE_NODE_Y_POSITION] = "role_nodeYPos";
    return roles;
}

QList<XMLNode> NodeListModel::items() const
{
    return m_nodes;
}

void NodeListModel::setItems(const QList<XMLNode> &items)
{
    _nodeLookup = _XMLprocessor.getNodes(_engine);

    QList<XMLNode*> qmlNodes;
    for (const auto& entry : _nodeLookup) {
        XMLNode* qmlNode = new XMLNode();

        qmlNode->setNodeTitle(entry.second->getNodeTitle());
        qmlNode->setNodeText(entry.second->getNodeText());
        qmlNode->setNodeUID(entry.second->getNodeUID());
        qmlNode->setNodeParentID(entry.second->getNodeParentID());
        qmlNode->setNodeXPosition(entry.second->getNodeXPosition());
        qmlNode->setNodeXPosition(entry.second->getNodeYPosition());
        qmlNodes.append(qmlNode);
    }

    beginResetModel();
    m_nodes = items;
    endResetModel();
}

}
