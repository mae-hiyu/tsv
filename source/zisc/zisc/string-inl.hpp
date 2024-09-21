/*!
 \file string-inl.hpp
 \author takemura
 */

#ifndef _ZISC_STRING_INL_HPP_
#define _ZISC_STRING_INL_HPP_

#include "string.hpp"
// Standard C++ library
#include <regex>
#include <string>
#include <type_traits>
// Zisc
#include "type_traits.hpp"

namespace zisc {

/*!
 \details
 No detailed.
 */
inline
bool toBoolean(const std::string& string)
{
  return string == "true";
}

/*!
  \details
  No detailed.
  */
template <> inline
float toFloat(const std::string& string)
{
  return std::stof(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
double toFloat(const std::string& string)
{
  return std::stod(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
long double toFloat(const std::string& string)
{
  return std::stold(string);
}

/*!
 \details
 No detailed.
 */
template <typename Float> inline
Float toFloat(const std::string& /* string */)
{
  static_assert(IsFloat<Float>::value, "## Template must be floating point type.");
  return static_cast<Float>(0);
}

/*!
  \details
  No detailed.
  */
template <> inline
int toInteger(const std::string& string)
{
  return std::stoi(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
long toInteger(const std::string& string)
{
  return std::stol(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
long long toInteger(const std::string& string)
{
  return std::stoll(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
unsigned long toInteger(const std::string& string)
{
  return std::stoul(string);
}

/*!
  \details
  No detailed.
  */
template <> inline
unsigned long long toInteger(const std::string& string)
{
  return std::stoull(string);
}

/*!
 \details
 No detailed.
 */
template <typename Integer> inline
Integer toInteger(const std::string& /* string */)
{
  static_assert(IsInteger<Integer>::value, "## Template must be integer type.");
  return static_cast<Integer>(0);
}

/*!
 \details
 No detailed.
 */
inline
bool isBooleanString(const std::string& string)
{
  return string == "true" || string == "false";
}

/*!
 \details
 No detailed.
 */
inline
bool isFloatString(const std::string& string)
{
  const std::regex floating_point{"[-+]?\\d*\\.?\\d*([eE][-+]?\\d+)?"};
  return std::regex_match(string, floating_point);
}

/*!
 \details
 No detailed.
 */
inline
bool isIntegerString(const std::string& string)
{
  const std::regex integral{"[-+]?([1-9]\\d*|0)"};
  return std::regex_match(string, integral);
}

/*!
 \details
 No detailed.
 */
inline
bool isUnsignedIntegerString(const std::string& string)
{
  const std::regex unsigned_integral{"[1-9]\\d*|0"};
  return std::regex_match(string, unsigned_integral);
}

} // namespace zisc

#endif // _Z_STRING_INL_HPP__
