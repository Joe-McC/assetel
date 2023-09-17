#ifndef XMLNODE_H
#define XMLNODE_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtQml/qqmlregistration.h>
#include <xmlelement.h>


namespace Misc
{

class XMLNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nodeTitle READ getNodeTitle WRITE setNodeTitle NOTIFY nodeTitleChanged)
    Q_PROPERTY(QString nodeText READ getNodeText WRITE setNodeText NOTIFY nodeTextChanged)
    Q_PROPERTY(QString nodeParentID READ getNodeParentID WRITE setNodeParentID NOTIFY nodeParentIDChanged)
    Q_PROPERTY(QString nodeUID READ getNodeUID WRITE setNodeUID NOTIFY nodeUIDChanged)
    Q_PROPERTY(QString nodeXPosition READ getNodeXPosition WRITE setNodeXPosition NOTIFY nodeXPositionChanged)
    Q_PROPERTY(QString nodeYPosition READ getNodeYPosition WRITE setNodeYPosition NOTIFY nodeYPositionChanged)

public:
    XMLNode();

    void setNodeTitle(const QString &title);
    QString getNodeTitle();

    void setNodeText(const QString &nodeText);
    QString getNodeText();

    void setNodeParentID(const QString &parentID);
    QString getNodeParentID();

    void setNodeUID(const QString &nodeUID);
    QString getNodeUID();

    void setNodeXPosition(const QString &nodeXPosition);
    QString getNodeXPosition();

    void setNodeYPosition(const QString &nodeYPosition);
    QString getNodeYPosition();

    void addChild(const QString &nodeText);

    QString _nodeUID;

signals:
    void nodeTitleChanged();
    void nodeTextChanged();
    void nodeParentIDChanged();
    void nodeUIDChanged();
    void nodeXPositionChanged();
    void nodeYPositionChanged();
private:
    QString _nodeTitle;
    QString _nodeText;
    QString _nodeParentID;
    QString _nodeXPosition;
    QString _nodeYPosition;
};

}
#endif // XMLNODE_H
