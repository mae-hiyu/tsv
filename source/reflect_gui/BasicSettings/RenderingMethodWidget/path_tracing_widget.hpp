/*!
  \file path_tracing_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_PATH_TRACING_WIDGET_HPP_
#define _REFLECT_PATH_TRACING_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_path_tracing_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class PathTracingWidget : public ReflectWidget
{
 public:
  //! Create a path tracing widget
  PathTracingWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  Ui::PathTracingWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_PATH_TRACING_WIDGET_HPP_
