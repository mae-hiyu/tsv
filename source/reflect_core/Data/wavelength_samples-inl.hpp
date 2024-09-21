/*!
  \file wavelength_samples-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_WAVELENGTH_SAMPLE_INL_HPP_
#define _REFLECT_WAVELENGTH_SAMPLE_INL_HPP_

#include "wavelength_samples.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSamples<kSampleSize>::WavelengthSamples() :
    primary_index_{0}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t& WavelengthSamples<kSampleSize>::operator[](const std::size_t index)
{
  return wavelengths_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
const std::size_t& WavelengthSamples<kSampleSize>::operator[](const std::size_t index)
  const
{
  return wavelengths_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t WavelengthSamples<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(wavelengths_);
  size += PRINT_VARIABLE_DATA(primary_index_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t WavelengthSamples<kSampleSize>::primaryWavelengthIndex() const
{
  return primary_index_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void WavelengthSamples<kSampleSize>::setPrimaryWavelength(const std::size_t index)
{
  primary_index_ = index;
}

template <std::size_t kSampleSize> inline
void WavelengthSamples<kSampleSize>::setXYZwavelength(const std::size_t wavelength, const std::size_t index)
{
  wavelengths_[index] = wavelength;
}

} // namespace reflect

#endif // _REFLECT_WAVELENGTH_SAMPLE_INL_HPP_
