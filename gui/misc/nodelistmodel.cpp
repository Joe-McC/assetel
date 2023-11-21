#include "nodelistmodel.h"

namespace Misc
{

NodeListModel::NodeListModel(QObject *parent, MyDocument *myDocument)
    : QAbstractListModel(parent)
{
    connect(myDocument, &MyDocument::nodeListUpdated, this, &NodeListModel::handleNodeListUpdated);
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

void NodeListModel::handleNodeListUpdated(std::map<int, std::shared_ptr<XMLNode>> updatedNodeList)
{
    std::cout << "NodeListModel::handleNodeListUpdated updatedNodeList.size(): " << updatedNodeList.size() << std::endl;
    //_nodeList.clear();
    for (const auto& entry : updatedNodeList) {
        beginResetModel();
        const auto& node = entry.second; // shared_ptr to XMLNode

        NodeListItem listItem;
        listItem.nodeTitle = node->getNodeTitle();
        listItem.nodeText = node->getNodeText();
        listItem.nodeParentID = node->getNodeParentID();
        listItem.nodeUID = node->getNodeUID();
        listItem.nodeXPosition = node->getNodeXPosition();
        listItem.nodeYPosition = node->getNodeYPosition();
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeTitle: " << listItem.nodeTitle.toStdString() << std::endl;
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeText: " << listItem.nodeText.toStdString()  << std::endl;
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeParentID: " << listItem.nodeParentID.toStdString()  << std::endl;
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeUID: " << listItem.nodeUID.toStdString()  << std::endl;
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeXPosition: " << listItem.nodeXPosition.toStdString() << std::endl;
        std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeYPosition: " << listItem.nodeYPosition.toStdString() << std::endl;
        //std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeXPosition  STRING: " << node->getNodeXPosition().toStdString() << std::endl;
        //std::cout << "NodeListModel::handleNodeListUpdated listItem.nodeYPosition STRING: " << node->getNodeYPosition().toStdString() << std::endl;

        _nodeList.push_back(listItem);
        endResetModel();
    }
}

}
