/*!
  \file reflect_widget.cpp
  \author takemura
  */

#include "reflect_widget.hpp"
// Standard C++ library
#include <memory>
// Qt
#include <QWidget>
// Zisc
#include "zisc/error.hpp"
// ReflectGui
#include "reflect_main_window.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ReflectWidget::ReflectWidget(QWidget* parent) :
    QWidget(parent)
{
}

/*!
  \details
  No detailed.
  */
void ReflectWidget::activate()
{
  show();
}

/*!
  \details
  No detailed.
  */
void ReflectWidget::deactivate()
{
  hide();
}

/*!
  \details
  No detailed.
  */
void ReflectWidget::setMainWindows(ReflectMainWindow* main_window)
{
  if (main_window != nullptr && main_window_ != nullptr)
    zisc::raiseError("Main window was already created.");
  main_window_ = main_window;
}

/*!
  \details
  No detailed.
  */
ReflectMainWindow* ReflectWidget::mainWindow()
{
  if (main_window_ == nullptr)
    zisc::raiseError("Main window is not created.");
  return main_window_;
}

ReflectMainWindow* ReflectWidget::main_window_ = nullptr;

} // namespace reflect
