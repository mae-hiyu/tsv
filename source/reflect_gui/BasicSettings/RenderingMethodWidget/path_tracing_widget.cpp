/*!
  \file path_tracing_widget.cpp
  \author takemura
  */

#include "path_tracing_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_path_tracing_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
PathTracingWidget::PathTracingWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void PathTracingWidget::readData(const QString& /* prefix */,
                                 const QSettings& /* settings */)
{
}

/*!
  \details
  No detailed.
  */
void PathTracingWidget::writeData(const QString& /* prefix */, 
                                  QSettings* /* settings */) const
{
}

/*!
  \details
  No detailed.
  */
void PathTracingWidget::initialize()
{
  ui_.setupUi(this);
}

} // namespace reflect
