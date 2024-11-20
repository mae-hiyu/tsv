/*!
  \file xyz_color_matching_function-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_INL_HPP_
#define _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_INL_HPP_

#include "xyz_color_matching_function.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"
#include "xyz_color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
XyzColor XyzColorMatchingFunction::toXyzInEmissiveCase(
    const SpectralDistribution& spectra) const
{
  auto x = x_bar_ * spectra;
  auto y = y_bar_ * spectra;
  auto z = z_bar_ * spectra;
  return XyzColor{x.sum(), y.sum(), z.sum()};
}

inline 
XyzColor XyzColorMatchingFunction::toXyzInEmissiveCase(
      const SpectralDistribution& xSpectra, const SpectralDistribution& ySpectra, const SpectralDistribution& zSpectra) const 
{
  // auto x = x_bar_ * xSpectra;
  // auto y = y_bar_ * ySpectra;
  // auto z = z_bar_ * zSpectra;
  return XyzColor{xSpectra.sum(), ySpectra.sum(), zSpectra.sum()};
}

/*!
  \details
  No detailed.
  */
inline
XyzColor XyzColorMatchingFunction::toXyzInReflectiveCase(
    const SpectralDistribution& spectra) const
{
  const double k = 1.0 / (y_bar_ * standard_illuminant_).sum();
  auto x = x_bar_ * spectra * standard_illuminant_;
  auto y = y_bar_ * spectra * standard_illuminant_;
  auto z = z_bar_ * spectra * standard_illuminant_;
  return XyzColor{k * x.sum(), k * y.sum(), k * z.sum()};
}

inline
XyzColor XyzColorMatchingFunction::toXyzInReflectiveCase(
  const SpectralDistribution& xSpectra, const SpectralDistribution& ySpectra, const SpectralDistribution& zSpectra) const {
  auto x = xSpectra * standard_illuminant_;
  auto y = ySpectra * standard_illuminant_;
  auto z = zSpectra * standard_illuminant_;

  return XyzColor{x.sum(), y.sum(), z.sum()};
}

/*!
  \details
  No detailed.
  */
inline
const SpectralDistribution& XyzColorMatchingFunction::xBar() const
{
  return x_bar_;
}

/*!
  \details
  No detailed.
  */
inline
const SpectralDistribution& XyzColorMatchingFunction::yBar() const
{
  return y_bar_;
}

/*!
  \details
  No detailed.
  */
inline
const SpectralDistribution& XyzColorMatchingFunction::zBar() const
{
  return z_bar_;
}

} // namespace reflect

#endif // _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_INL_HPP_
