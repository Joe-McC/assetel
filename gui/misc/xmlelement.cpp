#include "xmlelement.h"


//void insert(std::unique_ptr<AbstractAsseteltem> item, int index);

void XMLElement::insert(std::shared_ptr<XMLElement> item, int index)
{

}

void XMLElement::remove(std::unique_ptr<XMLElement> item )
{

}

/*std::unique_ptr<AbstractAsseteltem> getParent()
{
    return std::unique_ptr<AbstractAsseteltem> m_Parent;
}*/

std::shared_ptr<XMLElement> XMLElement::getChild(int index)
{
    return m_ChildList[index];
}

std::pair<float, float> XMLElement::getPosition()
{
    return m_Pos;
}

void XMLElement::setPosition(std::pair<float, float> position)
{
    m_Pos = position;
}

/*
void XMLElement::addChildElement(const std::string &name) {

    XMLElement newElement(name);

}
XMLElement XMLElement::getParentElement(XMLElement parentName) {

}

std::list<XMLElement> XMLElement::getChildElements(XMLElement parentName) {

}
void XMLElement::createNewAttribute(const std::string &name) {

}*/

//=============================================================================
//== Function Name  :   XmlWriter::writeOpenTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== openTag    const std::string   The name of the tag being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new tag, checking that the file is open, and saves
//== the tag name in a vector to keep track of it
//=============================================================================
void XMLElement::writeOpenTag(const std::string openTag) {
    if (outFile.is_open()) {
        for (int i = 0; i < indent; i++) {
            outFile << "\t";
        }
        tempOpenTag.resize(openTags + 1);
        outFile << "<" << openTag << ">\n";
        tempOpenTag[openTags] = openTag;
        indent += 1;
        openTags += 1;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlWriter::writeCloseTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closes the currently open tag
//=============================================================================
void XMLElement::writeCloseTag() {
    if (outFile.is_open()) {
        indent -= 1;
        for (int i = 0; i < indent; i++) {
            outFile << "\t";
        }
        outFile << "</" << tempOpenTag[openTags - 1] << ">\n";
        tempOpenTag.resize(openTags - 1);
        openTags -= 1;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlWriter::writeStartElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== elementTag const std::string   The name of the element being created
//==
//== Description
//== --------------------------------------------------------------------------
//== This function creates a new element tag and saves the name to a vector
//=============================================================================
void XMLElement::writeStartElementTag(const std::string elementTag) {
    if (outFile.is_open()) {
        for (int i = 0; i < indent; i++) {
            outFile << "\t";
        }
        tempElementTag.resize(openElements + 1);
        tempElementTag[openElements] = elementTag;
        openElements += 1;
        outFile << "<" << elementTag;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlWriter::writeEndElementTag
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function closed the currently opened element tag
//=============================================================================
void XMLElement::writeEndElementTag() {
    if (outFile.is_open()) {
        outFile << "</" << tempElementTag[openElements - 1] << ">\n";
        tempElementTag.resize(openElements - 1);
        openElements -= 1;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlWriter::writeAttribute
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== outAttribute   const std::string   The attribute being written out
//==
//== Description
//== --------------------------------------------------------------------------
//== This function writes an attribute (if any) after the element tag is first
//== opened and before the output for the element is written
//=============================================================================
void XMLElement::writeAttribute(const std::string outAttribute) {
    if (outFile.is_open()) {
        outFile << " " << outAttribute;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}
//=============================================================================
//== Function Name  :   XmlWriter::writeString
//==
//== Perameters
//== Name           Type                Description
//== ----------     -----------         --------------------
//== writeString    const std::string   The string to be written to the element
//==
//== Description
//== --------------------------------------------------------------------------
//=============================================================================
void XMLElement::writeString(const std::string outString) {
    if (outFile.is_open()) {
        outFile << ">" << outString;
    }
    else {
        std::cout << "File is closed. Unable to write to file.\n";
    }
}


