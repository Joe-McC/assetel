#include "xmlconnector.h"
#include <iostream>
/*void XMLConnector::insert(std::unique_ptr<AbstractAsseteltem> item, int index)
{
    // we don't anything here as a XMLConnector is a Leaf Component
    std::cout << "Cannot insert into leaf component";
}

void XMLConnector::remove(std::unique_ptr<AbstractAsseteltem> item )
{
    // we don't anything here as a XMLConnector is a Leaf Component
    std::cout << "Cannot remove from leaf component";
}*/

//std::unique_ptr<AbstractAsseteltem> getParent();

std::pair<float, float> XMLConnector::getPosition()
{
    return m_Pos;
}

void XMLConnector::setPosition(std::pair<float, float> position)
{
    m_Pos = position;
}


