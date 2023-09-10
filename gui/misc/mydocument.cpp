#include "mydocument.h"

/**
 * Returns the only instance of the class, this is to be used by the QML interface
 */

Misc::MyDocument &Misc::MyDocument::getInstance()
{
    static MyDocument instance;

    return instance;
}

void Misc::MyDocument::openDocument(const QString &filename)
{
    QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);
    std::cout << "Misc::MyDocument::openDocument filename: " << filenameModified.toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }
    return;
}

void Misc::MyDocument::saveDocument(const QString &filename)
{
    // don't think this is needed as we just need to open a file and write to it, so it's the same as opening a doc????
    /*QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);
    _XMLfilename.
    std::cout << "Misc::MyDocument::save filename: " << filenameModified.toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }
    return;*/
}




QString Misc::MyDocument::addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId)
{
    _uid++;//  ::_uidCount++;
    auto nodePtr = std::shared_ptr<Misc::XMLNode>(new Misc::XMLNode());

    QString uidQString = getUIDQString();

    // Check if a parent node ID is provided
    if (!parentNodeId.isEmpty())
    {
        // Add the new node as a child of the parent node
        auto parentNode = _nodeLookup.find(parentNodeId.toInt());

        if (parentNode != _nodeLookup.end())
        {
            parentNode->second->addChild(nodeTitle);
        }
        emit childNodeAdded(_uid, nodeTitle.toStdString(), parentNodeId.toInt());
    }
    else
    {
        std::cout << "emit TopLevelNodeAdded: " << _uid << std::endl;
        emit topLevelNodeAdded(_uid, nodeTitle.toStdString());
    }
    Misc::MyDocument::_nodeLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(_uid, nodePtr));

    //node.setNodeText(nodeText);
    //node.setNodeTitle(nodeTitle);
    nodePtr->setNodeTitle(nodeTitle);

    return uidQString;
}

QList<QObject*> Misc::MyDocument::getNodesForQml() {
    QList<QObject*> qmlNodes;
    for (const auto& entry : _nodeLookup) {
        QObject* qmlNode = new QObject(this);
        qmlNode->setProperty("nodeTitle", entry.second->getNodeTitle()); // Replace with actual property name
        qmlNode->setProperty("nodeText", entry.second->getNodeText());   // Replace with actual property name
        qmlNodes.append(qmlNode);
    }
    return qmlNodes;
}


QString Misc::MyDocument::getUIDQString()
{
   std::string uid = std::to_string(_uid);
   const int num = 3;

   if(uid.size() < num)
   {
       uid.insert(0, num - uid.size(), '0');
   }
   return QString::fromStdString(uid);
}
