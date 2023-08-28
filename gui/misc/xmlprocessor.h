#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include "xmlnode.h"
#include <QFile>

namespace Misc {

class XMLProcessor
{
public:
    XMLProcessor(QFile filename);

    std::vector<Misc::XMLNode> getNodes();
    void writeNodes(Misc::XMLNode parent);

private:
    inline static QFile _XMLfilename;
};

}
#endif // XMLPROCESSOR_H
