#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "xmlnode.h"
#include "xmlconnector.h"
#include "xmlprocessor.h"
#include <QQmlApplicationEngine>

namespace Misc
{

class MyDocument : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QList<QObject*> nodes READ getNodes CONSTANT)

public:
    MyDocument(QQmlApplicationEngine &engine);

    std::map<int, std::shared_ptr<XMLNode>> _nodeLookup;
    std::map<int, std::shared_ptr<XMLConnector>> _connectorLookup;

    Q_INVOKABLE void openDocument(const QString &filename);
    Q_INVOKABLE void saveDocument(const QString &filename);
    Q_INVOKABLE void saveDocument();
    Q_INVOKABLE void closeDocument();
    Q_INVOKABLE QString getFilename();

    Q_INVOKABLE QString addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId = "");
    Q_INVOKABLE void setNewNodeXandYPos(const QString &uid, const QString &nodeXPosition, const QString &nodeYPosition);

    Q_INVOKABLE QString addConnector();
    //Q_INVOKABLE void updatedXPos(int uid, const qreal xpos1, const qreal xpos2);
    //Q_INVOKABLE void updatedYPos(int uid, const qreal xpos1, const qreal xpos2);

    Q_INVOKABLE void updatedConnectorStartXPos(int uid, const QString &xpos);
    Q_INVOKABLE void updatedConnectorStartYPos(int uid, const QString &ypos);
    Q_INVOKABLE void updatedConnectorEndXPos(int uid, const QString &xpos);
    Q_INVOKABLE void updatedConnectorEndYPos(int uid, const QString &ypos);

    void setNewConnectorStartNode(const QString &uid, const QString &nodeUid);
    void setNewConnectorEndNode(const QString &uid, const QString &nodeUid);

    void setNewConnectorPos(const QString &uid, const QPointF &connectorStartPosition, const QPointF &connectorEndPosition);
    void getNodes();
    void getConnectors();

Q_SIGNALS:
    // Signals emitted to TreeModel
    void topLevelNodeAdded(const int &nodeId, const std::string &nodeTitle);
    void childNodeAdded(const int &nodeId, const std::string &nodeTitle, const int &parentNodeId);
    //Signals emitted to NodeListModel
    void nodeListUpdated(std::map<int, std::shared_ptr<XMLNode> > updatedNodeList);
    void clearNodes();
    //Signals emitted to ConnectorListModel
    void connectorListUpdated(std::map<int, std::shared_ptr<XMLConnector> > updatedNodeList);
    void clearConnectors();


//protected:
//    QString

private:

    QQmlApplicationEngine* _engine;
    inline static int _uid;
    inline static int _connectorUid;
    inline static QFile _XMLfilename;
    inline static XMLProcessor _XMLprocessor;

    QString getUIDQString(int uid_int);
};


}
#endif // MYDOCUMENT_H

