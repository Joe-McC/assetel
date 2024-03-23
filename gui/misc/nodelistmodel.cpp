#include "nodelistmodel.h"

namespace Misc
{

NodeListModel::NodeListModel(QObject *parent, MyDocument *myDocument)
    : QAbstractListModel(parent)
{
    connect(myDocument, &MyDocument::nodeListUpdated, this, &NodeListModel::handleNodeListUpdated);
    connect(myDocument, &MyDocument::clearNodes, this, &NodeListModel::handleClearNodes);
}


int NodeListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _nodeList.size();
}

QVariant NodeListModel::data(const QModelIndex& index, int role) const
{
    std::cout << "NodeListModel::data : " <<  std::endl;
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

    for (const auto& entry : updatedNodeList) {
        const auto& node = entry.second; // shared_ptr to XMLNode

        // Check if a node with the same UID already exists in _nodeList
        auto existingNodeIter = std::find_if(_nodeList.begin(), _nodeList.end(),
            [&node](const NodeListItem& listItem) {
                return listItem.nodeUID == node->getNodeUID();
            });

        if (existingNodeIter != _nodeList.end()) {
            // Node with the same UID exists, remove it
            int index = std::distance(_nodeList.begin(), existingNodeIter);
            beginRemoveRows(QModelIndex(), index, index);
            _nodeList.erase(existingNodeIter);
            endRemoveRows();
        }

        // Add the updated node to _nodeList
        beginInsertRows(QModelIndex(), _nodeList.size(), _nodeList.size());
        NodeListItem listItem;
        listItem.nodeTitle = node->getNodeTitle();
        listItem.nodeText = node->getNodeText();
        listItem.nodeParentID = node->getNodeParentID();
        listItem.nodeUID = node->getNodeUID();
        listItem.nodeXPosition = node->getNodeXPosition();
        listItem.nodeYPosition = node->getNodeYPosition();
        _nodeList.push_back(listItem);
        endInsertRows();
    }
}

void NodeListModel::handleClearNodes() {
    std::cout << "NodeListModel::handleClearNodes : " << std::endl;
    beginResetModel();
    _nodeList.clear();
    endResetModel();
}

}
