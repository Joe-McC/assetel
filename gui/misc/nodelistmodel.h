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
    /*struct NodeListItem {
        QString nodeTitle;
        QString nodeText;
        QString nodeParentID;
        QString nodeUID;
        int nodeXPosition;
        int nodeYPosition;
    };*/

    enum Role {
        ROLE_NODE_TITLE = Qt::UserRole + 1,
        ROLE_NODE_TEXT,
        ROLE_PARENT_ID,
        ROLE_NODE_UID,
        ROLE_NODE_X_POSITION,
        ROLE_NODE_Y_POSITION,
    };

    explicit NodeListModel(QObject* parent = nullptr, MyDocument *myDocument = nullptr);

    int rowCount(const QModelIndex& node = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<XMLNode*> items() const;
    //void setItems(const QList<XMLNode> &items);


public slots:
    void handleNodeListUpdated(std::map<int, std::shared_ptr<XMLNode> > updatedNodeList);


private:
    //QList<XMLNode*>* m_nodes;
    QList<XMLNode*>* m_nodes = new QList<XMLNode*>;


};

}

#endif // NODELISTMODEL_H
