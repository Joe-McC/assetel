#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <QFile>
#include <QTextStream>

namespace Misc
{
class XMLDocument : public QObject
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
    static XMLDocument &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE void createNewNode(const QString &nodeName);




    bool open(const std::string);
    void close();
    bool exists(const std::string);

};
}

#endif // XMLWRITER_H
