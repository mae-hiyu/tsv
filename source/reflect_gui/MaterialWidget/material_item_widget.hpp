/*!
  \file material_item_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_ITEM_WIDGET_HPP_
#define _REFLECT_MATERIAL_ITEM_WIDGET_HPP_

// Qt
#include <QStringList>
// ReflectGui
#include "material_item_type.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_material_item_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
class MaterialItemWidget : public ReflectWidget
{
 public:
  //! Create material item widget
  MaterialItemWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_lsit) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* current_widget_;
  Ui::MaterialItemWidget ui_;
};

//! Return the material type list
template <MaterialItemType kType>
QStringList getMaterialTypeList();

//! Make a material item widget
template <MaterialItemType kType>
ReflectWidget* makeMaterialItemWidget(QWidget* parent, const QString& type);

} // namespace reflect

#include "material_item_widget-inl.hpp"

#endif // _REFLECT_MATERIAL_ITEM_WIDGET_HPP_
