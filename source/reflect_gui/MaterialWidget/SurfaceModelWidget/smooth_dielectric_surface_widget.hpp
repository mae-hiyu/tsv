/*!
  \file smooth_dielectric_surface_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIELECTRIC_SURFACE_WIDGET_HPP_
#define _REFLECT_SMOOTH_DIELECTRIC_SURFACE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_smooth_dielectric_surface_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class SmoothDielectricSurfaceWidget : public ReflectWidget
{
 public:
  //! Create a smooth dielectric surface widget
  SmoothDielectricSurfaceWidget(QWidget* parent);


  //! Read data to  a settilg file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* exterior_refractive_index_widget_;
  ReflectWidget* interior_refractive_index_widget_;
  Ui::SmoothDielectricSurfaceWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SMOOTH_DIELECTRIC_SURFACE_WIDGET_HPP_
