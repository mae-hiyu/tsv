/*!
  \file floating_point.cpp
  \author takemura
  */

#include "floating_point.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
// Qt
#include <QDebug>
// Zisc
#include "zisc/error.hpp"
// Reflect
#include "Color/spectral_distribution.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
bool isBetweenZeroAndOneFloat(const double value)
{
  return 0.0 <= value && value <= 1.0;
}

/*!
  \details
  No detailed.
  */
bool isBetweenZeroAndOneFloat(const SpectralDistribution& distribution)
{
  for (std::size_t index = 0; index < distribution.size(); ++index) {
    if (!isBetweenZeroAndOneFloat(distribution[index]))
        return false;
  }
  return true;
}

/*!
  \details
  No detailed.
  */
bool isInfFloat(const double value)
{
  return std::isinf(value);
}

/*!
  \details
  No detailed.
  */
bool isInfFloat(const SpectralDistribution& distribution)
{
  for (std::size_t index = 0; index < distribution.size(); ++index) {
    const double intensity = distribution[index];
    if (isInfFloat(intensity))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
bool isNanFloat(const double value)
{
  return std::isnan(value);
}

/*!
  \details
  No detailed.
  */
bool isNanFloat(const SpectralDistribution& distribution)
{
  for (std::size_t index = 0; index < distribution.size(); ++index) {
    const double intensity = distribution[index];
    if (isNanFloat(intensity))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
bool isNegativeFloat(const double value)
{
  return value < 0.0;
}

/*!
  \details
  No detailed.
  */
bool isZeroFloat(const double value)
{
  return value == 0.0;
}

/*!
  \details
  No detailed.
  */
bool isZeroFloat(const SpectralDistribution& distribution)
{
  for (std::size_t index = 0; index < distribution.size(); ++index) {
    const double intensity = distribution[index];
    if (isZeroFloat(intensity))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
bool isZeroFloat(const Vector3& vector)
{
  for (std::size_t axis = 0; axis < 3; ++axis) {
    if (isZeroFloat(vector[axis]))
      return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
bool isUnitVector(const Vector3& vector)
{
  constexpr double error = 1.0e-6;
  const double norm = vector.norm();
  return (1.0 - error) < norm && norm < (1.0 + error);
}

/*!
  \details
  No detailed.
  */
void printFloatValue(const double value)
{
  qDebug() << "  Value: " << value;
}

} // namespace reflect
