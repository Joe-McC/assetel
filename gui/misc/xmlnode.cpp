#include "xmlnode.h"

void XMLNode::insert(std::shared_ptr<AbstractAsseteltem> item, int index)
{

}

void XMLNode::remove(std::unique_ptr<AbstractAsseteltem> item )
{

}

/*std::unique_ptr<AbstractAsseteltem> getParent()
{
    return std::unique_ptr<AbstractAsseteltem> m_Parent;
}*/



std::shared_ptr<AbstractAsseteltem> XMLNode::getChild(int index)
{
    return m_ChildList[index];
}

std::pair<float, float> XMLNode::getPosition()
{
    return m_Pos;
}

void XMLNode::setPosition(std::pair<float, float> position)
{
    m_Pos = position;
}
