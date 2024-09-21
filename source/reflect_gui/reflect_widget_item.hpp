/*!
  \file reflect_widget_item.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_WIDGET_ITEM_HPP_
#define _REFLECT_REFLECT_WIDGET_ITEM_HPP_

// Qt
#include <QListWidgetItem>
#include <QString>
#include <QTreeWidgetItem>
// ReflectGui
#include "reflect_object.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename WidgetItem>
class ReflectWidgetItem : public ReflectObject, public WidgetItem
{
 public:
  //! Get the item name
  QString name() const;

  //! Set the item name
  void setName(const QString& name);
};

using ReflectListItem = ReflectWidgetItem<QListWidgetItem>;
using ReflectTreeItem = ReflectWidgetItem<QTreeWidgetItem>;

} // namespace reflect

#endif // _REFLECT_REFLECT_WIDGET_ITEM_HPP_
