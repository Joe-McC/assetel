#include "treemodel.h"
#include "misc/mydocument.h"
#include <iostream>

TreeModel::TreeModel(QObject* parent)
   : QAbstractItemModel(parent),
     _rootItem{new TreeItem()}
{
    // Connect the signals to slots
    connect(&Misc::MyDocument::getInstance(), &Misc::MyDocument::topLevelNodeAdded, this, &TreeModel::handleTopLevelNodeAdded);
    connect(&Misc::MyDocument::getInstance(), &Misc::MyDocument::childNodeAdded, this, &TreeModel::handleChildNodeAdded);

}

TreeModel::~TreeModel()
{
   //delete _rootItem;
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid()){
      return _rootItem->childCount();
   }

   return internalPointer(parent)->childCount();
}

int TreeModel::columnCount(const QModelIndex&  /*parent*/) const
{
   // This is basically flatten as a list model
   return 1;
}

QModelIndex TreeModel::index(const int row, const int column, const QModelIndex& parent) const
{
   if (!hasIndex(row, column, parent)){
      return {};
   }

   auto item = _rootItem;

   //TreeItem* item = _rootItem;
   if (parent.isValid()){
      item = internalPointer(parent);
   }

   if (auto child = item->child(row)){
      return createIndex(row, column, child.get());
   }

   return {};
}

QModelIndex TreeModel::parent(const QModelIndex& index) const
{
   if (!index.isValid()){
      return {};
   }


   auto childItem = std::make_shared<TreeItem>(index);
   auto parentItem = childItem->parentItem();

   //TreeItem* childItem = internalPointer(index);
   //TreeItem* parentItem = childItem->parentItem();

   if (!parentItem){
      return {};
   }

   if (parentItem == _rootItem){
      return {};
   }

   return createIndex(parentItem->row(), 0, parentItem.get());
}

QVariant TreeModel::data(const QModelIndex& index, const int role) const
{
   if (!index.isValid() || role != Qt::DisplayRole) {
      return QVariant();
   }

   return internalPointer(index)->data();
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int /*role*/)
{
   if(!index.isValid()){
      return false;
   }

   if(auto item = internalPointer(index)){
      item->setData(value);
      emit dataChanged(index, index, {Qt::EditRole});
   }

   return false;
}

//???????? why do we add a child with a Top Level Item, is this correct????
void TreeModel::addTopLevelItem(std::shared_ptr<TreeItem> child)
{
   if(child){
      addItem(_rootItem, child);
   }
}

//void TreeModel::addItem(TreeItem* parent, TreeItem* child)
void TreeModel::addItem(std::shared_ptr<TreeItem> parent, std::shared_ptr<TreeItem> child)
{
   if(!child || !parent){
      return;
   }

   emit layoutAboutToBeChanged();

   if (child->parentItem()) {
      beginRemoveRows(QModelIndex(), child->parentItem()->childCount() - 1, child->parentItem()->childCount());
      child->parentItem()->removeChild(child);
      endRemoveRows();
   }

   beginInsertRows(QModelIndex(), parent->childCount() - 1, parent->childCount() - 1);
   child->setParentItem(parent);
   parent->appendChild(child);
   endInsertRows();

   emit layoutChanged();
}

void TreeModel::removeItem(std::shared_ptr<TreeItem> item)
{
   if(!item){
      return;
   }

   emit layoutAboutToBeChanged();

   if (item->parentItem()) {
      beginRemoveRows(QModelIndex(), item->parentItem()->childCount() - 1, item->parentItem()->childCount());
      item->parentItem()->removeChild(item);
      endRemoveRows();
   }

   emit layoutChanged();
}

std::shared_ptr<TreeItem> TreeModel::rootItem() const
{
   return _rootItem;
}

QModelIndex TreeModel::rootIndex()
{
   return {};
}

int TreeModel::depth(const QModelIndex& index) const
{
   int count = 0;
   auto anchestor = index;
   if(!index.isValid()){
      return 0;
   }
   while(anchestor.parent().isValid()){
      anchestor = anchestor.parent();
      ++count;
   }

   return count;
}

void TreeModel::clear()
{
   emit layoutAboutToBeChanged();
   beginResetModel();
   //delete _rootItem;
   //_rootItem = new TreeItem();
   _rootItem = std::make_shared<TreeItem>();
   endResetModel();
   emit layoutChanged();
}

/*TreeItem* TreeModel::internalPointer(const QModelIndex& index) const
{
   return static_cast<TreeItem* >(index.internalPointer());
}*/
std::shared_ptr<TreeItem> TreeModel::internalPointer(const QModelIndex& index) const
{
   auto ptr = reinterpret_cast<TreeItem*>(index.internalPointer());
   return std::shared_ptr<TreeItem>(ptr, [](TreeItem* item){});
}

void TreeModel::handleTopLevelNodeAdded(const int &nodeId)
{
    auto topLevelItem = std::make_shared<TreeItem>(nodeId);
    std::cout << "handleTopLevelNodeAdded: " << nodeId << std::endl;
    addTopLevelItem(topLevelItem);
}

void TreeModel::handleChildNodeAdded(const int &nodeId, const int &parentNodeId)
{
    auto parentItem = std::make_shared<TreeItem>(parentNodeId);
    auto childItem = std::make_shared<TreeItem>(nodeId);

    addItem(parentItem, childItem);
}
