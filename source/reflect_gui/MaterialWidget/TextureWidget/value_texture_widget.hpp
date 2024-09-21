/*!
  \file value_texture_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_VALUE_TEXTURE_WIDGET_HPP_
#define _REFLECT_VALUE_TEXTURE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_value_texture_widget.h"

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
class ValueTextureWidget : public ReflectWidget
{
 public:
  //! Create a value texture widget
  ValueTextureWidget(QWidget* parent);


  //! Raed data to a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const;

 private:
  //! Initialize
  void initialize();


  Ui::ValueTextureWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_VALUE_TEXTURE_WIDGET_HPP_
