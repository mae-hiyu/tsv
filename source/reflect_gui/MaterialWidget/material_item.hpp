/*!
  \file material_item.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_ITEM_HPP_
#define _REFLECT_MATERIAL_ITEM_HPP_

// Qt
#include <QPointer>
#include <QString>
// ReflectGui
#include "material_item_type.hpp"
#include "reflect_widget.hpp"
#include "reflect_widget_item.hpp"

// Foward declaration
class QSettings;
class QStringList;
class QWidget;

namespace reflect {

// Forward declaration
template <MaterialItemType> class MaterialWidget;

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
class MaterialItem : public ReflectListItem
{
 public:
  //! Creaete a material item
  MaterialItem(MaterialWidget<kType>* material_widget);


  //! Activate the item
  void activate() override;

  //! Deactivate the item
  void deactivate() override;

  // Return the type name string
  static QString getTypeName();

  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_lsit) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  void initialize(QWidget* item_frame);

  
  QPointer<ReflectWidget> item_widget_;
};

using SurfaceModelItem = MaterialItem<MaterialItemType::SurfaceModel>;
using EmitterModelItem = MaterialItem<MaterialItemType::EmitterModel>;
using TextureItem = MaterialItem<MaterialItemType::Texture>;

} // namespace reflect

#include "material_item-inl.hpp"

#endif // _REFLECT_MATERIAL_ITEM_HPP_
