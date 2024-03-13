#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include "xmlnode.h"
#include "xmlconnector.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickWindow>


namespace Misc {

class XMLProcessor
{
public:
    XMLProcessor();
    void setFilename(QFile &filename);
    void openDocument();
    void closeDocument();
    std::map<int, std::shared_ptr<XMLNode>> getNodes(QQmlApplicationEngine *engine);
    std::map<int, std::shared_ptr<XMLConnector>> getConnectors(QQmlApplicationEngine *engine);
    void writeNodes(std::map<int, std::shared_ptr<XMLNode>> &nodeLookup);
    void writeConnectors(std::map<int, std::shared_ptr<XMLConnector>> &connectorLookup);

private:
    inline static QFile _XMLfilename;
    inline static QDomDocument _XMLdocument;
    inline static QDomElement _nodes;
};

}
#endif // XMLPROCESSOR_H
