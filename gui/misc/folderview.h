#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QStandardItemModel>
#include <QStandardItem>

class FolderView : public QStandardItemModel
{
public:
    FolderView(QObject* parent = 0);
    ~FolderView();

    void setSandBoxDetails(QString names);
    void populateSandBoxes(const QStringList &names);
    void createDirectoryItem(QString dirName, QStandardItem *parentItem = NULL);

private:
    QStandardItem *rootItem;
    QIcon dirIcon;
    QIcon fileIcon;
};


#endif // FOLDERVIEW_H
