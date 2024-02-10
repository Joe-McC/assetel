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

}

void XMLProcessor::closeDocument()
{
    _XMLfilename.close();
}

std::map<int, std::shared_ptr<XMLNode>> XMLProcessor::getNodes(QQmlApplicationEngine *engine)
{
    std::cout << "Misc::MyProcessor::getNodes filename: " << _XMLfilename.fileName().toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
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

    std::map<int, std::shared_ptr<XMLNode>> nodeList;

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
        if (domNodes.tagName()=="node")
        {
            // Get the first child of the component
            QDomElement child=domNodes.firstChild().toElement();

            std::cout << "child = " << child.tagName().toStdString() << '\n';

            QString title;
            QString text;
            QString uidStr;
            QString parentid;
            QString xpos;
            QString ypos;

            // Read each child of the component node
            while (!child.isNull())
            {
                // Read Name and value
                if (child.tagName()=="title") title = child.firstChild().toText().data();
                if (child.tagName()=="text") text = child.firstChild().toText().data();
                if (child.tagName()=="uid") uidStr = child.firstChild().toText().data();
                if (child.tagName()=="parentid") parentid = child.firstChild().toText().data();
                if (child.tagName()=="xpos") xpos = child.firstChild().toText().data();
                if (child.tagName()=="ypos") ypos = child.firstChild().toText().data();
                // Next child
                child = child.nextSibling().toElement();
            }

            auto nodePtr = std::shared_ptr<XMLNode>(new XMLNode());

            nodePtr->setProperty("nodeTitle", title);
            nodePtr->setProperty("nodeText", text);
            nodePtr->setProperty("nodeUID", uidStr);
            nodePtr->setProperty("nodeParentID", parentid);
            nodePtr->setProperty("nodeXPosition", xpos);
            nodePtr->setProperty("nodeYPosition", ypos);

            std::cout << "title = " << title.toStdString() << '\n';
            std::cout << "text = " << text.toStdString() << '\n';
            std::cout << "text = " << uidStr.toStdString() << '\n';
            std::cout << "parentid = " << parentid.toStdString() << '\n';
            std::cout << "xpos = " << xpos.toStdString() << '\n';
            std::cout << "ypos = " << ypos.toStdString() << '\n';

            nodeList.insert(std::pair<int, std::shared_ptr<Misc::XMLNode>>(uid, nodePtr));
            uid++;
        }

        // Next component
        domNodes = domNodes.nextSibling().toElement();
    }

    return nodeList;
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
    // Set nodes as the root element of the XML document
    _XMLdocument.appendChild(nodes);

    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        std::cout << "XMLProcessor::writeNodes:Filename: " << _XMLfilename.fileName().toStdString() << std::endl;

        QTextStream stream( &_XMLfilename );
        stream << _XMLdocument.toString();
        std::cout << "XMLProcessor::writeNodes: " << stream.string() << std::endl;
        //_XMLfilename.close();
    }

    _XMLdocument.clear();
}

std::map<int, std::shared_ptr<XMLConnector>> XMLProcessor::getConnectors(QQmlApplicationEngine *engine)
{
    std::cout << "Misc::MyProcessor::getNodes filename: " << _XMLfilename.fileName().toStdString() << std::endl;
    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
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

    std::map<int, std::shared_ptr<XMLConnector>> connectorList;

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = _XMLdocument.documentElement();
    QString startTag = docElem.tagName();
    qDebug()<<"The docElem tag is"<<startTag;
    std::cout << "XMLProcessor::getConnectors" << '\n';

    int uid = 1;
    QDomElement domNodes = docElem.firstChild().toElement();

    // Loop while there is a child
    while(!domNodes.isNull())
    {
        std::cout << "domNodes.tagName() = " << domNodes.tagName().toStdString() << '\n';
        // Check if the child tag name is COMPONENT
        if (domNodes.tagName()=="connector")
        {
            // Get the first child of the component
            QDomElement child=domNodes.firstChild().toElement();

            std::cout << "child = " << child.tagName().toStdString() << '\n';
            QString connectorUID;
            QString connectorPositionStartX;
            QString connectorPositionStartY;
            QString connectorPositionEndX;
            QString connectorPositionEndY;
            QString nodeStartID;
            QString nodeEndID;

            // Read each child of the component node
            while (!child.isNull())
            {
                // Read Name and value
                if (child.tagName()=="connectoruid") connectorUID = child.firstChild().toText().data();
                if (child.tagName()=="connectorposstartX") connectorPositionStartX = child.firstChild().toText().data();
                if (child.tagName()=="connectorposstartY") connectorPositionStartY = child.firstChild().toText().data();
                if (child.tagName()=="connectorposendX") connectorPositionEndX = child.firstChild().toText().data();
                if (child.tagName()=="connectorposendY") connectorPositionEndY = child.firstChild().toText().data();
                if (child.tagName()=="nodestartid") nodeStartID = child.firstChild().toText().data();
                if (child.tagName()=="nodeendid") nodeEndID = child.firstChild().toText().data();

                // Next child
                child = child.nextSibling().toElement();
            }

            auto conectorPtr = std::shared_ptr<XMLConnector>(new XMLConnector());

            conectorPtr->setProperty("connectorUID", connectorUID);
            conectorPtr->setProperty("connectorPositionStartX", connectorPositionStartX);
            conectorPtr->setProperty("connectorPositionStartY", connectorPositionStartY);
            conectorPtr->setProperty("connectorPositionEndX", connectorPositionEndX);
            conectorPtr->setProperty("connectorPositionEndY", connectorPositionEndY);
            conectorPtr->setProperty("nodeStartID", nodeStartID);
            conectorPtr->setProperty("nodeEndID", nodeEndID);

            connectorList.insert(std::pair<int, std::shared_ptr<Misc::XMLConnector>>(uid, conectorPtr));
            uid++;
        }

        // Next component
        domNodes = domNodes.nextSibling().toElement();
    }
    //_XMLfilename.close();

    return connectorList;
}

