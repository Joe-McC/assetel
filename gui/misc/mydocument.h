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
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE QString addNode(const QString &nodeTitle, const QString& parentNodeId = "");

Q_SIGNALS:
    void topLevelNodeAdded(const int &nodeId, const std::string &nodeTitle);
    void childNodeAdded(const int &nodeId, const std::string &nodeTitle, const int &parentNodeId);
//protected:
//    QString

private:
    inline static std::map<int, std::shared_ptr<XMLNode>> _nodeLookup;
    inline static int _uid;

    QString getUIDQString();


};


}
#endif // MYDOCUMENT_H

