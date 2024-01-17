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
        QPointF connectorStartPosition;
        QPointF connectorEndPosition;
        QString nodeStartID;
        QString nodeEndID;
    };

    enum Role {
        ROLE_CONNECTOR_ID = Qt::UserRole + 1,
        ROLE_CONNECTOR_START_POS,
        ROLE_CONNECTOR_END_POS,
        ROLE_NODE_START_ID,
        ROLE_NODE_END_ID,
    };

    explicit ConnectorListModel(QObject* parent = nullptr, MyDocument *myDocument = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


public slots:
    void handleConnectorListUpdated(std::map<int, std::shared_ptr<Misc::XMLConnector> > updatedNodeList);
    void handleClearConnectors();

private:
    std::vector<ConnectorListItem> _connectorList;
};

}

#endif // CONNECTORLISTMODEL_H
