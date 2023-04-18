#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum TreeModelRoles
    {
        TreeModelRoleName = Qt::UserRole + 1,
        TreeModelRoleDescription
    };

    explicit TreeModel(const QString &data, QObject *parent = 0);
    ~TreeModel();

    /* QAbstractItemModel interface */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVariant newCustomType(const QString &text, int position);
    void setupModelData(const QStringList &lines, TreeItem *parent);

    TreeItem *rootItem;
    QHash<int, QByteArray> m_roleNameMapping;
};
//! [0]

#endif // TREEMODEL_H
