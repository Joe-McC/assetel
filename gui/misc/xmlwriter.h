#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <QFile>
#include <QTextStream>


#include <xmlnode.h>
#include <xmlelement.h>
#include <nodeconnector.h>


namespace Misc
{
class XMLWriter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???
    //Q_PROPERTY(bool isNightMode READ isNightMode WRITE setIsNightMode NOTIFY isNightModeChanged)
    Q_PROPERTY(float x_pos);
    Q_PROPERTY(float y_pos);
    //maybe use template here to set specific param?????
    //template <class T> void setParamter(T a, int n)
    //Q_INVOKABLE void setParamter(const QString &nodeName, type);
    QML_ELEMENT

    //template <typename T> T myMax(T x, T y)
    //{
    //    return (x > y) ? x : y;
    //}

    public:
    static XMLWriter &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE void createNewNode(const QString &nodeName);




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
    void setStartNode(XMLNode node);
    void setEndNode(XMLNode node);

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
