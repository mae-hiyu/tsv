/*!
  \file pinhole_camera_widget.cpp
  \author takemura
  */

#include "pinhole_camera_widget.hpp"
// Qt
#include <QDoubleSpinBox>
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_pinhole_camera_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
PinholeCameraWidget::PinholeCameraWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void PinholeCameraWidget::readData(const QString& prefix, 
                                   const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::angle_of_view;
  const auto angle_of_view = settings.value(key, 45.0);
  ui_.angle_spinbox->setValue(angle_of_view.toDouble());
}

/*!
  \details
  No detailed.
  */
void PinholeCameraWidget::initialize()
{
  ui_.setupUi(this);

  auto update_angle_of_view = [this](const double angle)
  {
    ui_.angle_spinbox->setValue(angle);
  };

  auto set_angle_of_view = [this, update_angle_of_view](const double angle)
  {
    constexpr auto key = keyword::angle_of_view;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set angle of view to %1.").arg(angle);
      const double old_angle = table_[key].toDouble();
      auto* command = new SetValueCommand<double>{text, angle, old_angle, 
                                                  update_angle_of_view};
      window->appendCommand(command);
    }
    table_[key].setValue(angle);
  };
  connection_list_ << connectSpinBox(ui_.angle_spinbox, set_angle_of_view);
  set_angle_of_view(ui_.angle_spinbox->value());
}

} // namespace reflect
