#include "xmlwriter.h"


/*Misc::MyDocument::MyDocument(QObject *parent)
    : QObject{parent}
{

}*/

/**
 * Returns the only instance of the class, this is to be used by the QML interface
 */

Misc::XMLWriter &Misc::XMLWriter::getInstance()
{
    static XMLWriter instance;
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

void Misc::XMLWriter::write(const QString &filename, const QString &inputXml)
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
bool Misc::XMLWriter::exists(const std::string fileName){
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
bool Misc::XMLWriter::open(const std::string strFile) {

    if (exists(strFile)){
        std::cout << "Error: File alread exists.\n";
        return false;
    }

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
void Misc::XMLWriter::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
    else {
        std::cout << "File already closed.\n";
    }

}
