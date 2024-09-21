/*!
  \file rendering_method_widget.cpp
  \author takemura
  */

#include "rendering_method_widget.hpp"
// Qt
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "BasicSettings/RenderingMethodWidget/path_tracing_widget.hpp"
#include "BasicSettings/RenderingMethodWidget/probabilistic_ppm_widget.hpp"
#include "BasicSettings/RenderingMethodWidget/russian_roulette_widget.hpp"
#include "Command/replace_widget_command.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_rendering_method_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
RenderingMethodWidget::RenderingMethodWidget(QWidget* parent) :
    ReflectWidget(parent),
    current_widget_{nullptr}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void RenderingMethodWidget::readData(const QString& prefix,   
                                     const QSettings& settings)
{
  auto key = prefix + "/" + keyword::ray_cast_epsilon;
  const auto epsilon = settings.value(key, 0.000001);
  ui_.ray_cast_epsilon_spinbox->setValue(epsilon.toDouble());

  key = prefix + "/" + keyword::rendering_method;
  const QString default_method{keyword::path_tracing_method};
  const auto method = settings.value(key, default_method);
  ui_.rendering_method_combobox->setCurrentText(method.toString());

  if (ui_.rendering_method_combobox->currentText() != method.toString())
    ui_.rendering_method_combobox->setCurrentText(default_method);

  QPointer<ReflectWidget> current_widget{current_widget_};
  if (!current_widget.isNull())
    delete current_widget;
  current_widget_ = makeRenderingMethodWidget(
      ui_.rendering_method_combobox->currentText());
  current_widget_->readData(prefix, settings);
  current_widget_->activate();

  key = prefix + "/" + keyword::russian_roulette;
  russian_roulette_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void RenderingMethodWidget::writeData(const QString& prefix, 
                                      QSettings* settings) const
{
  writeTableData(prefix, settings);
  current_widget_->writeData(prefix, settings);
  const auto key = prefix + "/" + keyword::russian_roulette;
  russian_roulette_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void RenderingMethodWidget::initialize()
{
  ui_.setupUi(this);

  ui_.rendering_method_combobox->addItem(keyword::path_tracing_method);
  ui_.rendering_method_combobox->addItem(keyword::probabilistic_ppm_method);
  ui_.rendering_method_combobox->addItem(keyword::tsv_rendering_method);
  ui_.rendering_method_combobox->addItem(keyword::tsv_probabilistic_ppm_method);
  ui_.rendering_method_combobox->addItem(keyword::tsv_light_rendering_method);
  ui_.rendering_method_combobox->setCurrentText(keyword::tsv_rendering_method);

  auto update_epsilon = [this](const double epsilon)
  {
    ui_.ray_cast_epsilon_spinbox->setValue(epsilon);
  };

  auto set_epsilon = [this, update_epsilon](const double epsilon)
  {
    constexpr auto key = keyword::ray_cast_epsilon;
    auto window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set ray cast epsilon to %1.").arg(epsilon);
      const double old_epsilon = table_[key].toDouble();
      auto command = 
          new SetValueCommand<double>{text, epsilon, old_epsilon, update_epsilon};
      window->appendCommand(command);
    }
    table_[key].setValue(epsilon);
  };
  connection_list_ << connectSpinBox(ui_.ray_cast_epsilon_spinbox, set_epsilon);
  set_epsilon(ui_.ray_cast_epsilon_spinbox->value());

  auto update_rendering_method = [this](const QString& method)
  {
    ui_.rendering_method_combobox->setCurrentText(method);
  };

  auto set_rendering_method = [this, update_rendering_method](const int method)
  {
    constexpr auto key = keyword::rendering_method;
    auto* window = ReflectWidget::mainWindow();
    const auto new_method = ui_.rendering_method_combobox->itemText(method);
    if (window->isEnabledCommandLogging()) {
      const auto text = 
          QStringLiteral("Set rendering method to \"%1\".").arg(new_method);
      const auto old_method = table_[key].toString();
      auto command = new SetValueCommand<QString>{text, new_method, old_method, 
                                                  update_rendering_method};

      auto* old_widget = current_widget_;
      window->disableCommandLogging();
      auto* new_widget = makeRenderingMethodWidget(new_method);
      window->enableCommandLogging();
      auto child = 
          new ReplaceWidgetCommand{"", old_widget, new_widget, &current_widget_};
      command->addChild(child);

      window->appendCommand(command);
    }
    table_[key].setValue(new_method);
  };

  connection_list_ <<
      connectComboBox(ui_.rendering_method_combobox, set_rendering_method);
  set_rendering_method(ui_.rendering_method_combobox->currentIndex());
  current_widget_ = 
      makeRenderingMethodWidget(ui_.rendering_method_combobox->currentText());

  russian_roulette_widget_ = new RussianRouletteWidget{ui_.russian_roulette_frame};
}

/*!
  \details
  No detailed.
  */
ReflectWidget* RenderingMethodWidget::makeRenderingMethodWidget(
    const QString& method)
{
  ReflectWidget* method_widget = nullptr;

  switch (zisc::toHash32(method.toStdString().c_str())) {
   case zisc::toHash32(keyword::path_tracing_method):
    method_widget = new PathTracingWidget{ui_.rendering_method_frame};
    break;
//   case zisc::toHash32(keyword::regularized_path_tracing_method):
//    method_widget = new RegularizedPathTracingWidget{ui_.rendering_method_frame};
//    break;
   case zisc::toHash32(keyword::probabilistic_ppm_method):
    method_widget = new ProbabilisticPpmWidget{ui_.rendering_method_frame};
    break;
   case zisc::toHash32(keyword::tsv_probabilistic_ppm_method):
    method_widget = new ProbabilisticPpmWidget{ui_.rendering_method_frame};
    break;
   case zisc::toHash32(keyword::tsv_rendering_method):
    method_widget = new PathTracingWidget{ui_.rendering_method_frame};
    break;
   case zisc::toHash32(keyword::tsv_light_rendering_method):
    method_widget = new PathTracingWidget{ui_.rendering_method_frame};
    break;
   default:
    zisc::raiseError("RenderingMethodError: Unsupported method is specified.");
    break;
  }

  return method_widget;
}

} // namespace reflect
