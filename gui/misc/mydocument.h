#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class MyDocument : public QObject
{
    Q_OBJECT
    //Q_PROPERTY???

public:
    explicit MyDocument(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filename, const QString &inputXml);

/*Q_SIGNALS:
    void myDocumentChanged();

protected:
    QString
*/




};

#endif // MYDOCUMENT_H
