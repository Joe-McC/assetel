#ifndef XMLCONNECTOR_H
#define XMLCONNECTOR_H

#include "abstractasseteltem.h"

class XMLConnector : AbstractAsseteltem
{
public:
    XMLConnector();
    //void insert(std::unique_ptr<AbstractAsseteltem> item, int index) override;
    //void remove(std::unique_ptr<AbstractAsseteltem> item) override;
    //std::unique_ptr<AbstractAsseteltem> getParent();
    //std::shared_ptr<AbstractAsseteltem> getChild(int index) override;
    std::pair<float, float> getPosition() override;
    void setPosition(std::pair<float, float>) override;


private:
    std::pair<float, float> m_Pos;

};



#endif // XMLCONNECTOR_H
