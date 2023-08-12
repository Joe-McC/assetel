#include "xmlnode.h"


namespace Misc
{

XMLNode::XMLNode() {
    // Constructor implementation
}

void XMLNode::setNodeTitle(const QString &title)
{
    _nodeTitle = title.toStdString();
}

std::string XMLNode::getNodeTitle()
{
    return _nodeTitle;
}


void XMLNode::setNodeText(const QString &text)
{
    _nodeText = text.toStdString();
}

std::string XMLNode::getNodeText()
{
    return _nodeText;
}


void XMLNode::addChild(const QString &nodeText)
{
    Misc::XMLNode node;
    node.setNodeText(nodeText);
}

}
