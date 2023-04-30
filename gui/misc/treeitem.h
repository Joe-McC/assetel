#ifndef QML_TREEVIEW_TREE_ITEM_H
#define QML_TREEVIEW_TREE_ITEM_H

#include <QVariant>

/*!
 * This class represents a node of the TreeModel.
 * TreeItem can be used to set and retreive information about the node,
 * insertion and removal is meant to be deal by the model.
 */
class TreeItem
{
   friend class TreeModel;

public:
   //! Instance a tree item with empty data.
   TreeItem();

   //! Instance a tree with the input data.
   explicit TreeItem(const QVariant& data);

   //! Destroy the item and all its children.
   ~TreeItem();

   //! Return the internal data.
   const QVariant& data() const;

   //! Set the internal data.
   void setData(const QVariant& data);

   //! Return the number of children of the item.
   int childCount() const;

   //! Return the number of the row referred to the parent item.
   int row() const;

   //! Return true if the item has no children.
   bool isLeaf() const;

   //! Return the depth of the item in the hierarchy.
   int depth() const;

private:
   TreeItem* parentItem();
   void setParentItem(TreeItem* parentItem);

   void appendChild(TreeItem* item);
   void removeChild(TreeItem* item);

   TreeItem* child(int row);

private:
   QVariant _itemData;
   TreeItem* _parentItem;
   QVector<TreeItem*> _childItems;
};

#endif // QML_TREEVIEW_TREE_ITEM_H
