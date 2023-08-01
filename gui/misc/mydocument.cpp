#include "mydocument.h"

/*Misc::MyDocument::MyDocument(QObject *parent)
    : QObject{parent}
{

}*/

/**
 * Returns the only instance of the class, this is to be used by the QML interface
 */

Misc::MyDocument &Misc::MyDocument::getInstance()
{
    static MyDocument instance;

    return instance;
}

void Misc::MyDocument::write(const QString &filename, const QString &inputXml)
{
    QFile file;
    file.setFileName(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }
    return;
}


QString Misc::MyDocument::addNode(const QString &nodeText, const QString& parentNodeId)
{
    _uid++;//  ::_uidCount++;
    Misc::XMLNode node;
    auto nodePtr = std::make_shared<Misc::XMLNode>(node);
    QString uidQString = getUIDQString();

    std::cout << "Misc::MyDocument::addNode parentNodeId: " << parentNodeId.toStdString() << std::endl;


    // Check if a parent node ID is provided
    if (!parentNodeId.isEmpty())
    {
        // Add the new node as a child of the parent node
        auto parentNode = _nodeLookup.find(parentNodeId.toInt());

        std::cout << "Misc::MyDocument::addNode parentNode after lookup: " << parentNode->second->getNodeText() << std::endl;


        if (parentNode != _nodeLookup.end())
        {
            parentNode->second->addChild(nodeText);
        }
        emit childNodeAdded(_uid, parentNodeId.toInt());
    }
    else
    {
        std::cout << "emit TopLevelNodeAdded: " << _uid << std::endl;
        emit topLevelNodeAdded(_uid);
    }
    Misc::MyDocument::_nodeLookup.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(_uid, nodePtr));

    node.setNodeText(nodeText);

    return uidQString;
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
