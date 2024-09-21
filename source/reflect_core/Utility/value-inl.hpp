/*!
  \file value-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_VALUE_INL_HPP_
#define _REFLECT_VALUE_INL_HPP_

#include "value.hpp"
// Zisc
#include "zisc/error.hpp"
// Qt
#include <QSettings>
#include <QString>

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename Type> inline
Type value(const QSettings& settings, const QString& key)
{
  if (!settings.contains(key)) {
    zisc::raiseError("ValueError: Setting file doesn't have the value for the key \"",
                     key.toStdString(), "\"");
  }
  return settings.value(key).value<Type>();
}

} // namespace reflect

#endif // _REFLECT_VALUE_INL_HPP_
