/*!
  \file smooth_conductor_surface_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_CONDUCTOR_SURFACE_WIDGET_HPP_
#define _REFLECT_SMOOTH_CONDUCTOR_SURFACE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_smooth_conductor_surface_widget.h"

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
class SmoothConductorSurfaceWidget : public ReflectWidget
{
 public:
  //! Create a smooth conductor surface widget
  SmoothConductorSurfaceWidget(QWidget* parent);


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
  ReflectWidget* interior_extinction_widget_;
  Ui::SmoothConductorSurfaceWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SMOOTH_CONDUCTOR_SURFACE_WIDGET_HPP_
