/*!
  \file color_widget.cpp
  \author takemura
  */

#include "color_widget.hpp"
// Qt
#include <QCheckBox>
#include <QComboBox>
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
#include "ui_color_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ColorWidget::ColorWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ColorWidget::readData(const QString& prefix, const QSettings& settings)
{
  QString key;

  key = prefix + "/" + keyword::rgb_rendering;
  const auto is_rgb_rendering = settings.value(key, false);
  ui_.rgb_checkbox->setChecked(is_rgb_rendering.toBool());

  key = prefix + "/" + keyword::standard_observer;
  const auto standard_observer = settings.value(key);
  ui_.standard_observer_combobox->setCurrentText(standard_observer.toString());

  key = prefix + "/" + keyword::standard_illuminant;
  const auto standard_illuminant = settings.value(key);
  ui_.standard_illuminant_combobox->setCurrentText(standard_illuminant.toString());

  key = prefix + "/" + keyword::spectrum_sampling;
  const auto spectrum_sampling = settings.value(key);
  ui_.spectrum_sampling_combobox->setCurrentText(spectrum_sampling.toString());

  key = prefix + "/" + keyword::color_space;
  const auto color_space = settings.value(key);
  ui_.color_space_combobox->setCurrentText(color_space.toString());

  key = prefix + "/" + keyword::gamma;
  const auto gamma = settings.value(key, 2.2);
  ui_.gamma_spinbox->setValue(gamma.toDouble());

  key = prefix + "/" + keyword::tonemapping;
  const auto tonemapping = settings.value(key);
  ui_.tonemapping_combobox->setCurrentText(tonemapping.toString());
}

/*!
  \details
  No detailed.
  */
void ColorWidget::initialize()
{
  ui_.setupUi(this);

  auto enable_rgb_rendering = [this](const bool enabled)
  {
    constexpr auto key = keyword::rgb_rendering;
    table_[key].setValue(enabled);
    ui_.spectrum_sampling_combobox->setEnabled(!enabled);
  };
  connection_list_ << connectCheckBox(ui_.rgb_checkbox, enable_rgb_rendering);
  enable_rgb_rendering(ui_.rgb_checkbox->isChecked());

  ui_.standard_observer_combobox->addItem(keyword::cie2_cmf);
  ui_.standard_observer_combobox->addItem(keyword::cie10_cmf);
  ui_.standard_observer_combobox->setCurrentText(keyword::cie2_cmf);
  auto set_standard_observer = [this](const int type)
  {
    constexpr auto key = keyword::standard_observer;
    const auto current_type = ui_.standard_observer_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ <<
      connectComboBox(ui_.standard_observer_combobox, set_standard_observer);
  set_standard_observer(ui_.standard_observer_combobox->currentIndex());

  ui_.standard_illuminant_combobox->addItem(keyword::cie_d65);
  ui_.standard_illuminant_combobox->addItem(keyword::cie_a);
  ui_.standard_illuminant_combobox->setCurrentText(keyword::cie_d65);
  auto set_standard_illuminant = [this](const int type)
  {
    constexpr auto key = keyword::standard_illuminant;
    const auto current_type = ui_.standard_illuminant_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ <<
      connectComboBox(ui_.standard_illuminant_combobox, set_standard_illuminant);
  set_standard_illuminant(ui_.standard_illuminant_combobox->currentIndex());

  ui_.spectrum_sampling_combobox->addItem(keyword::regular_sampling);
  ui_.spectrum_sampling_combobox->addItem(keyword::random_sampling);
  ui_.spectrum_sampling_combobox->addItem(keyword::stratified_sampling);
  ui_.spectrum_sampling_combobox->addItem(
      keyword::lights_based_importance_sampling);
  ui_.spectrum_sampling_combobox->addItem(
      keyword::materials_based_importance_sampling);
  ui_.spectrum_sampling_combobox->addItem(
      keyword::lights_and_materials_plus_based_importance_sampling);
  ui_.spectrum_sampling_combobox->addItem(
      keyword::lights_and_materials_multi_based_importance_sampling);
  ui_.spectrum_sampling_combobox->addItem(keyword::tristimulus_values_importance_sampling);
  ui_.spectrum_sampling_combobox->addItem(keyword::lights_and_tsv_multi_based_importance_sampling);
  ui_.spectrum_sampling_combobox->setCurrentText(keyword::stratified_sampling);
  auto set_spectrum_sampling = [this](const int type)
  {
    constexpr auto key = keyword::spectrum_sampling;
    const auto current_type = ui_.spectrum_sampling_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ <<
      connectComboBox(ui_.spectrum_sampling_combobox, set_spectrum_sampling);
  set_spectrum_sampling(ui_.spectrum_sampling_combobox->currentIndex());

  ui_.color_space_combobox->addItem(keyword::srgb_d65);
  ui_.color_space_combobox->addItem(keyword::srgb_d50);
  ui_.color_space_combobox->addItem(keyword::adobe_rgb_d65);
  ui_.color_space_combobox->addItem(keyword::adobe_rgb_d50);
  ui_.color_space_combobox->setCurrentText(keyword::srgb_d65);
  auto set_color_space = [this](const int type)
  {
    constexpr auto key = keyword::color_space;
    const auto current_type = ui_.color_space_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ << connectComboBox(ui_.color_space_combobox, set_color_space);
  set_color_space(ui_.color_space_combobox->currentIndex());

  auto update_gamma = [this](const double gamma)
  {
    ui_.gamma_spinbox->setValue(gamma);
  };

  auto set_gamma = [this, update_gamma](const double gamma)
  {
    constexpr auto key = keyword::gamma;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set gamma value to %1.").arg(gamma);
      const double old_gamma = table_[key].toDouble();
      auto* command = 
          new SetValueCommand<double>{text, gamma, old_gamma, update_gamma};
      window->appendCommand(command);
    }
    table_[key].setValue(gamma);
  };
  connection_list_ << connectSpinBox(ui_.gamma_spinbox, set_gamma);
  set_gamma(ui_.gamma_spinbox->value());

  ui_.tonemapping_combobox->addItem(keyword::simplified_reinhard);
  ui_.tonemapping_combobox->setCurrentText(keyword::simplified_reinhard);
  auto set_tonemapping = [this](const int type)
  {
    constexpr auto key = keyword::tonemapping;
    const auto current_type = ui_.tonemapping_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ << connectComboBox(ui_.tonemapping_combobox, set_tonemapping);
  set_tonemapping(ui_.tonemapping_combobox->currentIndex());
}

} // namespace reflect
