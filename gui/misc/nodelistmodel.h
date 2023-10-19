#ifndef NODELISTMODEL_H
#define NODELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "xmlnode.h"
#include "mydocument.h"

namespace Misc
{

class NodeListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct NodeListItem {
        QString nodeTitle;
        QString nodeText;
        QString nodeParentID;
        QString nodeUID;
        int nodeXPosition;
        int nodeYPosition;
    };

    Q_PROPERTY(QString nodeTitle READ getNodeTitle WRITE setNodeTitle NOTIFY nodeTitleChanged)
    Q_PROPERTY(QString nodeText READ getNodeText WRITE setNodeText NOTIFY nodeTextChanged)
    Q_PROPERTY(QString nodeParentID READ getNodeParentID WRITE setNodeParentID NOTIFY nodeParentIDChanged)
    Q_PROPERTY(QString nodeUID READ getNodeUID WRITE setNodeUID NOTIFY nodeUIDChanged)
    Q_PROPERTY(QString nodeXPosition READ getNodeXPosition WRITE setNodeXPosition NOTIFY nodeXPositionChanged)
    Q_PROPERTY(QString nodeYPosition READ getNodeYPosition WRITE setNodeYPosition NOTIFY nodeYPositionChanged)


    enum Role {
        ROLE_NODE_TITLE = Qt::UserRole + 1,
        ROLE_NODE_TEXT,
        ROLE_PARENT_ID,
        ROLE_NODE_UID,
        ROLE_NODE_X_POSITION,
        ROLE_NODE_Y_POSITION,
    };

    NodeListModel(QObject* parent = nullptr, MyDocument *myDocument);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<XMLNode> items() const;
    void setItems(const QList<XMLNode> &items);

private:
    QList<XMLNode> m_nodes;
};

}

#endif // NODELISTMODEL_H
