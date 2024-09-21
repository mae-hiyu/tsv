/*!
  \file floating_point-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_FLOATING_PONIT_INL_HPP_
#define _REFLECT_FLOATING_PONIT_INL_HPP_

#include "floating_point.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool isBetweenZeroAndOneFloat(const SampledSpectra<kSampleSize>& sample)
{
  for (std::size_t index = 0; index < sample.size(); ++index) {
    const double intensity = sample.intensity(index);
    if (!isBetweenZeroAndOneFloat(intensity))
      return false;
  }
  return true;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool isInfFloat(const SampledSpectra<kSampleSize>& sample)
{
  for (std::size_t index = 0; index < sample.size(); ++index) {
    const double intensity = sample.intensity(index);
    if (isInfFloat(intensity))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool isNanFloat(const SampledSpectra<kSampleSize>& sample)
{
  for (std::size_t index = 0; index < sample.size(); ++index) {
    const double intensity = sample.intensity(index);
    if (isNanFloat(intensity))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool isNegativeFloat(const SampledSpectra<kSampleSize>& sample)
{
  for (std::size_t index = 0; index < sample.size(); ++index) {
    const double intensity = sample.intensity(index);
    if (isNegativeFloat(intensity))
      return true;
  }
  return false;
}

} // namespace reflect

#endif // _REFLECT_FLOATING_PONIT_INL_HPP_
