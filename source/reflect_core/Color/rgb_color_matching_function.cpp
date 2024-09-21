/*!
  \file rgb_color_matching_function.cpp
  \author takemura
  */

#include "rgb_color_matching_function.hpp"
// Qt
#include <QString>
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RgbColorMatchingFunction::RgbColorMatchingFunction()
{
  initialize();
}

/*!
  \details
  No detailed.
  */
const SpectralDistribution& RgbColorMatchingFunction::blueBar() const
{
  return blue_bar_;
}

/*!
  \details
  No detailed.
  */
const SpectralDistribution& RgbColorMatchingFunction::greenBar() const
{
  return green_bar_;
}

/*!
  \details
  No detailed.
  */
const SpectralDistribution& RgbColorMatchingFunction::redBar() const
{
  return red_bar_;
}

/*!
  \details
  No detailed.
  */
void RgbColorMatchingFunction::initialize()
{
  red_bar_ = makeSpectra(":/property/cie_1931_red.csv");
  green_bar_ = makeSpectra(":/property/cie_1931_green.csv");
  blue_bar_ = makeSpectra(":/property/cie_1931_blue.csv");

//  constexpr double k = 3.782;
//  red_bar_ = red_bar_.normalized() * k;
//  green_bar_ = green_bar_.normalized() * k;
//  blue_bar_ = blue_bar_.normalized() * k;
}

} // namespace reflect
