/*!
  \file single_object_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SINGLE_OBJECT_WIDGET_HPP_
#define _REFLECT_SINGLE_OBJECT_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_single_object_item_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QWidget;

namespace reflect {

// Forward declaration
class TransformationWidget;

/*!
  \details
  No detailed.
  */
class SingleObjectWidget : public ReflectWidget
{
 public:
  //! Create single object item widget
  SingleObjectWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Initialize emitter combobox
  void initializeEmitterModelCombobox();

  //! Initialize surface scattering combobox
  void initializeSurfaceModelCombobox();


  bool is_updating_;
  TransformationWidget* transformation_widget_;
  Ui::SingleObjectItemWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SINGLE_OBJECT_WIDGET_HPP_
