#ifndef XMLCONNECTOR_H
#define XMLCONNECTOR_H

#include "abstractasseteltem.h"

class XMLConnector
{
public:

    XMLConnector();
    ~XMLConnector();

    void insert(std::unique_ptr<AbstractAsseteltem> item, int index);
    void remove(std::unique_ptr<AbstractAsseteltem> item );
    std::unique_ptr<AbstractAsseteltem> getParent();
    std::unique_ptr<AbstractAsseteltem> getChild(int index);
    std::pair<float, float> getPosition();
    void setPosition();


};

#endif // XMLCONNECTOR_H
