#ifndef PARENTSMODEL_H
#define PARENTSMODEL_H

#include <QAbstractListModel>
#include <QList>


namespace Misc
{

class ParentsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct ParentItem {
        QString nodeId;
        QString displayText;
    };

    enum Role {
        NodeIdRole = Qt::UserRole + 1,
        DisplayTextRole
    };

    ParentsModel(QObject* parent = nullptr);

    void setParents(const QList<ParentItem>& parents);

    Q_INVOKABLE void addParentItem(const QString& nodeId, const QString& displayText);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(int count READ count NOTIFY countChanged)

    int count() const;

signals:
    void countChanged();



private:
    QList<ParentItem> m_parents;
};

}

#endif // PARENTSMODEL_H
