#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

namespace Misc
{
class XMLWriter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???

public:
    static XMLWriter &getInstance();
    //explicit MyDocument(QObject *parent = nullptr);

    //Q_INVOKABLE void xxx(const QString &xxx, const QString &xxx);

/*Q_SIGNALS:
    void myDocumentChanged();

protected:
    QString
*/




};

#endif // XMLWRITER_H
