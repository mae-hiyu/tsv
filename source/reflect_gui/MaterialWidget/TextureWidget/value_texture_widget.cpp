/*!
  \file value_texture_widget.cpp
  \author takemura
  */

#include "value_texture_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_value_texture_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ValueTextureWidget::ValueTextureWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ValueTextureWidget::readData(const QString& prefix, const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::value;
  const auto value = settings.value(key, 0.5);
  ui_.value_spinbox->setValue(value.toDouble());
}

/*!
  \details
  No detailed.
  */
void ValueTextureWidget::validateData(QStringList* /* error_message_list */) const
{
}

/*!
  \details
  No detailed.
  */
void ValueTextureWidget::initialize()
{
  ui_.setupUi(this);

  auto update_value = [this](const double value)
  {
    ui_.value_spinbox->setValue(value);
  };

  auto set_value = [this, update_value](const double value)
  {
    constexpr auto key = keyword::value;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set value to %1.").arg(value);
      const double old_value = table_[key].toDouble();
      auto command = 
          new SetValueCommand<double>{text, value, old_value, update_value};
      window->appendCommand(command);
    }
    table_[key].setValue(value);
  };
  connection_list_ << connectSpinBox(ui_.value_spinbox, set_value);
  set_value(ui_.value_spinbox->value());
}

} // namespace reflect
