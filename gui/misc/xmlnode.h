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

    void setNodeTitle(const QString &title);
    std::string getNodeTitle();

    void setNodeText(const QString &nodeText);
    std::string getNodeText();

    void addChild(const QString &nodeText);
private:
    inline static std::string _nodeTitle;
    inline static std::string _nodeText;
};

}
#endif // XMLNODE_H
