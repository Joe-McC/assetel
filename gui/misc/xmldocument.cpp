#include "xmldocument.h"

/*Misc::MyDocument::MyDocument(QObject *parent)
    : QObject{parent}
{

}*/

QString Misc::XMLDocument::name() const
{
    return m_name;
}


void Misc::XMLDocument::setName(const QString &name)
{
    m_name = name;
}


/**
 * Returns the only instance of the class, this is to be used by the QML interface
 */

Misc::XMLDocument &Misc::XMLDocument::getInstance()
{
    static XMLDocument instance;
    return instance;
}

/*void Misc::MyDocument::create(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inputXml << Qt::endl;
    }
    return;
}*/

void Misc::XMLDocument::write(const QString &filename, const QString &inputXml)
{

    return;
}


void Misc::XMLDocument::createNewNode(const QString &nodeName)
{
    return;
}


//=============================================================================
//== Function Name  :   XmlWriter::exists
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== fileName   const std::string   The name of the file that is in use
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to check if the XML file exists
//=============================================================================
bool Misc::XMLDocument::exists(const std::string fileName){
    std::fstream checkFile(fileName);
    return checkFile.is_open();
}
//=============================================================================
//== Function Name  :   XmlWriter::open
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== strFile    const std::string   The name of the file that the user passes
//==                                in the code
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to open the XML file, first checking to see if it
//== exists first
//=============================================================================
bool Misc::XMLDocument::open(const std::string strFile) {

    if (exists(strFile)){
        std::cout << "Error: File alread exists.\n";
        return false;
    }

    //std::ifstream xmlDocument(strFile);

    outFile.open(strFile);
    if (outFile.is_open()) {
        std::cout << "File created successfully.\n";
        outFile << "<!--XML Document-->\n";
        outFile << "<?xml version='1.0' encoding='us-ascii'>\n";
        indent = 0;
        openTags = 0;
        openElements = 0;
        return true;
    }

    return false;
}
//=============================================================================
//== Function Name  :   XmlWriter::close
//==
//== Perameters
//== Name       Type                Description
//== ---------- -----------         --------------------
//== N/a        N/a                 N/a
//==
//== Description
//== --------------------------------------------------------------------------
//== This function is used to close the XML file
//=============================================================================
void Misc::XMLDocument::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
    else {
        std::cout << "File already closed.\n";
    }

}
