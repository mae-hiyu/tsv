/*!
  \file system_widget.cpp
  \author takemura
  */

#include "system_widget.hpp"
// Qt
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSettings>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QtGlobal>
#include <QTime>
#include <QThread>
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
#include "ui_system_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SystemWidget::SystemWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SystemWidget::readData(const QString& prefix, const QSettings& settings)
{
  auto key = prefix + "/" + keyword::scene_name;
  const auto scene_name = settings.value(key, QStringLiteral("Scene"));
  ui_.scene_name_editor->setText(scene_name.toString());
  table_[keyword::scene_name].setValue(scene_name);

  key = prefix + "/" + keyword::random_seed;
  const auto random_seed = settings.value(key, 0);
  ui_.random_seed_spinbox->setValue(random_seed.toInt());

  key = prefix + "/" + keyword::num_of_threads;
  const auto num_of_threads = settings.value(key, 1);
  ui_.thread_spinbox->setValue(num_of_threads.toInt());

  key = prefix + "/" + keyword::open_cl;
  const auto enable_open_cl = settings.value(key, false);
  ui_.open_cl_checkbox->setChecked(enable_open_cl.toBool());

  key = prefix + "/" + keyword::open_cl_cpu;
  const auto use_open_cl_cpu = settings.value(key, false);
  ui_.open_cl_cpu_checkbox->setChecked(use_open_cl_cpu.toBool());
  
  key = prefix + "/" + keyword::open_cl_use_multiple_gpus;
  const auto use_multiple_gpus = settings.value(key, false);
  ui_.open_cl_use_multiple_gpus_checkbox->setChecked(use_multiple_gpus.toBool());

  key = prefix + "/" + keyword::ldr_image_format;
  const auto ldr_image_format = settings.value(key, QString{keyword::png_format});
  ui_.ldr_image_format_combobox->setCurrentText(ldr_image_format.toString());
  
  key = prefix + "/" + keyword::spectra_image_saving;
  const auto enable_spectra_image_saving = settings.value(key, false);
  ui_.spectra_image_checkbox->setChecked(enable_spectra_image_saving.toBool());

  key = prefix + "/" + keyword::hdr_image_saving;
  const auto enable_hdr_image_saving = settings.value(key, false);
  ui_.hdr_image_checkbox->setChecked(enable_hdr_image_saving.toBool());

  key = prefix + "/" + keyword::saving_image_at_power_of_2_of_pass;
  const auto enable_saving_image_at_power_of_2_of_pass = settings.value(key, true);
  ui_.image_saving_checkbox->setChecked(
      enable_saving_image_at_power_of_2_of_pass.toBool());

  key = prefix + "/" + keyword::saving_interval;
  const auto saving_interval = settings.value(key, 600000);
  ui_.image_saving_interval_spinbox->setValue(saving_interval.toInt());

  key = prefix + "/" + keyword::termination_pass;
  const auto termination_pass = settings.value(key, 0);
  ui_.termination_pass_spinbox->setValue(termination_pass.toInt());
}

/*!
  \details
  No detailed.
  */
QString SystemWidget::sceneName() const
{
  return table_[keyword::scene_name].toString();
}

/*!
  \details
  No detailed.
  */
void SystemWidget::validateData(QStringList* error_message_list) const
{
  if (sceneName().isEmpty())
    (*error_message_list) << "Scene name is empry.";
}

/*!
  \details
  No detailed.
  */
void SystemWidget::initialize()
{
  ui_.setupUi(this);

  // Scene name
  auto update_scene_name = [this](const QString& scene_name)
  {
    ui_.scene_name_editor->setText(scene_name);
  };

  auto set_scene_name = [this, update_scene_name]()
  {
    constexpr auto key = keyword::scene_name;
    const auto old_name = table_[key].toString();
    const auto name = ui_.scene_name_editor->text();
    if (name == old_name)
      return;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set scene name to \"%1\".").arg(name);
      auto* command = 
          new SetValueCommand<QString>{text, name, old_name, update_scene_name};
      window->appendCommand(command);
    }
    table_[key].setValue(name);
  };
  connection_list_ <<
      connect(ui_.scene_name_editor, &QLineEdit::editingFinished, set_scene_name);
  table_[keyword::scene_name].setValue(ui_.scene_name_editor->text());

  // Random seed
  auto update_random_seed = [this](const int seed)
  {
    ui_.random_seed_spinbox->setValue(seed);
  };

  auto set_random_seed = [this, update_random_seed](const int seed)
  {
    constexpr auto key = keyword::random_seed;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set random seed to %1.").arg(seed);
      const int old_seed = table_[key].toInt();
      auto* command = 
          new SetValueCommand<int>{text, seed, old_seed, update_random_seed};
      window->appendCommand(command);
    }
    table_[key].setValue(seed);
  };
  connection_list_ << connectSpinBox(ui_.random_seed_spinbox, set_random_seed);
  set_random_seed(ui_.random_seed_spinbox->value());

  auto set_random_seed_randomly = [this]()
  {
    const int seed = qrand();
    ui_.random_seed_spinbox->setValue(seed);
  };
  connection_list_ << connectButton(ui_.random_button, set_random_seed_randomly);
  const int srand_seed = QTime{0, 0, 0, 0}.msecsTo(QTime::currentTime());
  qsrand(cast<unsigned int>(srand_seed));

  // Thread setting
  auto update_num_of_threads = [this](const int n)
  {
    ui_.thread_spinbox->setValue(n);
  };

  auto set_num_of_threads = [this, update_num_of_threads](const int n)
  {
    constexpr auto key = keyword::num_of_threads;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set number of threads to %1.").arg(n);
      const int old_n = table_[key].toInt();
      auto* command = 
          new SetValueCommand<int>{text, n, old_n, update_num_of_threads};
      window->appendCommand(command);
    }
    table_[key].setValue(n);
  };
  connection_list_ << connectSpinBox(ui_.thread_spinbox, set_num_of_threads);

  auto set_num_of_logical_threads = [this]()
  {
    const int n = QThread::idealThreadCount();
    if (n > 0) {
      ui_.thread_spinbox->setValue(n);
    }
    else {
      auto* window = mainWindow();
      emit window->printMessage("Can't get the number of logical threads");
    }
  };
  connection_list_ << 
      connectButton(ui_.thread_auto_button, set_num_of_logical_threads);
  set_num_of_logical_threads();

  // OpenCL setting
  auto enable_open_cl = [this](const bool enabled)
  {
    constexpr auto key = keyword::open_cl;
    table_[key].setValue(enabled);
#ifdef REFLECT_OPENCL
    ui_.open_cl_cpu_checkbox->setEnabled(enabled);
    ui_.open_cl_use_multiple_gpus_checkbox->setEnabled(enabled);
#else // REFLECT_OPENCL
    ui_.open_cl_cpu_checkbox->setEnabled(false);
    ui_.open_cl_use_multiple_gpus_checkbox->setEnabled(false);
#endif // REFLECT_OPENCL
  };
  connection_list_ << connectCheckBox(ui_.open_cl_checkbox, enable_open_cl);
  enable_open_cl(ui_.open_cl_checkbox->isChecked());

  auto use_open_cl_cpu = [this](const bool enabled)
  {
    constexpr auto key = keyword::open_cl_cpu;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.open_cl_cpu_checkbox, use_open_cl_cpu);
  use_open_cl_cpu(ui_.open_cl_cpu_checkbox->isChecked());

  auto open_cl_use_multiple_gpus = [this](const bool enabled)
  {
    constexpr auto key = keyword::open_cl_use_multiple_gpus;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.open_cl_use_multiple_gpus_checkbox,
                                      open_cl_use_multiple_gpus);
  open_cl_use_multiple_gpus(ui_.open_cl_use_multiple_gpus_checkbox->isChecked());

