/*!
  \file camera_object_widget.cpp
  \author takemura
  */

#include "camera_object_widget.hpp"
// Qt
#include <QCheckBox>
#include <QComboBox>
#include <QPointer>
#include <QRegularExpression>
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "pinhole_camera_widget.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "thin_lens_camera_widget.hpp"
#include "widget_connection.hpp"
#include "Command/replace_widget_command.hpp"
#include "Command/set_value_command.hpp"
#include "TransformationWidget/transformation_widget.hpp"
// UI
#include "ui_camera_item_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
CameraObjectWidget::CameraObjectWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void CameraObjectWidget::readData(const QString& prefix, 
                                  const QSettings& settings)
{
  // Camera
  auto key = prefix + "/" + keyword::camera_model;
  const auto camera_model = settings.value(key, QString{keyword::pinhole_camera});
  ui_.camera_model_combobox->setCurrentText(camera_model.toString());

  QPointer<ReflectWidget> current_widget{current_widget_};
  if (!current_widget.isNull())
    delete current_widget;
  current_widget_ = makeCameraWidget(camera_model.toString());
  current_widget_->activate();
  current_widget_->readData(prefix, settings);

  // Film
  key = prefix + "/" + keyword::image_size;
  const auto image_size = settings.value(key, QString{keyword::vga_size});
  ui_.size_template_combobox->setCurrentText(image_size.toString());

  key = prefix + "/" + keyword::jittering;
  const auto jittering = settings.value(key, true);
  ui_.jittering_checkbox->setChecked(jittering.toBool());

  key = prefix + "/" + keyword::transformation;
  transformation_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void CameraObjectWidget::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);
  current_widget_->writeData(prefix, settings);
  const auto key = prefix + "/" + keyword::transformation;
  transformation_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void CameraObjectWidget::initialize()
{
  ui_.setupUi(this);

  transformation_widget_ = new TransformationWidget{ui_.transformation_frame};
  transformation_widget_->setScalingEnabled(false);

  // Camera
  ui_.camera_model_combobox->addItem(keyword::pinhole_camera);
  ui_.camera_model_combobox->addItem(keyword::thin_lens_camera);
  ui_.camera_model_combobox->setCurrentText(keyword::pinhole_camera);

  auto update_camera_model = [this](const QString& type)
  {
    ui_.camera_model_combobox->setCurrentText(type);
  };

  auto set_camera_model = [this, update_camera_model](const int type)
  {
    constexpr auto key = keyword::camera_model;
    auto* window = ReflectWidget::mainWindow();
    const auto new_type = ui_.camera_model_combobox->itemText(type);
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set camera type to \"%1\".").arg(new_type);
      const auto old_type = table_[key].toString();
      auto* command = new SetValueCommand<QString>{text, new_type, old_type, 
                                                   update_camera_model};

      auto* old_widget = current_widget_;
      window->disableCommandLogging();
      auto* new_widget = makeCameraWidget(new_type);
      window->enableCommandLogging();
      auto* child =
        new ReplaceWidgetCommand{"", old_widget, new_widget, &current_widget_};
      command->addChild(child);

      window->appendCommand(command);
    }
    table_[key].setValue(new_type);
  };
  connection_list_ << connectComboBox(ui_.camera_model_combobox, set_camera_model);
  set_camera_model(ui_.camera_model_combobox->currentIndex());
  current_widget_ = makeCameraWidget(ui_.camera_model_combobox->currentText());

  // Film
  ui_.size_template_combobox->addItem(keyword::vga_size);
  ui_.size_template_combobox->addItem(keyword::svga_size);
  ui_.size_template_combobox->addItem(keyword::qvga_size);
  ui_.size_template_combobox->addItem(keyword::qhd_size);
  ui_.size_template_combobox->addItem(keyword::fwxga_size);
  ui_.size_template_combobox->addItem(keyword::full_hd_size);
  ui_.size_template_combobox->addItem(keyword::wqhd_size);
  ui_.size_template_combobox->setCurrentText(keyword::vga_size);
  auto set_image_size = [this](const int type)
  {
    constexpr auto key = keyword::image_size;
    const auto current_type = ui_.size_template_combobox->itemText(type);
    table_[key].setValue(current_type);

    const QRegularExpression pattern{R"(.*\((\d+)x(\d+)\))"};
    const auto match = pattern.match(ui_.size_template_combobox->currentText());
    const int width = match.captured(1).toInt();
    const int height = match.captured(2).toInt();
    ui_.width_spinbox->setValue(width);
    ui_.height_spinbox->setValue(height);
    table_[keyword::image_width].setValue(width);
    table_[keyword::image_height].setValue(height);
  };
  connection_list_ << connectComboBox(ui_.size_template_combobox, set_image_size);
  set_image_size(ui_.size_template_combobox->currentIndex());

  auto enable_jittering = [this](const bool enabled)
  {
    constexpr auto key = keyword::jittering;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.jittering_checkbox, enable_jittering);
  enable_jittering(ui_.jittering_checkbox->isChecked());
}

/*!
  \details
  No detailed.
  */
ReflectWidget* CameraObjectWidget::makeCameraWidget(const QString& type)
{
  ReflectWidget* camera_widget = nullptr;

  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::pinhole_camera):
    camera_widget = new PinholeCameraWidget{ui_.camera_widget_frame};
    break;
   case zisc::toHash32(keyword::thin_lens_camera):
    camera_widget = new ThinLensCameraWidget{ui_.camera_widget_frame};
    break;
   default:
    zisc::raiseError("CameraError: Unsupported type is specified.");
    break;
  }
  return camera_widget;
}

} // namespace reflect
