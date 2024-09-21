/*!
  \file checkerboard_texture_widget.cpp
  \author takemura
  */

#include "checkerboard_texture_widget.hpp"
// Qt
#include <QSettings>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "widget_connection.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
#include "MaterialWidget/color_palette_widget.hpp"
// UI
#include "ui_checkerboard_texture_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
CheckerboardTextureWidget::CheckerboardTextureWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void CheckerboardTextureWidget::readData(const QString& prefix, 
                                         const QSettings& settings)
{
  auto key = prefix + "/" + keyword::width;
  const auto width = settings.value(key, 5);
  ui_.width_number_spinbox->setValue(width.toInt());

  key = prefix + "/" + keyword::height;
  const auto height = settings.value(key, 5);
  ui_.height_number_spinbox->setValue(height.toInt());

  key = prefix + "/" + keyword::color1;
  color1_palette_->readData(key, settings);
  key = prefix + "/" + keyword::color2;
  color2_palette_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void CheckerboardTextureWidget::validateData(QStringList* error_message_list) const
{
  color1_palette_->validateData(error_message_list);
  color2_palette_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void CheckerboardTextureWidget::writeData(const QString& prefix,
                                          QSettings* settings) const
{
  writeTableData(prefix, settings);
  auto key = prefix + "/" + keyword::color1;
  color1_palette_->writeData(key, settings);
  key = prefix + "/" + keyword::color2;
  color2_palette_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void CheckerboardTextureWidget::initialize()
{
  ui_.setupUi(this);

  auto update_width_number = [this](const int number)
  {
    ui_.width_number_spinbox->setValue(number);
  };

  auto set_width_number = [this, update_width_number](const int number)
  {
    constexpr auto key = keyword::width;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set the width number to %1.").arg(number);
      const int old_number = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, number, old_number, 
                                               update_width_number};
      window->appendCommand(command);
    }
    table_[key].setValue(number);
  };
  connection_list_ << connectSpinBox(ui_.width_number_spinbox, set_width_number);
  set_width_number(ui_.width_number_spinbox->value());

  auto update_height_number = [this](const int number)
  {
    ui_.height_number_spinbox->setValue(number);
  };

  auto set_height_number = [this, update_height_number](const int number)
  {
    constexpr auto key = keyword::height;
    auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set the height number to %1.").arg(number);
      const int old_number = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, number, old_number,
                                               update_height_number};
      window->appendCommand(command);
    }
    table_[key].setValue(number);
  };
  connection_list_ << connectSpinBox(ui_.height_number_spinbox, set_height_number);
  set_height_number(ui_.height_number_spinbox->value());

  color1_palette_ = new ColorPaletteWidget{ui_.color1_frame};
  color2_palette_ = new ColorPaletteWidget{ui_.color2_frame};
}

} // namespace reflect
