/*!
  \file value.hpp
  \author takemura
  */

#ifndef _REFLECT_VALUE_HPP_
#define _REFLECT_VALUE_HPP_

// Reflect
#include "reflect_config.hpp"

// Forward declaration
class QString;
class QSettings;

namespace reflect {

//! \addtogroup Utility
//! \{

//! Return the value for settings key
template <typename Type>
Type value(const QSettings& settings, const QString& key);

//! Get index from the wavelength
constexpr std::size_t getIndex(const std::size_t wavelength)
{
  return (wavelength - kShortestWavelength) / kWavelengthResolution;
}

//! Get wavelength from the index
constexpr std::size_t getWavelength(const std::size_t index)
{
  return kShortestWavelength + index * kWavelengthResolution;
}

//! \} Utility

} // namespace reflect

#include "value-inl.hpp"

#endif // _REFLECT_VALUE_HPP_
