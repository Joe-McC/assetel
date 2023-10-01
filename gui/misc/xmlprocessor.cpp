#include "xmlprocessor.h"

namespace Misc
{
XMLProcessor::XMLProcessor()
{

}

void XMLProcessor::setFilename(QFile &filename)
{

    std::cout << "XMLProcessor::setFilename \n";


    _XMLfilename.setFileName(filename.fileName()); //QFile does not have copy constructor so need to get string of filename and reset

    std::cout << "XMLProcessor::setFilename " << _XMLfilename.fileName().toStdString() << '\n';


//SEE https://doc.qt.io/qt-6/qdomdocument.html and https://stackoverflow.com/questions/45814463/modify-an-xml-file-qxmlstreamreader-writer
    QDomDocument _XMLdocument;
    QString error;
    int line, column;

    if (!_XMLdocument.setContent(&filename, &error, &line, &column))
    {
        qDebug() << "XMLProcessor::setFilename failed to parse file";
        qDebug() << "Error:" << error << "in line " << line << "column" << column;
        filename.close();
    } 
}

std::map<int, std::shared_ptr<XMLNode>> XMLProcessor::getNodes()
{
    std::map<int, std::shared_ptr<XMLNode>> nodes;
    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = _XMLdocument.documentElement();

    std::cout << "XMLProcessor::getNodes" << '\n';
    int uid = 1;
    QDomNode n = docElem.firstChild();

    // we're not currently entering the following while loop...
    while(!n.isNull()) {
        std::cout << "XMLProcessor::getNodes QDomNode n is not null" << '\n';

        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
           std::cout << "XMLProcessor::getNodes QDomElement e  is not null" << '\n';

           auto nodePtr = std::shared_ptr<Misc::XMLNode>(new Misc::XMLNode());
           nodes.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(uid, nodePtr));
           uid++;
           std::cout << "TagName" << qPrintable(e.tagName()) << '\n'; // the node really is an element.
           std::cout << "NodeName" << qPrintable(e.nodeName()) << '\n'; // the node really is an element.
        }
        n = n.nextSibling();
    }

    return nodes;
}

void XMLProcessor::writeNodes(std::map<int, std::shared_ptr<XMLNode>> &nodeLookup)
{
    QDomElement nodes = _XMLdocument.createElement("nodes");

    for (auto const& nodeEntry : nodeLookup)
    {
        QDomElement node = _XMLdocument.createElement("node");
        nodes.appendChild(node);

        QDomElement nodeTitle = _XMLdocument.createElement("title");
        node.appendChild(nodeTitle);
        QDomText nodeTitleValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeTitle());
        nodeTitle.appendChild(nodeTitleValue);

        QDomElement nodeText = _XMLdocument.createElement("text");
        node.appendChild(nodeText);
        QDomText nodeTextValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeText());
        nodeText.appendChild(nodeTextValue);

        QDomElement nodeUID = _XMLdocument.createElement("uid");
        node.appendChild(nodeUID);
        QDomText nodeUIDValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeUID());
        nodeUID.appendChild(nodeUIDValue);

        QDomElement nodeParentID = _XMLdocument.createElement("parentid");
        node.appendChild(nodeParentID);
        QDomText nodeParentIDValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeParentID());
        nodeParentID.appendChild(nodeParentIDValue);

        QDomElement nodeXPos = _XMLdocument.createElement("xpos");
        node.appendChild(nodeXPos);
        QDomText nodeXPosValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeXPosition());
        nodeXPos.appendChild(nodeXPosValue);

        QDomElement nodeYPos = _XMLdocument.createElement("ypos");
        node.appendChild(nodeYPos);
        QDomText nodeYPosValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeYPosition());
        nodeYPos.appendChild(nodeYPosValue);
    }

    /* how do we write a child node into an existing node?? use https://stackoverflow.com/questions/45814463/modify-an-xml-file-qxmlstreamreader-writer??? */

    std::cout << "Misc::MyProcessor::writeNodes filename: " << _XMLfilename.fileName().toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }
    QTextStream stream( &_XMLfilename );
    stream << _XMLdocument.toString();

    _XMLfilename.close();
}

}

