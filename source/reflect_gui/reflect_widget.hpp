/*!
  \file reflect_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_WIDGET_HPP_
#define _REFLECT_REFLECT_WIDGET_HPP_

// Standard C++ library
#include <memory>
// Qt
#include <QWidget>
// ReflectGui
#include "reflect_object.hpp"

namespace reflect {

// Forward declaration
class ReflectMainWindow;

/*!
  \details
  No detailed.
  */
class ReflectWidget : public ReflectObject, public QWidget
{
 public:
  //! Create reflect widget
  ReflectWidget(QWidget* parent);


  //! Activate the widget
  void activate() override;

  //! Deactivate the widget
  void deactivate() override;

  //! Set main windows
  static void setMainWindows(ReflectMainWindow* main_windows);

  //! Get main window
  static ReflectMainWindow* mainWindow();

 private:
  static ReflectMainWindow* main_window_;
};

} // namespace reflect

#endif // _REFLECT_REFLECT_WIDGET_HPP_
