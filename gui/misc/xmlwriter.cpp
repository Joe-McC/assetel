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
