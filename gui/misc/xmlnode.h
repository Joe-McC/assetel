#ifndef XMLNODE_H
#define XMLNODE_H

#include "abstractasseteltem.h"
#include "xmlelement.h"

class XMLNode: public AbstractAsseteltem
{
public:
    XMLNode();
    void insert(std::unique_ptr<XMLElement> item, int index) override;
    void remove(std::unique_ptr<AbstractAsseteltem> item ) override;
    //std::unique_ptr<AbstractAsseteltem> getParent();
    std::shared_ptr<AbstractAsseteltem> getChild(int index) override;
    std::pair<float, float> getPosition() override;
    void setPosition(std::pair<float, float>) override;

private:
    std::pair<float, float> m_Pos;
    std::vector<std::shared_ptr<std::shared_ptr<AbstractAsseteltem>>> m_ChildList;
};

#endif // XMLNODE_H
