/*!
  \file probabilistic_ppm_widget.cpp
  \author takemura
  */

#include "probabilistic_ppm_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "russian_roulette_widget.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_probabilistic_ppm.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ProbabilisticPpmWidget::ProbabilisticPpmWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ProbabilisticPpmWidget::readData(const QString& prefix, 
                                      const QSettings& settings)
{
  auto key = prefix + "/" + keyword::num_of_photons;
  const auto num_of_photons = settings.value(key, 100000);
  ui_.num_of_photons_spinbox->setValue(num_of_photons.toInt());

  key = prefix + "/" + keyword::initial_radius;
  const auto initial_radius = settings.value(key, 0.025);
  ui_.initial_radius_spinbox->setValue(initial_radius.toDouble());

  key = prefix + "/" + keyword::alpha;
  const auto alpha = settings.value(key, 0.666667);
  ui_.alpha_spinbox->setValue(alpha.toDouble());

  key = prefix + "/" + keyword::k;
  const auto k = settings.value(key, 10);
  ui_.k_spinbox->setValue(k.toInt());

  key = prefix + "/" + keyword::filter_kernel;
  const auto filter_type = settings.value(key, QString{keyword::no_kernel});
  ui_.filter_kernel_combobox->setCurrentText(filter_type.toString());
}

/*!
  \details
  No detailed.
  */
void ProbabilisticPpmWidget::writeData(const QString& prefix, 
                                       QSettings* settings) const
{
  writeTableData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ProbabilisticPpmWidget::initialize()
{
  ui_.setupUi(this);

  auto update_num_of_photons = [this](const int n)
  {
    ui_.num_of_photons_spinbox->setValue(n);
  };

  auto set_num_of_photons = [this, update_num_of_photons](const int n)
  {
    constexpr auto key = keyword::num_of_photons;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set number of photons to \"%1\".").arg(n);
      const int old_n = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, n, old_n, 
                                               update_num_of_photons};
      window->appendCommand(command);
    }
    table_[key].setValue(n);
  };
  connection_list_ << connectSpinBox(ui_.num_of_photons_spinbox, set_num_of_photons);
  set_num_of_photons(ui_.num_of_photons_spinbox->value());

  auto update_k = [this](const int k)
  {
    ui_.k_spinbox->setValue(k);
  };

  auto set_k = [this, update_k](const int k)
  {
    constexpr auto key = keyword::k;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set k of k-NN to \"%1\".").arg(k);
      const int old_k = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, k, old_k, update_k};
      window->appendCommand(command);
    }
    table_[key].setValue(k);
  };
  connection_list_ << connectSpinBox(ui_.k_spinbox, set_k);
  set_k(ui_.k_spinbox->value());

  auto update_initial_radius = [this](const double radius)
  {
    ui_.initial_radius_spinbox->setValue(radius);
  };

  auto set_initial_radius = [this, update_initial_radius](const double radius)
  {
    constexpr auto key = keyword::initial_radius;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = 
          QStringLiteral("Set initial radius to \"%1\".").arg(radius);
      const double old_radius = table_[key].toDouble();
      auto* command = new SetValueCommand<double>{text, radius, old_radius, 
                                                  update_initial_radius};
      window->appendCommand(command);
    }
    table_[key].setValue(radius);
  };
  connection_list_ << connectSpinBox(ui_.initial_radius_spinbox, set_initial_radius);
  set_initial_radius(ui_.initial_radius_spinbox->value());

  auto update_alpha = [this](const double alpha)
  {
    ui_.alpha_spinbox->setValue(alpha);
  };

  auto set_alpha = [this, update_alpha](const double alpha)
  {
    constexpr auto key = keyword::alpha;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set alpha to \"%1\".").arg(alpha);
      const double old_alpha = table_[key].toDouble();
      auto* command = 
          new SetValueCommand<double>{text, alpha, old_alpha, update_alpha};
      window->appendCommand(command);
    }
    table_[key].setValue(alpha);
  };
  connection_list_ << connectSpinBox(ui_.alpha_spinbox, set_alpha);
  set_alpha(ui_.alpha_spinbox->value());

  ui_.filter_kernel_combobox->addItem(keyword::no_kernel);
  ui_.filter_kernel_combobox->addItem(keyword::cone_kernel);
//  ui_.filter_kernel_combobox->addItem(keyword::gauss_kernel);
  ui_.filter_kernel_combobox->addItem(keyword::perlin_kernel);
  ui_.filter_kernel_combobox->setCurrentText(keyword::no_kernel);
  auto set_filter_kernel = [this](const int type)
  {
    constexpr auto key = keyword::filter_kernel;
    const auto current_type = ui_.filter_kernel_combobox->itemText(type);
    table_[key].setValue(current_type);
  };
  connection_list_ << connectComboBox(ui_.filter_kernel_combobox, set_filter_kernel);
  set_filter_kernel(ui_.filter_kernel_combobox->currentIndex());
}

} // namespace reflect
