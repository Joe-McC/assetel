#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <xmlelement.h>

class XMLNode: public QObject
{
public:
    XMLNode();

    Q_OBJECT

    Q_PROPERTY(float x READ x WRITE)
    Q_PROPERTY(float y READ y WRITE)

    QML_ELEMENT

    void addElement(QString name);
    //std::pair<float, float> getPosition();
    void setPosition(std::pair<float, float>);



private:
    //std::pair<float, float> m_Pos;
    //std::vector<std::shared_ptr<QObject>> m_ChildList;
};

#endif // TEST_H
