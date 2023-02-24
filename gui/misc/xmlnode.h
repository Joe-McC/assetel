#ifndef XMLNODE_H
#define XMLNODE_H

#include "abstractasseteltem.h"

class XMLNode: public AbstractAsseteltem
{
public:
    XMLNode();
    void insert(std::shared_ptr<AbstractAsseteltem> item, int index);
    //void insert(std::unique_ptr<AbstractAsseteltem> item, int index);
    void remove(std::unique_ptr<AbstractAsseteltem> item);
    //std::unique_ptr<AbstractAsseteltem> getParent();
    std::shared_ptr<AbstractAsseteltem> getChild(int index);
    std::pair<float, float> getPosition() override;
    void setPosition(std::pair<float, float>) override;


private:
    std::pair<float, float> m_Pos;
    std::vector<std::shared_ptr<AbstractAsseteltem>> m_ChildList;
};

#endif // XMLNODE_H
