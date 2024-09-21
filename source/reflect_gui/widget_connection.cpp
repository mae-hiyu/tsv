/*!
  \file widget_connection.cpp
  \author takemura
  */

#include "widget_connection.hpp"
// Standard C++ library
#include <functional>
// Qt
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QMetaObject>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>

namespace reflect {

/*!
  \details
  No detailed.
  */
auto connectCheckBox(QCheckBox* checkbox, const std::function<void (bool)>& function)
    -> QMetaObject::Connection
{
  return QObject::connect(checkbox, &QCheckBox::toggled, function);
}

/*!
  \details
  No detailed.
  */
auto connectComboBox(QComboBox* combobox, const std::function<void (int)>& function)
    -> QMetaObject::Connection
{
  return QObject::connect(
      combobox,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      function);
}

/*!
  \details
  No detailed.
  */
auto connectButton(QPushButton* button, const std::function<void ()>& function)
    -> QMetaObject::Connection
{
  return QObject::connect(button, &QPushButton::clicked, function);
}

/*!
  \details
  No detailed.
  */
auto connectSpinBox(QDoubleSpinBox* spinbox, 
                    const std::function<void (double)>& function)
    -> QMetaObject::Connection
{
  return QObject::connect(
      spinbox, 
      static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
      function);
}

/*!
  \details
  No detailed.
  */
auto connectSpinBox(QSpinBox* spinbox, const std::function<void (int)>& function)
    -> QMetaObject::Connection
{
  return QObject::connect(
      spinbox,
      static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
      function);
}

} // namespace reflect
