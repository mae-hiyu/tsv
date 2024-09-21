/*!
  \file binary_radix_bvh_widget.cpp
  \author takemura
  */

#include "binary_radix_bvh_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "bvh_optimization_widget.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_binary_radix_bvh_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
BinaryRadixBvhWidget::BinaryRadixBvhWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvhWidget::readData(const QString& prefix, 
                                    const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvhWidget::validateData(QStringList* error_message_list) const
{
  bvh_optimization_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvhWidget::writeData(const QString& prefix,
                                     QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvhWidget::initialize()
{
  ui_.setupUi(this);

  bvh_optimization_widget_ = new BvhOptimizationWidget{ui_.bvh_optimization_frame};
  bvh_optimization_widget_->activate();
}

} // namespace reflect