#ifndef REFLECT_OPENCL
  ui_.open_cl_checkbox->setEnabled(false);
  ui_.open_cl_cpu_checkbox->setEnabled(false);
  ui_.open_cl_use_multiple_gpus_checkbox->setEnabled(false);
#endif // REFLECT_OPENCL

  // Spectra image saving
  auto enable_spectra_image_saving = [this](const bool enabled)
  {
    constexpr auto key = keyword::spectra_image_saving;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.spectra_image_checkbox, 
                                      enable_spectra_image_saving);
  enable_spectra_image_saving(ui_.spectra_image_checkbox->isChecked());

  // HDR image saving
  auto enable_hdr_image_saving = [this](const bool enabled)
  {
    constexpr auto key = keyword::hdr_image_saving;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.hdr_image_checkbox, 
                                      enable_hdr_image_saving);
  enable_hdr_image_saving(ui_.hdr_image_checkbox->isChecked());

  // Image setting
  auto enable_saving_image_at_power_of_2_of_pass = [this](const bool enabled)
  {
    constexpr auto key = keyword::saving_image_at_power_of_2_of_pass;
    table_[key].setValue(enabled);
  };
  connection_list_ << 
      connectCheckBox(ui_.image_saving_checkbox,
                      enable_saving_image_at_power_of_2_of_pass);
  enable_saving_image_at_power_of_2_of_pass(ui_.image_saving_checkbox->isChecked());

  auto update_saving_interval = [this](const int interval)
  {
    ui_.image_saving_interval_spinbox->setValue(interval);
  };

  auto set_saving_interval = [this, update_saving_interval](const int interval)
  {
    constexpr auto key = keyword::saving_interval;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text =
          QStringLiteral("Set saving image interval to %1").arg(interval);
      const int old_interval = table_[key].toInt();
      auto* command = new SetValueCommand<int>(text, interval, old_interval, 
                                               update_saving_interval);
      window->appendCommand(command);
    }
    table_[key].setValue(interval);
  };
  connection_list_ << connectSpinBox(ui_.image_saving_interval_spinbox,
                                     set_saving_interval);
  set_saving_interval(ui_.image_saving_interval_spinbox->value());

  // LDR image format
  ui_.ldr_image_format_combobox->addItem(keyword::png_format);
  ui_.ldr_image_format_combobox->addItem(keyword::bmp_format);
  ui_.ldr_image_format_combobox->addItem(keyword::ppm_format);
  ui_.ldr_image_format_combobox->setCurrentText(keyword::png_format);

  auto set_ldr_image_format = [this](const int format)
  {
    constexpr auto key = keyword::ldr_image_format;
    const auto new_format = ui_.ldr_image_format_combobox->itemText(format);
    table_[key].setValue(new_format);
  };
  connection_list_ 
      << connectComboBox(ui_.ldr_image_format_combobox, set_ldr_image_format);
  set_ldr_image_format(ui_.ldr_image_format_combobox->currentIndex());

  auto update_termination_pass = [this](const int pass)
  {
    ui_.termination_pass_spinbox->setValue(pass);
  };

  auto set_termination_pass = [this, update_termination_pass](const int pass)
  {
    constexpr auto key = keyword::termination_pass;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set termination pass to %1").arg(pass);
      const int old_pass = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, pass, old_pass, 
                                               update_termination_pass};
      window->appendCommand(command);
    }
    table_[key].setValue(pass);
  };
  connection_list_ << connectSpinBox(ui_.termination_pass_spinbox,
                                     set_termination_pass);
  set_termination_pass(ui_.termination_pass_spinbox->value());
}

} // namespace reflect
