#include "xmlprocessor.h"

namespace Misc
{
XMLProcessor::XMLProcessor(QFile filename)
{
    _XMLfilename.setFileName(filename.fileName()); //QFile does not have copy constructor so need to get string of filename and reset
}

std::vector<Misc::XMLNode> XMLProcessor::getNodes()
{
    std::vector<Misc::XMLNode> nodes;

    if (_XMLfilename.open(QIODevice::ReadWrite))
    {
        std::cout << "File Opened" << std::endl;
        //QTextStream stream(&file);
        //stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }
    return nodes;
}

void XMLProcessor::writeNodes(Misc::XMLNode parent)
{

}

}

