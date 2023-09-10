#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "xmlnode.h"

namespace Misc
{

class MyDocument : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???

public:
    static MyDocument &getInstance();
    //explicit MyDocument(QObject *parent = nullptr)

    std::map<int, std::shared_ptr<XMLNode>> _nodeLookup;;

    Q_INVOKABLE void openDocument(const QString &filename);
    Q_INVOKABLE void saveDocument(const QString &filename);
    Q_INVOKABLE QString addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId = "");    
    Q_INVOKABLE QList<QObject*> getNodesForQml();

Q_SIGNALS:
    void topLevelNodeAdded(const int &nodeId, const std::string &nodeTitle);
    void childNodeAdded(const int &nodeId, const std::string &nodeTitle, const int &parentNodeId);
//protected:
//    QString

private:

    inline static int _uid;
    inline static QFile _XMLfilename;

    QString getUIDQString();
};


}
#endif // MYDOCUMENT_H

