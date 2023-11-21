#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "xmlnode.h"
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

    Q_INVOKABLE void openDocument(const QString &filename);
    Q_INVOKABLE void saveDocument(const QString &filename);
    Q_INVOKABLE void saveDocument();
    Q_INVOKABLE QString getFilename();
    Q_INVOKABLE QString addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId = "");
    Q_INVOKABLE void setNewNodeXPos(const QString &uid, const QString &nodeXPosition);
    Q_INVOKABLE void setNewNodeYPos(const QString &uid, const QString &nodeYPosition);
    //Q_INVOKABLE QList<QObject*> getNodesForQml();

    void getNodes();

Q_SIGNALS:
    // Signals emitted to TreeModel
    void topLevelNodeAdded(const int &nodeId, const std::string &nodeTitle);
    void childNodeAdded(const int &nodeId, const std::string &nodeTitle, const int &parentNodeId);
    //Signals emitted to NodeListModel
    void nodeListUpdated(std::map<int, std::shared_ptr<XMLNode> > updatedNodeList);


//protected:
//    QString

private:

    QQmlApplicationEngine* _engine;
    inline static int _uid;
    inline static QFile _XMLfilename;
    inline static XMLProcessor _XMLprocessor;

    QString getUIDQString();
};


}
#endif // MYDOCUMENT_H

