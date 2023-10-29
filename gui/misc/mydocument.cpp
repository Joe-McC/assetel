#include "mydocument.h"
#include <QQmlApplicationEngine>


namespace Misc
{
/*Misc::MyDocument &Misc::MyDocument::getInstance()
{
    static MyDocument instance;

    return instance;
}*/

MyDocument::MyDocument(QQmlApplicationEngine& engine):
    _engine(&engine)
{
}

void MyDocument::openDocument(const QString &filename)
{
    std::cout << "MyDocument::openDocument \n";


    QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);
    _XMLprocessor.setFilename(_XMLfilename);

    // Loads saved nodes using XMLProcessor and sends signals to NodeListModel, which sends the data to qml.
    getNodes();

    return;
}

void MyDocument::saveDocument(const QString &filename)
{
    QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);
    _XMLprocessor.setFilename(_XMLfilename);
    _XMLprocessor.writeNodes(_nodeLookup);  // MAYBE PASS A VECTOR OF NODES AND WRITE THEM ALL?
}

void MyDocument::saveDocument()
{
    //_XMLprocessor.writeNodes();  -- MAYBE PASS A VECTOR OF NODES AND WRITE THEM ALL?
}

QString MyDocument::getFilename() {
    return _XMLfilename.fileName();
}

QString MyDocument::addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId)
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
    _nodeLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(_uid, nodePtr));

    nodePtr->setNodeTitle(nodeTitle);
    nodePtr->setNodeText(nodeText);
    nodePtr->setNodeParentID(parentNodeId);
    nodePtr->setNodeUID(uidQString);


    return uidQString;
}

void MyDocument::setNewNodeXPos (const QString &uid, const QString &nodeXPosition)
{
     auto nodeEntry = _nodeLookup.find(uid.toInt());
     nodeEntry->second->setNodeXPosition(nodeXPosition);
}

void MyDocument::setNewNodeYPos (const QString &uid, const QString &nodeYPosition)
{
    auto nodeEntry = _nodeLookup.find(uid.toInt());
    nodeEntry->second->setNodeYPosition(nodeYPosition);
}

void MyDocument::getNodes() {
    std::cout << "MyDocument::getNodesForQml() - called from projectviewer.qml repeater" << "std::endl() \n";

    _nodeLookup = _XMLprocessor.getNodes(_engine);

    emit nodeListUpdated(_nodeLookup);
}
QString MyDocument::getUIDQString()
{
   std::string uid = std::to_string(_uid);
   const int num = 3;

   if(uid.size() < num)
   {
       uid.insert(0, num - uid.size(), '0');
   }
   return QString::fromStdString(uid);
}

}
