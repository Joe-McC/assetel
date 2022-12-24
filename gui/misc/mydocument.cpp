#include "mydocument.h"

MyDocument::MyDocument(QObject *parent)
    : QObject{parent}
{

}


void MyDocument::write(const QString &filename, const QString &inputXml)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inputXml << Qt::endl;
    }
    return;
}
