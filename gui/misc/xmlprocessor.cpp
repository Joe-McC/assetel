#include "xmlprocessor.h"

namespace Misc
{
XMLProcessor::XMLProcessor()
{

}

void XMLProcessor::setFilename(QFile &filename)
{
    _XMLfilename.setFileName(filename.fileName()); //QFile does not have copy constructor so need to get string of filename and reset

//SEE https://doc.qt.io/qt-6/qdomdocument.html and https://stackoverflow.com/questions/45814463/modify-an-xml-file-qxmlstreamreader-writer
    QDomDocument _XMLdocument;
    if (!_XMLdocument.setContent(&filename))
    {
        qDebug() << "failed to parse file";
        filename.close();
        //return 0;
    }

    //filename.close();

    /*QDomElement docEle = _XMLdocument.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("LAMPS");

    QDomElement light1 = _XMLdocument.createElement( "LIGHT1" );
    QDomElement state = _XMLdocument.createElement("State");
    QDomText nextNode = _XMLdocument.createTextNode("State");
    state.appendChild(nextNode);
    light1.appendChild(state);
    docEle.appendChild( light1 );

    QFile outFile( "test-result.xml" );
    if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );
        //return 0;
    }

    QTextStream stream( &outFile );
    stream << _XMLdocument.toString();

    outFile.close();*/

    /* Create an object, through which the recording to file */
    /*//QXmlStreamWriter _xmlWriter(&_XMLfilename);
    //_xmlWriter(&_XMLfilename);
    _xmlWriter.setDevice(&_XMLfilename);

    //Create an object, through which the reading of the file
    _xmlReader.setDevice(&_XMLfilename);


    _xmlWriter.setAutoFormatting(true);  // Set the auto-formatting text_xmlWriter.writeStartDocument();     // run record in a document

    _xmlWriter.writeStartDocument();
    _xmlWriter.writeDTD(QStringLiteral("<!DOCTYPE xbel>"));
    _xmlWriter.writeStartElement(QStringLiteral("xbel"));
    _xmlWriter.writeAttribute(QStringLiteral("version"), QStringLiteral("1.0"));


    //_xmlWriter.writeEndDocument();*/
}

std::vector<Misc::XMLNode> XMLProcessor::getNodes()
{
    std::vector<Misc::XMLNode> nodes;


    // already done in MyDocument.open ????

    /*if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }*/
    return nodes;
}

void XMLProcessor::writeNodes(std::map<int, std::shared_ptr<XMLNode>> &nodeLookup)
{
    /* FROM https://doc.qt.io/qt-6/qdomdocument.html
     * QDomDocument doc;
     * QDomElement root = doc.createElement("MyML");
     * doc.appendChild(root);
     * QDomElement tag = doc.createElement("Greeting");
     * root.appendChild(tag);
     * QDomText t = doc.createTextNode("Hello World");
     * tag.appendChild(t);
     * QString xml = doc.toString();
     */


    QDomElement nodes = _XMLdocument.createElement("Nodes");

    for (auto const& nodeEntry : nodeLookup)
    {
        QDomElement node = _XMLdocument.createElement("Node");
        _XMLdocument.appendChild(node);

        QDomElement nodeTitle = _XMLdocument.createElement("Node Title");
        node.appendChild(nodeTitle);
        QDomText nodeTitleValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeTitle());
        nodeTitle.appendChild(nodeTitleValue);

        QDomElement nodeText = _XMLdocument.createElement("Node Text");
        node.appendChild(nodeText);
        QDomText nodeTextValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeText());
        nodeText.appendChild(nodeTextValue);

        QDomElement nodeUID = _XMLdocument.createElement("Node UID");
        node.appendChild(nodeUID);
        QDomText nodeUIDValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeUID());
        nodeUID.appendChild(nodeUIDValue);

        QDomElement nodeParentID = _XMLdocument.createElement("Node Parent ID");
        node.appendChild(nodeParentID);
        QDomText nodeParentIDValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeParentID());
        nodeParentID.appendChild(nodeParentIDValue);

        QDomElement nodeXPos = _XMLdocument.createElement("Node X Position");
        node.appendChild(nodeXPos);
        QDomText nodeXPosValue = _XMLdocument.createTextNode(nodeEntry.second->getNodeXPosition());
        nodeXPos.appendChild(nodeXPosValue);

        QDomElement nodeYPos = _XMLdocument.createElement("Node Y Position");
        node.appendChild(nodeXPos);
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

    /*_xmlWriter.writeStartElement("resources");   // Write the first element of his name

    _xmlWriter.writeStartElement("Node");

    _xmlWriter.writeTextElement("NodeTitle", node.getNodeTitle());
    _xmlWriter.writeTextElement("NodeText", node.getNodeText());
    _xmlWriter.writeTextElement("NodeParentID", node.getNodeParentID());
    _xmlWriter.writeTextElement("NodeUID", node.getNodeUID());
    _xmlWriter.writeTextElement("NodeXPosition", node.getNodeXPosition());
    _xmlWriter.writeTextElement("NodeYPosition", node.getNodeYPosition());

    _xmlWriter.writeEndElement();

    // ************************************ WHEN DO WE WANT TO CLOSE THE FILE -- Never??? **********************************
    //_XMLfilename.close();*/
}

}

