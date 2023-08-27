#include "xmlnode.h"


namespace Misc
{

XMLNode::XMLNode() {
    // Constructor implementation
}

void XMLNode::setNodeTitle(const QString &title)
{
    _nodeTitle = title;
}

QString XMLNode::getNodeTitle()
{
    return _nodeTitle;
}


void XMLNode::setNodeText(const QString &text)
{
    _nodeText = text;
}

QString XMLNode::getNodeText()
{
    return _nodeText;
}

void XMLNode::setNodeParentID(const QString &parentID)
{
    _nodeParentID = parentID;
}

QString XMLNode::getNodeParentID()
{
    return _nodeParentID;
}

void XMLNode::setNodeUID(const QString &nodeUID)
{
    _nodeUID = nodeUID;
}

QString XMLNode::getNodeUID()
{
    return _nodeUID;
}

void XMLNode:: setNodeXPosition(const QString &nodeXPosition)
{
    _nodeXPosition = nodeXPosition;
}

QString XMLNode::getNodeXPosition()
{
    return _nodeXPosition;
}

void XMLNode::setNodeYPosition(const QString &nodeYPosition)
{
    _nodeYPosition = nodeYPosition;
}

QString XMLNode::getNodeYPosition()
{
    return _nodeYPosition;
}

void XMLNode::addChild(const QString &nodeText)
{
    Misc::XMLNode node;
    node.setNodeText(nodeText);
}

}
