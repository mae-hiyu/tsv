/*!
  \file string-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_STRING_INL_HPP_
#define _REFLECT_STRING_INL_HPP_

// Qt
#include <QString>
// Zisc
#include "zisc/type_traits.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <> inline
QString toQString<QString>(const QString& value)
{
  return value;
}

/*!
  \details
  No detailed.
  */
template <typename Type, zisc::EnableIfInteger<Type> = zisc::kEnabler> inline
QString toQString(const Type& value)
{
  return QString::number(value);
}

/*!
  \details
  No detailed.
  */
template <typename Type, zisc::EnableIfFloat<Type> = zisc::kEnabler> inline
QString toQString(const Type& value)
{
  return QString::number(value);
}

/*!
  \details
  No detailed.
  */
template <int N> inline
QString toQString(char const (&value) [N])
{
  return QString{value};
}

/*!
  \details
  No detailed.
  */
template <typename Type, typename ...Types> inline
QString toQString(const Type& value, const Types& ...values)
{
  return toQString(value) + toQString(values...);
}

} // namespace reflect

#endif // _REFLECT_STRING_INL_HPP_
