#include "xmlconnector.h"

void XMLConnector::insert(std::unique_ptr<AbstractAsseteltem> item, int index)
{

}

void XMLConnector::remove(std::unique_ptr<AbstractAsseteltem> item )
{

}

//std::unique_ptr<AbstractAsseteltem> getParent();

// Connectors are leaf components and do not have childrenm return nullptr.
std::unique_ptr<AbstractAsseteltem> XMLConnector::getChild(int index)
{
    return nullptr;
}

std::pair<float, float> XMLConnector::getPosition()
{
    return m_Pos;
}

void XMLConnector::setPosition(std::pair<float, float> position)
{
    m_Pos = position;
}
