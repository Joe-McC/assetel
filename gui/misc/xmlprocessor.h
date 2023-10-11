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
#include <QQmlApplicationEngine>
#include <QQmlComponent>


namespace Misc {

class XMLProcessor
{
public:
    XMLProcessor();
    void setFilename(QFile &filename);
    std::map<int, std::shared_ptr<XMLNode>> getNodes(QQmlApplicationEngine *engine);
    void writeNodes(std::map<int, std::shared_ptr<XMLNode>> &nodeLookup);

private:
    inline static QFile _XMLfilename;
    //inline static QXmlStreamWriter _xmlWriter;
    //inline static QXmlStreamReader _xmlReader;
    inline static QDomDocument _XMLdocument;
};

}
#endif // XMLPROCESSOR_H
