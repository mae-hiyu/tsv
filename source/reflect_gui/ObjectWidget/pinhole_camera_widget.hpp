/*!
  \file pinhole_camera_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_PINHOLE_CAMERA_WIDGET_HPP_
#define _REFLECT_PINHOLE_CAMERA_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_pinhole_camera_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class PinholeCameraWidget : public ReflectWidget
{
 public:
  //! Create a pinhole camera widget
  PinholeCameraWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

 private:
  //! Initialize
  void initialize();


  Ui::PinholeCameraWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_PINHOLE_CAMERA_WIDGET_HPP_
