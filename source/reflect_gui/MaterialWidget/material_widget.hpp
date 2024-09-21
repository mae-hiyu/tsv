/*!
  \file material_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_WIDGET_HPP_
#define _REFLECT_MATERIAL_WIDGET_HPP_

// Qt
#include <QListWidget>
// ReflectGui
#include "material_item_type.hpp"
#include "material_list_manager.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_material_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
class MaterialWidget : public ReflectWidget
{
 public:
  //! Create a material widget
  MaterialWidget(QWidget* parent);

  //! Return the item frame
  QWidget* itemFrame() const;

  //! Return the material widget manager
  const MaterialListManager* manager() const;

  //! Return the material list widget
  QListWidget* materialListWidget() const;

  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write default setting
  static void setDefaultConfiguration(const QString& group, QSettings* settings);

  //! Validate data
  void validateData(QStringList* error_message_lsit) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  MaterialListManager manager_;
  Ui::MaterialWidget ui_;
};

using SurfaceModelWidget = MaterialWidget<MaterialItemType::SurfaceModel>;
using EmitterModelWidget = MaterialWidget<MaterialItemType::EmitterModel>;
using TextureWidget = MaterialWidget<MaterialItemType::Texture>;

} // namespace reflect

#include "material_widget-inl.hpp"

#endif // _REFLECT_MATERIAL_WIDGET_HPP_
