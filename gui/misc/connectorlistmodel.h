#ifndef CONNECTORLISTMODEL_H
#define CONNECTORLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "mydocument.h"
#include "xmlconnector.h"

namespace Misc
{

class ConnectorListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct ConnectorListItem {
        QString connectorUID;
        QString connectorXPosition;
        QString connectorYPosition;
        QString nodeStartID;
        QString nodeEndID;
    };

    enum Role {
        ROLE_CONNECTOR_ID = Qt::UserRole + 1,
        ROLE_CONNECTOR_X_POS,
        ROLE_CONNECTOR_Y_POS,
        ROLE_NODE_START_ID,
        ROLE_NODE_END_ID,
    };

    explicit ConnectorListModel(QObject* parent = nullptr, MyDocument *myDocument = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


public slots:
    void handleConnectorListUpdated(std::map<int, std::shared_ptr<XMLConnector> > updatedNodeList);
    void handleClearConnectors();

private:
    std::vector<ConnectorListItem> _connectorList;
};

}

#endif // CONNECTORLISTMODEL_H