void XMLProcessor::writeConnectors(std::map<int, std::shared_ptr<XMLConnector>> &connectorLookup) {
    QDomElement connectors = _XMLdocument.createElement("connectors");

    for (auto const& connectorEntry : connectorLookup)
    {
        QDomElement connector = _XMLdocument.createElement("connector");
        connectors.appendChild(connector);

        QDomElement connectorUID = _XMLdocument.createElement("connectoruid");
        connector.appendChild(connectorUID);
        QDomText connectorUIDValue = _XMLdocument.createTextNode(connectorEntry.second->getConnectorUID());
        qDebug() << "connectorUIDValue:" << connectorEntry.second->getConnectorUID();
        connectorUID.appendChild(connectorUIDValue);

        QDomElement connectorPositionStartX = _XMLdocument.createElement("posstartx");
        connector.appendChild(connectorPositionStartX);
        QDomText connectorPositionStartXValue = _XMLdocument.createTextNode(connectorEntry.second->getConnectorXPositionStart());
        connectorPositionStartX.appendChild(connectorPositionStartXValue);

        QDomElement connectorPositionStartY = _XMLdocument.createElement("posstarty");
        connector.appendChild(connectorPositionStartY);
        QDomText connectorPositionStartYValue = _XMLdocument.createTextNode(connectorEntry.second->getConnectorYPositionStart());
        connectorPositionStartY.appendChild(connectorPositionStartYValue);

        QDomElement connectorPositionEndX = _XMLdocument.createElement("posendx");
        connector.appendChild(connectorPositionEndX);
        QDomText connectorPositionEndXValue = _XMLdocument.createTextNode(connectorEntry.second->getConnectorXPositionEnd());
        connectorPositionEndX.appendChild(connectorPositionEndXValue);

        QDomElement connectorPositionEndY = _XMLdocument.createElement("posendy");
        connector.appendChild(connectorPositionEndY);
        QDomText connectorPositionEndYValue = _XMLdocument.createTextNode(connectorEntry.second->getConnectorYPositionEnd());
        connectorPositionEndY.appendChild(connectorPositionEndYValue);

        /*QString startY = connectorEntry.second->getConnectorYPositionStart();
        //QString startYStr = QString::number(startY);
        QDomText connectorPositionStartValue = _XMLdocument.createTextNode(startX + ',' + startY);
        connectorPositionStart.appendChild(connectorPositionStartValue);

        QDomElement connectorPositionEnd = _XMLdocument.createElement("posend");
        connector.appendChild(connectorPositionEnd);
        QString endX = connectorEntry.second->getConnectorXPositionEnd();
        qDebug() << "endX:" << endX;
        //QString endXStr = QString::number(endX);
        //qDebug() << "endXStr:" << endXStr;
        QString endY = connectorEntry.second->getConnectorYPositionEnd();
        qDebug() << "endY:" << endY;
        //QString endYStr = QString::number(endY);
        //qDebug() << "endYStr:" << endYStr;
        QDomText connectorPositionEndValue = _XMLdocument.createTextNode(endX + ',' + endY);
        connectorPositionEnd.appendChild(connectorPositionEndValue);
        */


        QDomElement nodeStartID = _XMLdocument.createElement("nodestartid");
        connector.appendChild(nodeStartID);
        QDomText nodeStartIDValue = _XMLdocument.createTextNode(connectorEntry.second->getNodeStartID());
        nodeStartID.appendChild(nodeStartID);

        QDomElement nodeEndID = _XMLdocument.createElement("nodeendid");
        connector.appendChild(nodeEndID);
        QDomText nodeXPosValue = _XMLdocument.createTextNode(connectorEntry.second->getNodeEndID());
        nodeEndID.appendChild(nodeXPosValue);
    }

    /* how do we write a child node into an existing node?? use https://stackoverflow.com/questions/45814463/modify-an-xml-file-qxmlstreamreader-writer??? */
    // Set nodes as the root element of the XML document
    _XMLdocument.appendChild(connectors);

    //if (_XMLfilename.open(QIODevice::ReadWrite))
    //{
    //    std::cout << "File Opened" << std::endl;
    //    std::cout << "XMLProcessor::writeNodes:Filename: " << _XMLfilename.fileName().toStdString() << std::endl;

    QTextStream stream( &_XMLfilename );
    stream << _XMLdocument.toString();

    //    std::cout << "XMLProcessor::writeNodes: " << stream.string() << std::endl;
        //_XMLfilename.close();
    //}

    _XMLdocument.clear();
}

}

