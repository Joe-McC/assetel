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

void MyDocument::setNewNodeXandYPos (const QString &uid, const QString &nodeXPosition, const QString &nodeYPosition)
{
     auto nodeEntry = _nodeLookup.find(uid.toInt());
     nodeEntry->second->setNodeXPosition(nodeXPosition);
     nodeEntry->second->setNodeYPosition(nodeYPosition);
     std::cout << "MyDocument::setNewNodePos nodeXPosition:  " << nodeXPosition.toStdString() << std::endl;

       std::cout << "MyDocument::setNewNodePos _nodeXPosition:  " << nodeEntry->second->_nodeXPosition.toStdString() << std::endl;
         std::cout << "MyDocument::setNewNodePos getNodeXPosition():  " << nodeEntry->second->getNodeXPosition().toStdString() << std::endl;
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
        //setNewNodeXPos(uid, xpos);
        //setNewNodeYPos(uid, ypos);
    }
    //emit nodeListUpdated(_nodeLookup);
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

QString MyDocument::addConnector() {

    //std::shared_ptr<XMLConnector> > updatedNodeList
    emit connectorListUpdated(_connectorLookup);
    _connectorUid++;//  ::_uidCount++;
    auto connectorPtr = std::shared_ptr< Misc::XMLConnector>(new Misc::XMLConnector());

    QString uidQString = getUIDQString(_connectorUid);


    /*Q_PROPERTY(QString connectorUID READ getConnectorUID WRITE setConnectorUID NOTIFY connectorUIDChanged)
    Q_PROPERTY(QString connectorXPosition READ getConnectorXPosition WRITE setConnectorXPosition NOTIFY connectorXPositionChanged)
    Q_PROPERTY(QString connectorYPosition READ getConnectorYPosition WRITE setConnectorYPosition NOTIFY connectorYPositionChanged)
    Q_PROPERTY(QString nodeStartID READ getNodeStartID WRITE setNodeStartID NOTIFY nodeStartUIDChanged)
    Q_PROPERTY(QString nodeEndID READ getNodeEndID WRITE setNodeEndID NOTIFY nodeEndIDChanged)

    connectorPtr->setConnectorUID(uidQString);
    connectorPtr->setConnectorXPosition(connectorXPosition);
    connectorPtr->setConnectorYPosition(connectorYPosition);
    connectorPtr->setNodeStartID(nodeStartID);
    connectorPtr->setNodeEndID(nodeEndID);
    */

    connectorPtr->setConnectorUID(uidQString);
    _connectorLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLConnector>>(_connectorUid, connectorPtr));

    emit nodeListUpdated(_nodeLookup);

    return uidQString;
}

void MyDocument::setNewConnectorXandYPos(const QString &uid, const QString &connectorXPosition, const QString &connectorYPosition) {
    auto connectorEntry = _connectorLookup.find(uid.toInt());
    connectorEntry->second->setConnectorXPosition(connectorXPosition);
    connectorEntry->second->setConnectorYPosition(connectorYPosition);
    std::cout << "MyDocument::setNewNodePos nodeXPosition:  " << connectorXPosition.toStdString() << std::endl;

    std::cout << "MyDocument::getConnectorXPosition connectorXPosition:  " << connectorEntry->second->getConnectorXPosition().toStdString() << std::endl;
    std::cout << "MyDocument::getConnectorXPosition connectorYPosition(:  " << connectorEntry->second->getConnectorYPosition().toStdString() << std::endl;
    emit connectorListUpdated(_connectorLookup);
}

void MyDocument::setNewConnectorStartNode(const QString &uid, const QString &connectorStartNodeX) {
    auto connectorEntry = _connectorLookup.find(uid.toInt());
    connectorEntry->second->setNodeStartID(connectorStartNodeX);
}

void MyDocument::setNewConnectorEndNode(const QString &uid, const QString &connectorStartNodeY) {
    auto connectorEntry = _connectorLookup.find(uid.toInt());
    connectorEntry->second->setNodeEndID(connectorStartNodeY);
}


}
