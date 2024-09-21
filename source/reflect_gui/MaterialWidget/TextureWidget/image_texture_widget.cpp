/*!
  \file image_texture_widget.cpp
  \author takemura
  */

#include "image_texture_widget.hpp"
// Qt
#include <QFileInfo>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QSettings>
#include <QString>
#include <QStringList>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
// UI
#include "ui_image_texture_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ImageTextureWidget::ImageTextureWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ImageTextureWidget::readData(const QString& prefix,
                                  const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::image_file;
  const auto file_path = settings.value(key, QString{}).toString();
  setImageFile(file_path);
}

/*!
  \details
  No detailed.
  */
void ImageTextureWidget::validateData(QStringList* error_message_list) const
{
  const auto file_path = table_[keyword::image_file].toString();
  const QFileInfo file_info{file_path};
  if (!file_info.exists()) {
    const auto error_message =
        QStringLiteral("ImageTextureWidget: Image file \"%1\" is not exists.");
    (*error_message_list) << error_message.arg(file_path);
  }
}

/*!
  \details
  No detailed.
  */
void ImageTextureWidget::initialize()
{
  ui_.setupUi(this);

  auto open_image = [this]()
  {
    const QString caption{"Open image file"};
    auto* window = ReflectWidget::mainWindow();
    const auto file_path = window->getOpenFilePath(caption, ".", "");
    if (!file_path.isEmpty())
      setImageFile(file_path);
  };
  connection_list_ << connectButton(ui_.image_open_button, open_image);
}

/*!
  \details
  No detailed.
  */
void ImageTextureWidget::setImageFile(const QString& file_path)
{
  QImage image{file_path};
  if (!image.isNull()) {
    table_[keyword::image_file].setValue(file_path);
    const QFileInfo file_info{file_path};
    ui_.image_open_button->setText(file_info.fileName());

    const auto pixmap = QPixmap::fromImage(image);
    const auto view_size = ui_.image_viewer->size();
    ui_.image_viewer->setPixmap(pixmap.scaled(view_size, Qt::KeepAspectRatio));
  }
}

} // namespace reflect
