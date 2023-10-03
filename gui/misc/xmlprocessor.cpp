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
    /*QDomDocument _XMLdocument;
    QString error;
    int line, column;

    if (!_XMLdocument.setContent(&filename, &error, &line, &column))
    {
        qDebug() << "XMLProcessor::setFilename failed to parse file";
        qDebug() << "Error:" << error << "in line " << line << "column" << column;
        filename.close();
    } */
}

std::map<int, std::shared_ptr<XMLNode>> XMLProcessor::getNodes()
{
    std::cout << "Misc::MyProcessor::getNodes filename: " << _XMLfilename.fileName().toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }

    QDomDocument _XMLdocument;
    QString error;
    int line, column;

    if (!_XMLdocument.setContent(&_XMLfilename, &error, &line, &column))
    {
        qDebug() << "XMLProcessor::setFilename failed to parse file";
        qDebug() << "Error:" << error << "in line " << line << "column" << column;
        _XMLfilename.close();
    }

    std::map<int, std::shared_ptr<XMLNode>> nodes;
    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = _XMLdocument.documentElement();
    QString startTag = docElem.tagName();
    qDebug()<<"The docElem tag is"<<startTag;
    std::cout << "XMLProcessor::getNodes" << '\n';

    int uid = 1;
    QDomElement domNodes = docElem.firstChild().toElement();
    //QDomNode node = nodes.firstChild();

    // Loop while there is a child
    while(!domNodes.isNull())
    {
        std::cout << "domNodes.tagName() = " << domNodes.tagName().toStdString() << '\n';
        // Check if the child tag name is COMPONENT
        if (domNodes.tagName()=="Node")
        {
            // Get the first child of the component
            QDomElement child=domNodes.firstChild().toElement();

            QString title;
            QString text;
            QString uid;
            QString parentid;
            QString xpos;
            QString ypos;

            // Read each child of the component node
            while (!child.isNull())
            {
                // Read Name and value
                if (child.tagName()=="title") title = child.firstChild().toText().data();
                if (child.tagName()=="text") text = child.firstChild().toText().data();
                if (child.tagName()=="uid") uid = child.firstChild().toText().data();
                if (child.tagName()=="parentid") parentid = child.firstChild().toText().data();
                if (child.tagName()=="xpos") xpos = child.firstChild().toText().data();
                if (child.tagName()=="ypos") ypos = child.firstChild().toText().data();
                // Next child
                child = child.nextSibling().toElement();
            }

            // Display component data
            std::cout << "title = " << title.toStdString().c_str() << std::endl;
            std::cout << "text  = " << text.toStdString().c_str() << std::endl;
            std::cout << "uid = " << uid.toStdString().c_str() << std::endl;
            std::cout << "parentid  = " << parentid.toStdString().c_str() << std::endl;
            std::cout << "xpos = " << xpos.toStdString().c_str() << std::endl;
            std::cout << "ypos  = " << ypos.toStdString().c_str() << std::endl;


            std::cout << std::endl;
        }

        // Next component
        domNodes = domNodes.nextSibling().toElement();
    }


    /*

    QString data = domNodes.tagName();
    qDebug()<<"The FirstChild is"<<data;
    qDebug("After the Nodes DOM Element");

    QDomNodeList nodesList = _XMLdocument.elementsByTagName("Nodes");
    for(int i = 0; i < nodesList.count(); i++)
    {
        QDomNodeList nodeTitle = _XMLdocument.elementsByTagName("title");
        QDomNode elm = nodesList.at(i);
        if(elm.isElement())
        {
            qDebug() << elm.toElement().tagName()
                     << " = "
                     << elm.toElement().text();
        }

        QDomNodeList nodeText = _XMLdocument.elementsByTagName("text");
        QDomNode elm2 = nodesList.at(i);
        if(elm2.isElement())
        {
            qDebug() << elm2.toElement().tagName()
                     << " = "
                     << elm2.toElement().text();
        }

    }


    // we're not currently entering the following while loop...
    /*while(!domNodes.isNull()) {
        std::cout << "XMLProcessor::getNodes QDomNode n is not null" << '\n';

        QDomElement e = domNodes.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
           std::cout << "XMLProcessor::getNodes QDomElement e  is not null" << '\n';

           auto nodePtr = std::shared_ptr<Misc::XMLNode>(new Misc::XMLNode());
           nodes.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(uid, nodePtr));
           uid++;
           std::cout << "TagName" << qPrintable(e.tagName()) << '\n'; // the node really is an element.
           std::cout << "NodeName" << qPrintable(e.nodeName()) << '\n'; // the node really is an element.
        }
        //n = nodes.nextSibling();
    }*/

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

