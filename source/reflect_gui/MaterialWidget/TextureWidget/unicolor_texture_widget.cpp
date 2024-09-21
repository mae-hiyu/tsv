/*!
  \file unicolor_texture_widget.cpp
  \author takemura
  */

#include "unicolor_texture_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "MaterialWidget/color_palette_widget.hpp"
// UI
#include "ui_unicolor_texture_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
UnicolorTextureWidget::UnicolorTextureWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void UnicolorTextureWidget::readData(const QString& prefix, 
                                     const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::color;
  color_palette_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void UnicolorTextureWidget::validateData(QStringList* error_message_list) const
{
  color_palette_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void UnicolorTextureWidget::writeData(const QString& prefix, 
                                      QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::color;
  color_palette_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void UnicolorTextureWidget::initialize()
{
  ui_.setupUi(this);

  color_palette_ = new ColorPaletteWidget{ui_.color_frame};
}

} // namespace reflect
