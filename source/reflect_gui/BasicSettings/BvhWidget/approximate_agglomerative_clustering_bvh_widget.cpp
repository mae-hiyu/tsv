/*!
  \file approximate_agglomerative_clustering_bvh_widget.cpp
  \author takemura
  */

#include "approximate_agglomerative_clustering_bvh_widget.hpp"
// Qt
#include <QDoubleSpinBox>
#include <QSettings>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "bvh_optimization_widget.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
// UI
#include "ui_approximate_agglomerative_clustering_bvh_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ApproximateAgglomerativeClusteringBvhWidget::
    ApproximateAgglomerativeClusteringBvhWidget(QWidget* parent) :
        ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvhWidget::readData(
    const QString& prefix, const QSettings& settings)
{
  auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->readData(key, settings);

  key = prefix + "/" + keyword::delta;
  const auto delta = settings.value(key, 20);
  ui_.delta_spinbox->setValue(delta.toInt());

  key = prefix + "/" + keyword::epsilon;
  const auto epsilon = settings.value(key, 0.1);
  ui_.epsilon_spinbox->setValue(epsilon.toDouble());
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvhWidget::validateData(
    QStringList* error_message_list) const
{
  bvh_optimization_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvhWidget::writeData(
    const QString& prefix, QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->writeData(key, settings);

  writeTableData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvhWidget::initialize()
{
  ui_.setupUi(this);

  bvh_optimization_widget_ = new BvhOptimizationWidget{ui_.bvh_optimization_frame};
  bvh_optimization_widget_->activate();

  auto update_delta = [this](const int delta)
  {
    ui_.delta_spinbox->setValue(delta);
  };

  auto set_delta = [this, update_delta](const int delta)
  {
    constexpr auto key = keyword::delta;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set delta to %1.").arg(delta);
      const int old_delta = table_[key].toInt();
      auto* command = 
          new SetValueCommand<int>{text, delta, old_delta, update_delta};
      window->appendCommand(command);
    }
    table_[key].setValue(delta);
  };
  connection_list_ << connectSpinBox(ui_.delta_spinbox, set_delta);
  set_delta(ui_.delta_spinbox->value());

  auto update_epsilon = [this](const double epsilon)
  {
    ui_.epsilon_spinbox->setValue(epsilon);
  };

  auto set_epsilon = [this, update_epsilon](const double epsilon)
  {
    constexpr auto key = keyword::epsilon;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set epsilon to %1.").arg(epsilon);
      const double old_epsilon = table_[key].toDouble();
      auto* command = 
          new SetValueCommand<double>{text, epsilon, old_epsilon, update_epsilon};
      window->appendCommand(command);
    }
    table_[key].setValue(epsilon);
  };
  connection_list_ << connectSpinBox(ui_.epsilon_spinbox, set_epsilon);
  set_epsilon(ui_.epsilon_spinbox->value());
}

} // namespace reflect
