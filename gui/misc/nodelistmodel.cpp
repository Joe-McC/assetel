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

int NodeListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_nodes->count();
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_nodes->count())
        return QVariant();

    const XMLNode* i = m_nodes->at(index.row());

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
        XMLNode* node = entry.second.get();
        m_nodes->append(node);
    }


}


}
