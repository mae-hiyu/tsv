/*!
  \file bvh_optimization_widget.cpp
  \author takemura
  */

#include "bvh_optimization_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_bvh_optimization_widget.h"

namespace reflect {
 
/*!
  \details
  No detailed.
  */
BvhOptimizationWidget::BvhOptimizationWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  current_widget_ = nullptr;
  initialize();
}

/*!
  \details
  No detailed.
  */
void BvhOptimizationWidget::initialize()
{
  ui_.setupUi(this);
}

} // namespace reflect
