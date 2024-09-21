/*!
  \file unicolor_texture_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_UNICOLOR_TEXTURE_WIDGET_HPP_
#define _REFLECT_UNICOLOR_TEXTURE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_unicolor_texture_widget.h"

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
class UnicolorTextureWidget : public ReflectWidget
{
 public:
  //! Create a unicolor texture widget
  UnicolorTextureWidget(QWidget* parent);


  //! Raed data to a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* color_palette_;
  Ui::UnicolorTextureWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_UNICOLOR_TEXTURE_WIDGET_HPP_
