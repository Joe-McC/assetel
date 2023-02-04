#ifndef XMLNODE_H
#define XMLNODE_H

#include "abstractasseteltem.h"
#include "xmlelement.h"

class XMLNode: public AbstractAsseteltem
{
public:
    XMLNode();
    void insert(std::unique_ptr<XMLElement> item, int index);
    void remove(std::unique_ptr<AbstractAsseteltem> item );
    //std::unique_ptr<AbstractAsseteltem> getParent();
    std::unique_ptr<AbstractAsseteltem> getChild(int index);
    std::pair<float, float> getPosition();
    void setPosition();
};

#endif // XMLNODE_H
