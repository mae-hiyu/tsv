/*!
  \file yxy_color.cpp
  \author takemura
  */

#include "yxy_color.hpp"
// Reflect
#include "color.hpp"
#include "xyz_color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
XyzColor YxyColor::toXyz() const
{
  const double coefficient = Y() / y();
  return XyzColor{coefficient * x(), Y(), coefficient * (1.0 - x() - y())};
}

} // namespace reflect
