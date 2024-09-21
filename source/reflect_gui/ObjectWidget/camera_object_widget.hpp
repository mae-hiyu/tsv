/*!
  \file camera_object_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_CAMERA_OBJECT_WIDGET_HPP_
#define _REFLECT_CAMERA_OBJECT_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_camera_item_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

// Forward declaration
class TransformationWidget;

/*!
  \details
  No detailed.
  */
class CameraObjectWidget : public ReflectWidget
{
 public:
  //! Create camera object item widget
  CameraObjectWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write date to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Make a camera widget
  ReflectWidget* makeCameraWidget(const QString& type);


  ReflectWidget* current_widget_;
  TransformationWidget* transformation_widget_;
  Ui::CameraItemWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_CAMERA_OBJECT_WIDGET_HPP_
