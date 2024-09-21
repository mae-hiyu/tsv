/*!
  \file non_directional_emitter_widget.cpp
  \author takemura
  */

#include "non_directional_emitter_widget.hpp"
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
#include "Command/set_value_command.hpp"
#include "MaterialWidget/color_palette_widget.hpp"
// UI
#include "ui_non_directional_emitter_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
NonDirectionalEmitterWidget::NonDirectionalEmitterWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void NonDirectionalEmitterWidget::readData(const QString& prefix, 
                                           const QSettings& settings)
{
  auto key = prefix + "/" + keyword::radiant_emittance;
  const auto radiant_emittance = settings.value(key, 10.0);
  ui_.radiant_emittance_spinbox->setValue(radiant_emittance.toDouble());

  key = prefix + "/" + keyword::property;
  color_palette_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void NonDirectionalEmitterWidget::validateData(QStringList* error_message_list) const
{
  color_palette_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void NonDirectionalEmitterWidget::writeData(const QString& prefix, 
                                            QSettings* settings) const
{
  auto key = prefix + "/" + keyword::radiant_emittance;
  settings->setValue(key, table_[keyword::radiant_emittance]);

  key = prefix + "/" + keyword::property;
  color_palette_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void NonDirectionalEmitterWidget::initialize()
{
  ui_.setupUi(this);

  color_palette_ = new ColorPaletteWidget{ui_.property_frame};

  auto update_radiant_emittance = [this](const double radiant_emittance)
  {
    ui_.radiant_emittance_spinbox->setValue(radiant_emittance);
  };

  auto set_radiant_emittance = 
  [this, update_radiant_emittance](const double radiant_emittance)
  {
    constexpr auto key = keyword::radiant_emittance;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set radiant emittance to %1.").arg(
          radiant_emittance);
      const double old_radiant_emittance = table_[key].toDouble();
      auto* command = new SetValueCommand<double>{text, 
                                                  radiant_emittance,
                                                  old_radiant_emittance,
                                                  update_radiant_emittance};
      window->appendCommand(command);
    }
    table_[key].setValue(radiant_emittance);
  };
  connection_list_ << 
      connectSpinBox(ui_.radiant_emittance_spinbox, set_radiant_emittance);
  set_radiant_emittance(ui_.radiant_emittance_spinbox->value());
}

} // namespace reflect
