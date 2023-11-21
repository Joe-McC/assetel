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

    _nodeLookup.clear();
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
    _XMLprocessor.writeNodes(_nodeLookup);
}

QString MyDocument::getFilename() {
    return _XMLfilename.fileName();
}

QString MyDocument::addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId)
{
    emit nodeListUpdated(_nodeLookup);
    _uid++;//  ::_uidCount++;
    auto nodePtr = std::shared_ptr<Misc::XMLNode>(new Misc::XMLNode());

    QString uidQString = getUIDQString();

    // Check if a parent node ID is provided
    if (!parentNodeId.isEmpty())
    {
        std::cout << "MyDocument::addNode emit childNodeAdded: " << _uid << std::endl;
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

    nodePtr->setNodeTitle(nodeTitle);
    nodePtr->setNodeText(nodeText);
    nodePtr->setNodeParentID(parentNodeId);
    nodePtr->setNodeUID(uidQString);

    _nodeLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(_uid, nodePtr));

    //emit nodeListUpdated(_nodeLookup);

    return uidQString;
}

void MyDocument::setNewNodeXPos (const QString &uid, const QString &nodeXPosition)
{
     auto nodeEntry = _nodeLookup.find(uid.toInt());
     nodeEntry->second->setNodeXPosition(nodeXPosition);
     std::cout << "MyDocument::setNewNodePos nodeXPosition:  " << nodeXPosition.toStdString() << std::endl;

       std::cout << "MyDocument::setNewNodePos _nodeXPosition:  " << nodeEntry->second->_nodeXPosition.toStdString() << std::endl;
         std::cout << "MyDocument::setNewNodePos getNodeXPosition():  " << nodeEntry->second->getNodeXPosition().toStdString() << std::endl;
     //emit nodeListUpdated(_nodeLookup);
}

void MyDocument::setNewNodeYPos (const QString &uid, const QString &nodeYPosition)
{
    std::cout << "MyDocument::setNewNodeYPos uid:  " << uid.toStdString() << std::endl;
    auto nodeEntry = _nodeLookup.find(uid.toInt());
    nodeEntry->second->setNodeYPosition(nodeYPosition);
    std::cout << "MyDocument::setNewNodeYPos nodeYPosition:  " << nodeYPosition.toStdString() << std::endl;
    emit nodeListUpdated(_nodeLookup);
}

void MyDocument::getNodes() {
    std::cout << "MyDocument::getNodes() - called when loading" << "std::endl() \n";

    _nodeLookup = _XMLprocessor.getNodes(_engine);

    for (auto const& nodeEntry : _nodeLookup)
    {
        QString title = nodeEntry.second->getNodeTitle();
        QString text = nodeEntry.second->getNodeText();
        QString uid = nodeEntry.second->getNodeUID();
        QString parentid = nodeEntry.second->getNodeParentID();
        QString xpos = nodeEntry.second->getNodeXPosition();
        QString ypos = nodeEntry.second->getNodeYPosition();

        addNode(title, text, parentid);
        setNewNodeXPos(uid, xpos);
        setNewNodeYPos(uid, ypos);
    }
    //emit nodeListUpdated(_nodeLookup);
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
