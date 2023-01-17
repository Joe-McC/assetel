#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Misc
{
class XMLWriter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???


    public:
    static XMLWriter &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE void createNewNode(const QString &nodeName);

    //maybe use template here to set specific param?????
    Q_INVOKABLE void setParamter(const QString &nodeName, type);

    bool open(const std::string);
    void close();
    bool exists(const std::string);

/*Q_SIGNALS:
    void myDocumentChanged();

protected:
    QString
*/

};


}



// An ELement class is used by the Node class to create the pre-define ELements using the attributes set in the QML implementation.
class Element
{
//add new attribute
    Element();
    ~Element();
public:
    void addChildElement(const std::string &name);
    Element getParentElement(Element parentName);
    std::list<Element> getChildElements(Element parentName);
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



// An Node is a predefine xml structure which is popluated using data from the QML implementation.
class Node
{
//add new attribute
    Node(QString name);
    ~Node();
public:
    void setPosition(float x, float y);
    //int getUID(QString name) ?? do we need this??
    std::pair<float,float> getPosition(QString name);

};

class Connector
{
    //add new attribute
    Connector();
    ~Connector();
    public:
    void setStartNode(Element node);
    void setEndNode(Element node);

};




/*
class Attribute
{
    Attribute(const std::string &name);
    ~Attribute();
    void addValue(const std::string &value);
    std::string getValue();
};

*/

#endif // XMLWRITER_H
