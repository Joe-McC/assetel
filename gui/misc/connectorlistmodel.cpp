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
    std::cout << "ConnectorListModel::data : " <<  std::endl;
    if (!index.isValid() || index.row() >= _connectorList.size())
        return QVariant();

    const ConnectorListItem& listItem = _connectorList.at(index.row());

    switch (role) {
    case ROLE_CONNECTOR_ID:
        std::cout << "ConnectorListModel::data listItem.connectorUID: " << listItem.connectorUID.toStdString() << std::endl;
        return QVariant(listItem.connectorUID);
    case ROLE_CONNECTOR_START_POS_X:
        return QVariant(listItem.connectorStartPositionX);
    case ROLE_CONNECTOR_START_POS_Y:
        return QVariant(listItem.connectorStartPositionY);
    case ROLE_CONNECTOR_END_POS_X:
        return QVariant(listItem.connectorEndPositionX);
    case ROLE_CONNECTOR_END_POS_Y:
        return QVariant(listItem.connectorEndPositionY);
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
    roles[ROLE_CONNECTOR_START_POS_X] = "connectorStartPosX";
    roles[ROLE_CONNECTOR_START_POS_Y] = "connectorStartPosY";
    roles[ROLE_CONNECTOR_END_POS_X] = "connectorEndPosX";
    roles[ROLE_CONNECTOR_END_POS_Y] = "connectorEndPosY";
    roles[ROLE_NODE_START_ID] = "nodeStartID";
    roles[ROLE_NODE_END_ID] = "nodeEndID";
    return roles;
}

void ConnectorListModel::handleConnectorListUpdated(std::map<int, std::shared_ptr<Misc::XMLConnector>> updatedConnectorList)
{
    std::cout << "ConnectorListModel::handleConnectorListUpdated updatedConnectorList.size(): " << updatedConnectorList.size() << std::endl;

    for (const auto& entry : updatedConnectorList) {
        const auto& connector = entry.second;

        // Check if all necessary data is available
        if (connector->getConnectorUID().isEmpty() ||
            connector->getConnectorXPositionStart().isEmpty() ||
            connector->getConnectorYPositionStart().isEmpty() ||
            connector->getConnectorXPositionEnd().isEmpty() ||
            connector->getConnectorYPositionEnd().isEmpty()) {
            // Skip adding this connector as it lacks necessary data
            continue;
        }

        // Add the updated connector to _connectorList
        beginInsertRows(QModelIndex(), _connectorList.size(), _connectorList.size());
        ConnectorListItem listItem;
        listItem.connectorUID = connector->getConnectorUID();
        listItem.connectorStartPositionX = connector->getConnectorXPositionStart();
        listItem.connectorStartPositionY = connector->getConnectorYPositionStart();
        listItem.connectorEndPositionX = connector->getConnectorXPositionEnd();
        listItem.connectorEndPositionY = connector->getConnectorYPositionEnd();
        listItem.nodeStartID = connector->getNodeStartID();
        listItem.nodeEndID = connector->getNodeEndID();

        // Output debug information
        std::cout << "listItem.connectorUID : " << listItem.connectorUID.toStdString() << std::endl;
        std::cout << "listItem.connectorStartPositionX : " << listItem.connectorStartPositionX.toStdString() << std::endl;
        std::cout << "listItem.connectorStartPositionY : " << listItem.connectorStartPositionY.toStdString() << std::endl;
        std::cout << "listItem.connectorEndPositionX : " << listItem.connectorEndPositionX.toStdString() << std::endl;
        std::cout << "listItem.connectorEndPositionY : " << listItem.connectorEndPositionY.toStdString() << std::endl;
        std::cout << "listItem.nodeStartID : " << listItem.nodeStartID.toStdString() << std::endl;
        std::cout << "listItem.nodeEndID : " << listItem.nodeEndID.toStdString() << std::endl;

        _connectorList.push_back(listItem);
        endInsertRows();

        emit modelPopulated();
    }
}

void ConnectorListModel::handleClearConnectors() {
    std::cout << "ConnectorListModel::handleClearConnectors : " << std::endl;
    beginResetModel();
    _connectorList.clear();
    endResetModel();
}

}
