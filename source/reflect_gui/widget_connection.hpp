/*!
  \file widget_connection.hpp
  \author takemura
  */

#ifndef _REFLECT_WIDGET_CONNECTION_HPP_
#define _REFLECT_WIDGET_CONNECTION_HPP_

// Qt
#include <QMetaObject>
// Standard C++ library
#include <functional>

// Forward declaration
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
class QPushButton;
class QSpinBox;

namespace reflect {

//! Connect a checkbox with a function
QMetaObject::Connection connectCheckBox(QCheckBox* checkbox,
                                        const std::function<void (bool)>& function);

//! Connect a combobox with a function
QMetaObject::Connection connectComboBox(QComboBox* combobox,
                                        const std::function<void (int)>& function);

//! Connect a button with a function
QMetaObject::Connection connectButton(QPushButton* button,
                                      const std::function<void ()>& function);

//! Connect a spinbox with a function
QMetaObject::Connection connectSpinBox(QDoubleSpinBox* spinbox,
                                       const std::function<void (double)>& function);

//! Connect a spinbox with a function
QMetaObject::Connection connectSpinBox(QSpinBox* spinbox,
                                       const std::function<void (int)>& function);

} // namespace reflect

#endif // _REFLECT_WIDGET_CONNECTION_HPP_
