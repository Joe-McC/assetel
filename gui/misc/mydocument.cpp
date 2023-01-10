#include "mydocument.h"

/*Misc::MyDocument::MyDocument(QObject *parent)
    : QObject{parent}
{

}*/

/**
 * Returns the only instance of the class, this is to be used by the QML interface
 */

Misc::MyDocument &Misc::MyDocument::getInstance()
{
    static MyDocument instance;
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

void Misc::MyDocument::write(const QString &filename, const QString &inputXml)
{
    QFile file;
    file.setFileName(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inputXml << Qt::endl;
    }
    else
    {
        qDebug("File not opened!");
    }
    return;
}