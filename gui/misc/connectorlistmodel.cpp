#include "connectorlistmodel.h"

namespace Misc
{

ConnectorListModel::ConnectorListModel(QObject *parent, MyDocument *myDocument)
    : QAbstractListModel(parent)
{
    connect(myDocument, &MyDocument::connectorListUpdated, this, &ConnectorListModel::handleConnectorListUpdated);
    connect(myDocument, &MyDocument::clearConnectors, this, &ConnectorListModel::handleClearConnectors);
}


int ConnectorListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _connectorList.size();
}

QVariant ConnectorListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= _connectorList.size())
        return QVariant();

    const ConnectorListItem& listItem = _connectorList.at(index.row());

    switch (role) {
    case ROLE_CONNECTOR_ID:
        return QVariant(listItem.connectorUID);
    case ROLE_CONNECTOR_X_POS:
        return QVariant(listItem.connectorXPosition);
    case ROLE_CONNECTOR_Y_POS:
        return QVariant(listItem.connectorYPosition);
    case ROLE_NODE_START_ID:
        return QVariant(listItem.nodeStartID);
    case ROLE_NODE_END_ID:
        return QVariant(listItem.nodeEndID);
    }
    return QVariant();
}

QHash<int, QByteArray> ConnectorListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLE_CONNECTOR_ID] = "connectorID";
    roles[ROLE_CONNECTOR_X_POS] = "connectorXPos";
    roles[ROLE_CONNECTOR_Y_POS] = "connectorYPos";
    roles[ROLE_NODE_START_ID] = "nodeStartID";
    roles[ROLE_NODE_END_ID] = "nodeEndID";
    return roles;
}

void ConnectorListModel::handleConnectorListUpdated(std::map<int, std::shared_ptr<XMLConnector>> updatedNodeList)
{
    std::cout << "NodeListModel::handleNodeListUpdated updatedNodeList.size(): " << updatedNodeList.size() << std::endl;

    for (const auto& entry : updatedNodeList) {
        const auto& connector = entry.second; // shared_ptr to XMLNode

        // Check if a node with the same UID already exists in _nodeList
        auto existingNodeIter = std::find_if(_connectorList.begin(), _connectorList.end(),
            [&connector](const ConnectorListItem& listItem) {
                return listItem.connectorUID == connector->getConnectorUID();
            });

        if (existingNodeIter != _connectorList.end()) {
            // Node with the same UID exists, remove it
            int index = std::distance(_connectorList.begin(), existingNodeIter);
            beginRemoveRows(QModelIndex(), index, index);
            _connectorList.erase(existingNodeIter);
            endRemoveRows();
        }

        // Add the updated node to _nodeList
        beginInsertRows(QModelIndex(), _connectorList.size(), _connectorList.size());
        ConnectorListItem listItem;
        listItem.connectorUID = connector->getConnectorUID();
        listItem.connectorXPosition = connector->getConnectorXPosition();
        listItem.connectorYPosition = connector->getConnectorYPosition();
        listItem.nodeStartID = connector->getNodeStartID();
        listItem.nodeEndID = connector->getNodeEndID();
        _connectorList.push_back(listItem);
        endInsertRows();
    }
}

void ConnectorListModel::handleClearConnectors() {
    std::cout << "ConnectorListModel::handleClearConnectors : " << std::endl;
    beginResetModel();
    _connectorList.clear();
    endResetModel();
}

}
