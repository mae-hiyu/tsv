/*!
  \file rgb_color_matching_function.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_COLOR_MATCHING_FUNCTION_HPP_
#define _REFLECT_RGB_COLOR_MATCHING_FUNCTION_HPP_

// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"

namespace reflect {

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class RgbColorMatchingFunction
{
 public:
  //! Create a rgb color matching function
  RgbColorMatchingFunction();


  //! Return the blue bar
  const SpectralDistribution& blueBar() const;

  //! Return the green bar
  const SpectralDistribution& greenBar() const;

  //! Return the red bar
  const SpectralDistribution& redBar() const;

 private:
  //! Initialize
  void initialize();


  SpectralDistribution red_bar_,
                       green_bar_,
                       blue_bar_;
};

//! \} Color

} // namespace reflect

#endif // _REFLECT_RGB_COLOR_MATCHING_FUNCTION_HPP_
