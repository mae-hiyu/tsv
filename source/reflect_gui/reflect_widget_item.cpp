/*!
  \file reflect_widget_item.cpp
  \author takemura
  */

#include "reflect_widget_item.hpp"
// Qt
#include <QListWidgetItem>
#include <QString>
#include <QTreeWidgetItem>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_object.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <>
QString ReflectListItem::name() const
{
  return table_[keyword::name].toString();
}

/*!
  \details
  No detailed.
  */
template <>
QString ReflectTreeItem::name() const
{
  return table_[keyword::name].toString();
}

/*!
  \details
  No detailed.
  */
template <>
void ReflectListItem::setName(const QString& name)
{
  table_[keyword::name].setValue(name);
  setText(name);
}

/*!
  \details
  No detailed.
  */
template <>
void ReflectTreeItem::setName(const QString& name)
{
  table_[keyword::name].setValue(name);
  setText(0, name);
}

} // namespace reflect
