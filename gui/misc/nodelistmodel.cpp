#include "nodelistmodel.h"

// see https://forum.qt.io/topic/89567/help-with-model-for-repeater/2

namespace Misc
{

NodeListModel::NodeListModel(QObject *parent, MyDocument *myDocument)
    : QAbstractListModel(parent)
{
    connect(myDocument, &MyDocument::nodeListUpdated, this, &NodeListModel::handleNodeListUpdated);
    qDebug() << "myDocument: " << myDocument;
    qDebug() << "nodeListModel: " << this;
}


int NodeListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _nodeList.size();
}

QVariant NodeListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= _nodeList.size())
        return QVariant();

    const NodeListItem& listItem = _nodeList.at(index.row());

    switch (role) {
    case ROLE_NODE_TITLE:
        return QVariant(listItem.nodeTitle);
    case ROLE_NODE_TEXT:
        return QVariant(listItem.nodeText);
    case ROLE_PARENT_ID:
        return QVariant(listItem.nodeParentID);
    case ROLE_NODE_UID:
        return QVariant(listItem.nodeUID);
    case ROLE_NODE_X_POSITION:
        return QVariant(listItem.nodeXPosition);
    case ROLE_NODE_Y_POSITION:
        return QVariant(listItem.nodeYPosition);
    }

    return QVariant();
}

QHash<int, QByteArray> NodeListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLE_NODE_TITLE] = "nodeTitle";
    roles[ROLE_NODE_TEXT] = "nodeText";
    roles[ROLE_PARENT_ID] = "nodeParentID";
    roles[ROLE_NODE_UID] = "nodeUID";
    roles[ROLE_NODE_X_POSITION] = "nodeXPosition";
    roles[ROLE_NODE_Y_POSITION] = "nodeYPosition";
    return roles;
}

/*void NodeListModel::setNodeList(const QVector<NodeListItem>& nodeList)
{
    beginResetModel();
    _nodeList = nodeList;
    endResetModel();
}*/

void NodeListModel::handleNodeListUpdated(std::map<int, std::shared_ptr<XMLNode>> updatedNodeList)
{
    //QList<XMLNode*> qmlNodes;
    /*for (const auto entry : updatedNodeList) {
        //qmlNodes.append(entry.second.get());
        //m_nodes.append(entry.second.get());
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        XMLNode* node = entry.second.get();
        m_nodes->append(node);
        endInsertRows();
    }*/

    for (const auto& entry : updatedNodeList) {
        beginResetModel();
        const auto& node = entry.second; // shared_ptr to XMLNode

        NodeListItem listItem;
        listItem.nodeTitle = node->getNodeTitle();
        listItem.nodeText = node->getNodeText();
        listItem.nodeParentID = node->getNodeParentID();
        listItem.nodeUID = node->getNodeUID();
        listItem.nodeXPosition = node->getNodeXPosition().toInt();
        listItem.nodeYPosition = node->getNodeYPosition().toInt();

        _nodeList.push_back(listItem);
        endResetModel();
    }


}
/*
int NodeListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    //return m_nodes->count()
    return _nodeList.size();
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_nodes->count())
        return QVariant();

    const XMLNode* i = m_nodes->at(index.row());
    //const NodeListItem _nodeList.
    switch(role){

    case ROLE_NODE_TITLE: return i->_nodeTitle;
    case ROLE_NODE_TEXT: return i->_nodeText;
    case ROLE_PARENT_ID: return i->_nodeParentID;
    case ROLE_NODE_UID: return i->_nodeUID;
    case ROLE_NODE_X_POSITION: return i->_nodeXPosition;
    case ROLE_NODE_Y_POSITION: return i->_nodeYPosition;;

    }

    return QVariant();
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= _nodeList.count())
        return QVariant();

    const NodeListItem& listItem = _nodeList.at(index.row());

    switch (role) {
    case ROLE_NODE_TITLE:
        return QVariant(listItem.nodeTitle);
    case ROLE_NODE_TEXT:
        return QVariant(listItem.nodeText);
    case ROLE_PARENT_ID:
        return QVariant(listItem.nodeParentID);
    case ROLE_NODE_UID:
        return QVariant(listItem.nodeUID);
    case ROLE_NODE_X_POSITION:
        return QVariant(listItem.nodeXPosition);
    case ROLE_NODE_Y_POSITION:
        return QVariant(listItem.nodeYPosition);
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

QList<XMLNode*> NodeListModel::items() const
{
    return *m_nodes;
}

void NodeListModel::handleNodeListUpdated(std::map<int, std::shared_ptr<XMLNode>> updatedNodeList)
{
    //QList<XMLNode*> qmlNodes;
    for (const auto entry : updatedNodeList) {
        //qmlNodes.append(entry.second.get());
        //m_nodes.append(entry.second.get());
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        XMLNode* node = entry.second.get();
        m_nodes->append(node);
        endInsertRows();
    }

    for (const auto& entry : updatedNodeList) {
        const auto& node = entry.second; // shared_ptr to XMLNode

        NodeListItem listItem;
        listItem.nodeTitle = node->getNodeTitle();
        listItem.nodeText = node->getNodeText();
        listItem.nodeParentID = node->getNodeParentID();
        listItem.nodeUID = node->getNodeUID();
        listItem.nodeXPosition = node->getNodeXPosition().toInt();
        listItem.nodeYPosition = node->getNodeYPosition().toInt();

        _nodeList.push_back(listItem);
    }


}*/


}
