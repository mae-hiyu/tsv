/*!
  \file russian_roulette_widget.cpp
  \author takemura
  */

#include "russian_roulette_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_russian_roulette_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
RussianRouletteWidget::RussianRouletteWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void RussianRouletteWidget::readData(const QString& prefix,   
                                     const QSettings& settings)
{
  auto key = prefix + "/" + keyword::type;
  const QString default_method{keyword::reflectance_max};
  const auto russian_roulette = settings.value(key, default_method);
  ui_.russian_roulette_combobox->setCurrentText(russian_roulette.toString());

  key = prefix + "/" + keyword::path_length_max;
  const auto path_length_max = settings.value(key, 3);
  ui_.path_length_max_spinbox->setValue(path_length_max.toInt());
}

/*!
  \details
  No detailed.
  */
void RussianRouletteWidget::initialize()
{
  ui_.setupUi(this);

  ui_.russian_roulette_combobox->addItem(keyword::path_length);
  ui_.russian_roulette_combobox->addItem(keyword::reflectance_average);
  ui_.russian_roulette_combobox->addItem(keyword::reflectance_max);
  ui_.russian_roulette_combobox->setCurrentText(keyword::reflectance_max);
  auto set_russian_roulette = [this](const int type)
  {
    constexpr auto key = keyword::type;
    const auto current_type = ui_.russian_roulette_combobox->itemText(type);
    table_[key].setValue(current_type);
    ui_.path_length_max_spinbox->setEnabled(current_type == keyword::path_length);
  };
  connection_list_ <<
      connectComboBox(ui_.russian_roulette_combobox, set_russian_roulette);
  set_russian_roulette(ui_.russian_roulette_combobox->currentIndex());

  auto update_path_length_max = [this](const int length)
  {
    ui_.path_length_max_spinbox->setValue(length);
  };

  auto set_path_length_max = [this, update_path_length_max](const int length)
  {
    constexpr auto key = keyword::path_length_max;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = 
          QStringLiteral("Set path length max to \"%1\".").arg(length);
      const int old_length = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, length, old_length, 
                                               update_path_length_max};
      window->appendCommand(command);
    }
    table_[key].setValue(length);
  };
  connection_list_ <<
      connectSpinBox(ui_.path_length_max_spinbox, set_path_length_max);
  set_path_length_max(ui_.path_length_max_spinbox->value());
}

} // namespace reflect
