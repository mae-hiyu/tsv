/*!
  \file material_item-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_ITEM_INL_HPP_
#define _REFLECT_MATERIAL_ITEM_INL_HPP_

#include "material_item.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "material_item_type.hpp"
#include "material_item_widget.hpp"
#include "material_widget.hpp"
#include "reflect_widget_item.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
MaterialItem<kType>::MaterialItem(MaterialWidget<kType>* material_widget)
{
  initialize(material_widget->itemFrame());
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::activate()
{
  item_widget_->activate();
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::deactivate()
{
  item_widget_->deactivate();
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::readData(const QString& prefix, const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::name;
  const auto name = settings.value(key, getTypeName()).toString();
  setName(name);

  item_widget_->readData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::validateData(QStringList* error_message_lsit) const
{
  item_widget_->validateData(error_message_lsit);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::writeData(const QString& prefix, QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::name;
  settings->setValue(key, table_[keyword::name]);

  item_widget_->writeData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItem<kType>::initialize(QWidget* parent)
{
  setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
  setName(getTypeName());
  item_widget_ = new MaterialItemWidget<kType>{parent};
}

} // namespace reflect

#endif // _REFLECT_MATERIAL_ITEM_INL_HPP_
