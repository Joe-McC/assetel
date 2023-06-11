#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include "xmlnode.h"

namespace Misc
{

class MyDocument : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???

public:
    static MyDocument &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);
    Q_INVOKABLE QString addNode(const QString &nodeText);

/*Q_SIGNALS:
    void myDocumentChanged();

protected:
    QString
*/
private:
    inline static std::map<QString, std::shared_ptr<XMLNode>> _nodeLookup;
    inline static int _uidCount;

    QString getNewUID();


};


}
#endif // MYDOCUMENT_H

