/*!
  \file rgb_palette_widget.cpp
  \author takemura
  */

#include "rgb_palette_widget.hpp"
// Qt
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_rgb_palette_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
RgbPaletteWidget::RgbPaletteWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void RgbPaletteWidget::readData(const QString& prefix, const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::color;
  const auto color = settings.value(key, QColor{255, 255, 255});
  setColor(color.value<QColor>());
}

/*!
  \details
  No detailed.
  */
void RgbPaletteWidget::writeData(const QString& prefix, QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::color;
  settings->setValue(key, color_);
}

/*!
  \details
  No detailed.
  */
void RgbPaletteWidget::initialize()
{
  ui_.setupUi(this);

  auto set_color = [this](const QColor& color)
  {
    setColor(color);
  };

  auto select_color = [this, set_color]()
  {
    auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());

    const auto color = QColorDialog::getColor(color_, window);
    if (color == color_)
      return;

    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set RGB color to %1.").arg(color.name());
      auto* command = new SetValueCommand<QColor>{text, color, color_, set_color};
      window->appendCommand(command);
    }
  };
  connection_list_ << connectButton(ui_.palette_button, select_color);
  set_color(Qt::white);
}

/*!
  \details
  No detailed.
  */
void RgbPaletteWidget::setColor(const QColor& color)
{
  color_ = color;
  const auto style = ((QStringLiteral("background-color: rgb(%1, %2, %3);")
      .arg(color.red()))
      .arg(color.green()))
      .arg(color.blue());
  ui_.color_label->setStyleSheet(style);
}

} // namespace reflect
