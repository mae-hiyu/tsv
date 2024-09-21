/*!
  \file smooth_plastic_surface_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_PLASTIC_SURFACE_WIDGET_HPP_
#define _REFLECT_SMOOTH_PLASTIC_SURFACE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_smooth_plastic_surface_widget.h"

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
class SmoothPlasticSurfaceWidget : public ReflectWidget
{
 public:
  //! Create a rough dielectric surface widget
  SmoothPlasticSurfaceWidget(QWidget* parent);


  //! Read data to  a settilg file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* diffuse_reflectance_widget_;
  ReflectWidget* exterior_refractive_index_widget_;
  ReflectWidget* interior_refractive_index_widget_;
  Ui::SmoothPlasticSurfaceWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SMOOTH_PLASTIC_SURFACE_WIDGET_HPP_
