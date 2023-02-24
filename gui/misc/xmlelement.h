#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "abstractasseteltem.h"


// An ELement class is used by the Node class to create the pre-define ELements using the attributes set in the QML implementation.
class XMLElement: public AbstractAsseteltem
{

public:
    XMLElement();
    void insert(std::shared_ptr<XMLElement> item, int index);
    //void insert(std::unique_ptr<AbstractAsseteltem> item, int index);
    void remove(std::unique_ptr<XMLElement> item);
    //std::unique_ptr<AbstractAsseteltem> getParent();
    std::shared_ptr<XMLElement> getChild(int index);
    std::pair<float, float> getPosition() override;
    void setPosition(std::pair<float, float>) override;




    void addChildElement(const std::string &name);
    XMLElement getParentElement(XMLElement parentName);
    std::list<XMLElement> getChildElements(XMLElement parentName);
    void createNewAttribute(const std::string &name);
    void writeOpenTag(const std::string);
    void writeCloseTag();
    void writeStartElementTag(const std::string);
    void writeEndElementTag();
    void writeAttribute(const std::string);
    void writeString(const std::string);
private:
    std::pair<float, float> m_Pos;
    std::vector<std::shared_ptr<XMLElement>> m_ChildList;


    std::ofstream outFile;
    int indent;
    int openTags;
    int openElements;
    std::vector<std::string> tempOpenTag;
    std::vector<std::string> tempElementTag;
};

#endif // XMLELEMENT_H
