/*!
  \file median_split_bvh_widget.cpp
  \author takemura
  */

#include "median_split_bvh_widget.hpp"
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
#include "ui_median_split_bvh_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
MedianSplitBvhWidget::MedianSplitBvhWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvhWidget::readData(const QString& prefix, 
                                    const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvhWidget::validateData(QStringList* error_message_list) const
{
  bvh_optimization_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvhWidget::writeData(const QString& prefix,
                                     QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::optimization;
  bvh_optimization_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvhWidget::initialize()
{
  ui_.setupUi(this);

  bvh_optimization_widget_ = new BvhOptimizationWidget{ui_.bvh_optimization_frame};
  bvh_optimization_widget_->activate();
}



} // namespace reflect
