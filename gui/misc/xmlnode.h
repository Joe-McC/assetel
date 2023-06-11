#ifndef XMLNODE_H
#define XMLNODE_H

#include <QObject>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <xmlelement.h>


namespace Misc
{

class XMLNode
{
public:
    XMLNode();

    void addNodeText(const QString &nodeText);

private:

};

}
#endif // XMLNODE_H
