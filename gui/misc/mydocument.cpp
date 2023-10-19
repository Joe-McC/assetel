#include "mydocument.h"
#include "qqmlcomponent.h"
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

    //_nodeLookup = _XMLprocessor.getNodes(_engine);

    return;
}

void MyDocument::saveDocument(const QString &filename)
{
    QString filenameModified = filename.mid(8);
    _XMLfilename.setFileName(filenameModified);

    _XMLprocessor.setFilename(_XMLfilename);

    _XMLprocessor.writeNodes(_nodeLookup);  // MAYBE PASS A VECTOR OF NODES AND WRITE THEM ALL?

    // don't think this is needed as we just need to open a file and write to it, so it's the same as opening a doc???? --IT NEEDS TO BE CALLED AFTER WRITING TO EXISTING FILE
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
    Misc::MyDocument::_nodeLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(_uid, nodePtr));

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

QList<QObject*> MyDocument::getNodesForQml() {
    std::cout << "MyDocument::getNodesForQml() - called from projectviewer.qml repeater" << "std::endl() \n";

    _nodeLookup = _XMLprocessor.getNodes(_engine);

    //QQmlComponent component(_engine, QUrl::fromLocalFile("Node.qml"));
    //QObject *object = component.create();
    //object->setProperty("width", 200);
    //object->setProperty("height", 150);
    //object->setProperty("color", "blue");


    QList<QObject*> qmlNodes;
    QObject* qmlNode = new QObject(this);
    for (const auto& entry : _nodeLookup) {
        /*XMLNode* node = entry.second.get(); // Assuming _nodeLookup is a std::map<int, std::shared_ptr<XMLNode>>

        // Ensure signals are connected properly for property changes
        connect(node, &XMLNode::nodeTitleChanged, this, &MyDocument::handleNodeTitleChange);
        connect(node, &XMLNode::nodeUIDChanged, this, &MyDocument::handleNodeUIDChange);
        // ... connect other signals ...

        qmlNodes.append(node);*/


        //qmlNode->setProperty("nodeTitle", entry.second->getNodeTitle());
        //qmlNode->setProperty("nodeText", entry.second->getNodeText());
        //qmlNodes.append(qmlNode);
        //QObject* qmlNode = new XMLNode();

        std::cout << "title = " << entry.second->getNodeTitle().toStdString().c_str() << std::endl;
        std::cout << "text  = " << entry.second->getNodeText().toStdString().c_str() << std::endl;
        std::cout << "uid = " << entry.second->getNodeUID().toStdString().c_str() << std::endl;
        std::cout << "parentid  = " << entry.second->getNodeParentID().toStdString().c_str() << std::endl;
        std::cout << "xpos = " << entry.second->getNodeXPosition().toStdString().c_str() << std::endl;
        std::cout << "ypos  = " << entry.second->getNodeYPosition().toStdString().c_str() << std::endl;

        std::cout << std::endl;


        qmlNode->setProperty("nodeTitle", entry.second->getNodeTitle());
        qmlNode->setProperty("nodeText", entry.second->getNodeText());
        qmlNode->setProperty("nodeUID", entry.second->getNodeUID());
        qmlNode->setProperty("nodeParentID", entry.second->getNodeParentID());
        qmlNode->setProperty("nodeXPosition", entry.second->getNodeXPosition());
        qmlNode->setProperty("nodeYPosition", entry.second->getNodeYPosition());
        qmlNodes.append(qmlNode);
    }



    //_engine->rootContext()->setContextProperty("axes", QVariant::fromValue(data.axes()));

    return qmlNodes;
}

QList<QObject*> MyDocument::getNodes() {
    std::cout << "MyDocument::getNodesForQml() - called from projectviewer.qml repeater" << "std::endl() \n";

    _nodeLookup = _XMLprocessor.getNodes(_engine);

    QList<QObject*> qmlNodes;
    for (const auto& entry : _nodeLookup) {
        /*XMLNode* node = entry.second.get(); // Assuming _nodeLookup is a std::map<int, std::shared_ptr<XMLNode>>

        // Ensure signals are connected properly for property changes
        connect(node, &XMLNode::nodeTitleChanged, this, &MyDocument::handleNodeTitleChange);
        connect(node, &XMLNode::nodeUIDChanged, this, &MyDocument::handleNodeUIDChange);
        // ... connect other signals ...

        qmlNodes.append(node);*/

        //QObject* qmlNode = new QObject(this);
        //qmlNode->setProperty("nodeTitle", entry.second->getNodeTitle());
        //qmlNode->setProperty("nodeText", entry.second->getNodeText());
        //qmlNodes.append(qmlNode);
        //QObject* qmlNode = new XMLNode();

        //XMLNode* qmlNode = new XMLNode();

        //node->setProperty("width", 200);
        //object->setProperty("height", 150);
        //object->setProperty("color", "blue");

        std::cout << "title = " << entry.second->getNodeTitle().toStdString().c_str() << std::endl;
        std::cout << "text  = " << entry.second->getNodeText().toStdString().c_str() << std::endl;
        std::cout << "uid = " << entry.second->getNodeUID().toStdString().c_str() << std::endl;
        std::cout << "parentid  = " << entry.second->getNodeParentID().toStdString().c_str() << std::endl;
        std::cout << "xpos = " << entry.second->getNodeXPosition().toStdString().c_str() << std::endl;
        std::cout << "ypos  = " << entry.second->getNodeYPosition().toStdString().c_str() << std::endl;


        //qmlNode->setProperty("nodeTitle", QString("Test"));

        std::cout << std::endl;

       /*qmlNode->setNodeTitle(entry.second->getNodeTitle());
        qmlNode->setNodeText(entry.second->getNodeText());
        qmlNode->setNodeUID(entry.second->getNodeUID());
        qmlNode->setNodeParentID(entry.second->getNodeParentID());
        qmlNode->setNodeXPosition(entry.second->getNodeXPosition());
        qmlNode->setNodeXPosition(entry.second->getNodeYPosition());
        qmlNodes.append(qmlNode);*/


    }
    return qmlNodes;
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
