#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>


// An ELement class is used by the Node class to create the pre-define ELements using the attributes set in the QML implementation.
class XMLElement
{

public:
    XMLElement(std::string);
    ~XMLElement();
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
    std::ofstream outFile;
    int indent;
    int openTags;
    int openElements;
    std::vector<std::string> tempOpenTag;
    std::vector<std::string> tempElementTag;
};

#endif // XMLELEMENT_H
