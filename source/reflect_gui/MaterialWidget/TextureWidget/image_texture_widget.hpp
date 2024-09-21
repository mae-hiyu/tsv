/*!
  \file image_texture_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_IMAGE_TEXTURE_WIDGET_HPP_
#define _REFLECT_IMAGE_TEXTURE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_image_texture_widget.h"

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
class ImageTextureWidget : public ReflectWidget
{
 public:
  //! Create a image texture widget
  ImageTextureWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

 private:
  //! Initialize
  void initialize();

  //! Set image file path
  void setImageFile(const QString& file_path);


  Ui::ImageTextureWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_IMAGE_TEXTURE_WIDGET_HPP_
