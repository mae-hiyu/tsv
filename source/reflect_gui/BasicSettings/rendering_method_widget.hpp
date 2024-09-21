/*!
  \file rendering_method_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERING_METHOD_WIDGET_HPP_
#define _REFLECT_RENDERING_METHOD_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_rendering_method_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class RenderingMethodWidget : public ReflectWidget
{
 public:
  //! Create rendering method widget
  RenderingMethodWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& preifx, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Make a rendering method widget
  ReflectWidget* makeRenderingMethodWidget(const QString& method);


  ReflectWidget* current_widget_;
  ReflectWidget* russian_roulette_widget_;
  Ui::RenderingMethodWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_RENDERING_METHOD_WIDGET_HPP_
