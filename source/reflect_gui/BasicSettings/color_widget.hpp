/*!
  \file color_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_WIDGET_HPP_
#define _REFLECT_COLOR_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_color_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ColorWidget : public ReflectWidget
{
 public:
  //! Create color widget
  ColorWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

 private:
  //! Initialize
  void initialize();


  Ui::ColorWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_COLOR_WIDGET_HPP_
