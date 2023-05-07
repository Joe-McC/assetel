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
    //int Misc::MyDocument::_uidCount++;
    //std::map<QString, std::shared_ptr<XMLNode>> Misc::MyDocument::_nodeLookup;
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

QString Misc::MyDocument::addNode()
{
    Misc::MyDocument::_uidCount++;//  ::_uidCount++;
    XMLNode node;
    auto nodePtr = std::make_shared<XMLNode>(node);
    QString uid = getNewUID();
    Misc::MyDocument::_nodeLookup.insert(std::pair<QString, std::shared_ptr<XMLNode>>(uid, nodePtr));
    return uid;
}


QString Misc::MyDocument::getNewUID()
{
   std::string uid = std::to_string(_uidCount);
   const int num = 3;

   if(uid.size() < num)
   {
       uid.insert(0, num - uid.size(), '0');
   }
   return QString::fromStdString(uid);
}
