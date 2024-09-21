/*!
  \file xyz_color_matching_function.hpp
  \author takemura
  */

#ifndef _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_HPP_
#define _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_HPP_

// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"
#include "xyz_color.hpp"

// Forward declaration
class QString;

namespace reflect {

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class XyzColorMatchingFunction
{
 public:
  //! Create a xyz color matching function
  XyzColorMatchingFunction(const QString& standard_observer, 
                           const QString& standard_illuminant);


  //! In the emissive case, convert spectrums to XYZ using color matching function.
  XyzColor toXyzInEmissiveCase(const SpectralDistribution& spectra) const;

  //! In the reflective or transmissive case, convert spectrums to XYZ
  XyzColor toXyzInReflectiveCase(const SpectralDistribution& spectra) const;

  //! Return the x bar
  const SpectralDistribution& xBar() const;

  //! Return the y bar
  const SpectralDistribution& yBar() const;

  //! Return the z bar
  const SpectralDistribution& zBar() const;

 private:
  //! Initialize
  void initialize(const QString& standard_observer, 
                  const QString& standard_illuminant);

  //! Set standard illuminant
  void setStandardIlluminant(const QString& standard_illuminant);

  //! Set standard obverser
  void setStandardObserver(const QString& standard_observer);


  SpectralDistribution standard_illuminant_;
  SpectralDistribution x_bar_,
                       y_bar_,
                       z_bar_;
};

//! \} Color

} // namespace reflect

#include "xyz_color_matching_function-inl.hpp"

#endif // _REFLECT_XYZ_COLOR_MATCHING_FUNCTION_HPP_
