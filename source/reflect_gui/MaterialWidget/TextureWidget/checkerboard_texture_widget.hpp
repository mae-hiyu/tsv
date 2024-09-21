/*!
  \file checkerboard_texture_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_CHECKERBOARD_TEXTURE_WIDGET_HPP_
#define _REFLECT_CHECKERBOARD_TEXTURE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_checkerboard_texture_widget.h"

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
class CheckerboardTextureWidget : public ReflectWidget
{
 public:
  //! Create a checkerboard texture widget
  CheckerboardTextureWidget(QWidget* parent);


  //! Read data to a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* color1_palette_;
  ReflectWidget* color2_palette_;
  Ui::CheckerboardTextureWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_CHECKERBOARD_TEXTURE_WIDGET_HPP_
