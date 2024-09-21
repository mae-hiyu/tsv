/*!
  \file thin_lens_camera_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_THIN_LENS_CAMERA_WIDGET_HPP_
#define _REFLECT_THIN_LENS_CAMERA_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_thin_lens_camera_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ThinLensCameraWidget : public ReflectWidget
{
 public:
  //! Create a thin lens camera widget
  ThinLensCameraWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

 private:
  //! Initialize
  void initialize();


  Ui::ThinLensCameraWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_THIN_LENS_CAMERA_WIDGET_HPP_
