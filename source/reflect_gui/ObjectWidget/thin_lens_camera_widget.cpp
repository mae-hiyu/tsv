/*!
  \file thin_lens_camera_widget.cpp
  \author takemura
  */

#include "thin_lens_camera_widget.hpp"
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
#include "ui_thin_lens_camera_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ThinLensCameraWidget::ThinLensCameraWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ThinLensCameraWidget::readData(const QString& prefix, 
                                   const QSettings& settings)
{
  auto key = prefix + "/" + keyword::angle_of_view;
  const auto angle_of_view = settings.value(key, 45.0);
  ui_.angle_spinbox->setValue(angle_of_view.toDouble());

  key = prefix + "/" + keyword::aperture;
  const auto aperture = settings.value(key, 0.000001);
  ui_.aperture_spinbox->setValue(aperture.toDouble());

  key = prefix + "/" + keyword::focal_distance;
  const auto focal_distance = settings.value(key, 0.05);
  ui_.focal_distance_spinbox->setValue(focal_distance.toDouble());
}

/*!
  \details
  No detailed.
  */
void ThinLensCameraWidget::initialize()
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

  auto update_aperture = [this](const double aperture)
  {
    ui_.aperture_spinbox->setValue(aperture);
  };

  auto set_aperture = [this, update_aperture](const double aperture)
  {
    constexpr auto key = keyword::aperture;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set aperture to %1.").arg(aperture);
      const double old_aperture = table_[key].toDouble();
      auto* command = new SetValueCommand<double>{text, aperture, old_aperture,
                                                  update_aperture};
      window->appendCommand(command);
    }
    table_[key].setValue(aperture);
  };
  connection_list_ << connectSpinBox(ui_.aperture_spinbox, set_aperture);
  set_aperture(ui_.aperture_spinbox->value());

  auto update_focal_distance = [this](const double focal_distance)
  {
    ui_.focal_distance_spinbox->setValue(focal_distance);
  };

  auto set_focal_distance = [this, update_focal_distance](const double focal_distance)
  {
    constexpr auto key = keyword::focal_distance;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set focal_distance to %1.").arg(focal_distance);
      const double old_focal_distance = table_[key].toDouble();
      auto* command = new SetValueCommand<double>{text, 
                                                  focal_distance, 
                                                  old_focal_distance,
                                                  update_focal_distance};
      window->appendCommand(command);
    }
    table_[key].setValue(focal_distance);
  };
  connection_list_ << connectSpinBox(ui_.focal_distance_spinbox, set_focal_distance);
  set_focal_distance(ui_.focal_distance_spinbox->value());
}

} // namespace reflect
