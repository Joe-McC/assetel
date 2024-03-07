#include "mydocument.h"
#include <QQmlApplicationEngine>


namespace Misc
{

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
    getConnectors();

    //return;
}

void MyDocument::saveDocument(const QString &filename)
{
    QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);
    _XMLprocessor.setFilename(_XMLfilename);
    _XMLprocessor.writeNodes(_nodeLookup);

    auto connectorEntry = _connectorLookup.find(_connectorUid);

    _connectorLookup.emplace(_connectorUid, connectorEntry->second);

    _XMLprocessor.writeConnectors(_connectorLookup);
    _XMLprocessor.closeDocument();
}

void MyDocument::saveDocument()
{
    _XMLprocessor.writeNodes(_nodeLookup);

    auto connectorEntry = _connectorLookup.find(_connectorUid);

    _connectorLookup.emplace(_connectorUid, connectorEntry->second);

    _XMLprocessor.writeConnectors(_connectorLookup);
    _XMLprocessor.closeDocument();
}

void MyDocument::closeDocument()
{
    _nodeLookup.clear();
    emit clearNodes();
}


QString MyDocument::getFilename() {
    return _XMLfilename.fileName();
}

QString MyDocument::addNode(const QString &nodeTitle, const QString &nodeText, const QString& parentNodeId)
{
    emit nodeListUpdated(_nodeLookup);
    _uid++;//  ::_uidCount++;
    auto nodePtr = std::shared_ptr<Misc::XMLNode>(new Misc::XMLNode());

    QString uidQString = getUIDQString(_uid);

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

    emit nodeListUpdated(_nodeLookup);

    return uidQString;
}

void MyDocument::setNewNodeXandYPos(const QString &uid, const QString &nodeXPosition, const QString &nodeYPosition)
{
     auto nodeEntry = _nodeLookup.find(uid.toInt());
     nodeEntry->second->setNodeXPosition(nodeXPosition);
     nodeEntry->second->setNodeYPosition(nodeYPosition);
     std::cout << "MyDocument::setNewNodePos nodeXPosition:  " << nodeXPosition.toStdString() << std::endl;

     //std::cout << "MyDocument::setNewNodePos _nodeXPosition:  " << nodeEntry->second->_nodeXPosition.toStdString() << std::endl;
     //std::cout << "MyDocument::setNewNodePos getNodeXPosition():  " << nodeEntry->second->getNodeXPosition().toStdString() << std::endl;
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
        setNewNodeXandYPos(uid, xpos, ypos);
    }
}

void MyDocument::getConnectors() {
    std::cout << "MyDocument::getConnectors() - called when loading" << std::endl;

    _connectorLookup = _XMLprocessor.getConnectors(_engine);

    for (auto const& connectorEntry : _connectorLookup)
    {
        QString connectorXPositionStart = connectorEntry.second->getConnectorXPositionStart();
        QString connectorYPositionStart = connectorEntry.second->getConnectorYPositionStart();
        QString connectorXPositionEnd = connectorEntry.second->getConnectorXPositionEnd();
        QString connectorYPositionEnd = connectorEntry.second->getConnectorYPositionEnd();
        QString connectorUID = connectorEntry.second->getConnectorUID();
        QString nodeStartID = connectorEntry.second->getNodeStartID();
        QString nodeEndID = connectorEntry.second->getNodeEndID();

        auto connectorPtr = std::shared_ptr< Misc::XMLConnector>(new Misc::XMLConnector());

        connectorPtr->setConnectorUID(connectorUID);
        _connectorLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLConnector>>(_connectorUid, connectorPtr));

        updatedConnectorStartXPos(connectorUID.toInt(), connectorXPositionStart);
        updatedConnectorStartYPos(connectorUID.toInt(), connectorYPositionStart);
        updatedConnectorEndXPos(connectorUID.toInt(), connectorXPositionEnd);
        updatedConnectorEndYPos(connectorUID.toInt(), connectorYPositionEnd);
        setNewConnectorStartNode(connectorUID.toInt(), nodeStartID);
        setNewConnectorEndNode(connectorUID.toInt(), nodeEndID);

        emit connectorListUpdated(_connectorLookup);
    }
}

QString MyDocument::getUIDQString(int uid_int)
{
   std::string uid = std::to_string(uid_int);
   const int num = 3;

   if(uid.size() < num)
   {
       uid.insert(0, num - uid.size(), '0');
   }
   return QString::fromStdString(uid);
}

void MyDocument::addConnector(const QString& uid) {
    auto connectorPtr = std::shared_ptr< Misc::XMLConnector>(new Misc::XMLConnector());
    connectorPtr->setConnectorUID(uid);
    _connectorLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLConnector>>(_connectorUid, connectorPtr));

    std::cout << "MyDocument::addConnector emit MyDocument::addConnector " << std::endl;

    emit connectorListUpdated(_connectorLookup);
}

QString MyDocument::addConnector() {
    //emit connectorListUpdated(_connectorLookup);
    _connectorUid++;//  ::_uidCount++;
    auto connectorPtr = std::shared_ptr< Misc::XMLConnector>(new Misc::XMLConnector());

    QString uidQString = getUIDQString(_connectorUid);

    connectorPtr->setConnectorUID(uidQString);
    _connectorLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLConnector>>(_connectorUid, connectorPtr));

    emit connectorListUpdated(_connectorLookup);

    return uidQString;
}


void MyDocument::updatedConnectorStartXPos(int uid, const QString &xpos)
{
    // convert pos end and pos start attributes to startx, starty, endx, endy
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setConnectorXPositionStart(xpos);
    std::cout << "MyDocument::updatedConnectorStartXPos xpos:  " << xpos.toStdString() << ", uid: " << uid << std::endl;
}


void MyDocument::updatedConnectorStartYPos(int uid, const QString &ypos)
{
    // convert pos end and pos start attributes to startx, starty, endx, endy
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setConnectorYPositionStart(ypos);
    std::cout << "MyDocument::updatedConnectorStartYPos xpos:  " << ypos.toStdString() << ", uid: " << uid << std::endl;
}


void MyDocument::updatedConnectorEndXPos(int uid, const QString &xpos)
{
    // convert pos end and pos start attributes to startx, starty, endx, endy
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setConnectorXPositionEnd(xpos);
    std::cout << "MyDocument::updatedConnectorEndXPos xpos:  " << xpos.toStdString() << ", uid: " << uid << std::endl;
}


void MyDocument::updatedConnectorEndYPos(int uid, const QString &ypos)
{
    // convert pos end and pos start attributes to startx, starty, endx, endy
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setConnectorYPositionEnd(ypos);
    std::cout << "MyDocument::updatedConnectorEndYPos ypos:  " << ypos.toStdString() << ", uid: " << uid << std::endl;
}

void MyDocument::setNewConnectorStartNode(int uid, const QString &connectorStartNodeX)
{
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setNodeStartID(connectorStartNodeX);
}

void MyDocument::setNewConnectorEndNode(int uid, const QString &connectorStartNodeY)
{
    auto connectorEntry = _connectorLookup.find(uid);
    connectorEntry->second->setNodeEndID(connectorStartNodeY);
}


}
