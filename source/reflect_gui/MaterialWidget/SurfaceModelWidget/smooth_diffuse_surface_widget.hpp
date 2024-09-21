/*!
  \file smooth_diffuse_surface_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIFFUSE_SURFACE_WIDGET_HPP_
#define _REFLECT_SMOOTH_DIFFUSE_SURFACE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_smooth_diffuse_surface_widget.h"

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
class SmoothDiffuseSurfaceWidget : public ReflectWidget
{
 public:
  //! Create a smooth diffuse surface widget
  SmoothDiffuseSurfaceWidget(QWidget* parent);


  //! Raed data to a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* reflectance_widget_;
  Ui::SmoothDiffuseSurfaceWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SMOOTH_DIFFUSE_SURFACE_WIDGET_HPP_
