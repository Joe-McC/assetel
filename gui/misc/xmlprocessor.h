#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include "xmlnode.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>

namespace Misc {

class XMLProcessor
{
public:
    XMLProcessor();
    void setFilename(QFile &filename);
    std::vector<Misc::XMLNode> getNodes();
    void writeNodes(Misc::XMLNode parent);

private:
    inline static QFile _XMLfilename;
    //inline static QXmlStreamWriter _xmlWriter;
    //inline static QXmlStreamReader _xmlReader;
    inline static QDomDocument _XMLdocument;
};

}
#endif // XMLPROCESSOR_H
