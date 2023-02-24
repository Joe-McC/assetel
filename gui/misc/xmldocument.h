#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>

namespace Misc
{
class XMLDocument : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???
    //Q_PROPERTY(bool isNightMode READ isNightMode WRITE setIsNightMode NOTIFY isNightModeChanged)
    //Q_PROPERTY(float xPos READ xPos WRITE xPos NOTIFY isXPosChanged)
    //Q_PROPERTY(float yPos READ yPos WRITE yPos NOTIFY isYPosChanged)

    //maybe use template here to set specific param?????
    //template <class T> void setParamter(T a, int n)
    //Q_INVOKABLE void setParamter(const QString &nodeName, type);
    QML_ELEMENT

    //template <typename T> T myMax(T x, T y)
    //{
    //    return (x > y) ? x : y;
    //}

public:
    static XMLDocument &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE void createNewNode(const QString &nodeName);

    bool open(const std::string);
    void close();
    bool exists(const std::string);

private:
    std::ofstream outFile;
    int indent;
    int openTags;
    int openElements;
    std::vector<std::string> tempOpenTag;
    std::vector<std::string> tempElementTag;
    //float xPos;
    //float yPos;
};
}

#endif // XMLWRITER_H
