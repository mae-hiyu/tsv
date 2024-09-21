/*!
  \file spectral_distribution-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRAL_DISTRIBUTION_INL_HPP_
#define _REFLECT_SPECTRAL_DISTRIBUTION_INL_HPP_

#include "spectral_distribution.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution::SpectralDistribution()
{
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution::SpectralDistribution(
    const zisc::ArithmeticArray<double, kDistributionSize>& distribution)
        : distribution_{distribution}
{
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator+(
    const SpectralDistribution& other) const
{
  return SpectralDistribution{distribution_ + other.distribution_};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator-(
    const SpectralDistribution& other) const
{
  return SpectralDistribution{distribution_ - other.distribution_};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator*(const double scalar) const
{
  return SpectralDistribution{distribution_ * scalar};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator*(
    const SpectralDistribution& other) const
{
  return SpectralDistribution{distribution_ * other.distribution_};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator/(const double scalar) const
{
  const double inverse = 1.0 / scalar;
  return SpectralDistribution{distribution_ * inverse};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::operator/(
    const SpectralDistribution& other) const
{
  return SpectralDistribution{distribution_ / other.distribution_};
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator+=(
    const SpectralDistribution& other)
{
  distribution_ += other.distribution_;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator-=(
    const SpectralDistribution& other)
{
  distribution_ -= other.distribution_;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator*=(const double scalar)
{
  distribution_ *= scalar;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator*=(
    const SpectralDistribution& other)
{
  distribution_ *= other.distribution_;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator/=(const double scalar)
{
  distribution_ /= scalar;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution& SpectralDistribution::operator/=(
    const SpectralDistribution& other)
{
  distribution_ /= other.distribution_;
  return *this;
}

/*!
  \details
  No detailed.
  */
inline
double& SpectralDistribution::operator[](const std::size_t index)
{
  return distribution_[index];
}

/*!
  \details
  No detailed.
  */
inline
const double& SpectralDistribution::operator[](const std::size_t index) const
{
  return distribution_[index];
}

/*!
  \details
  No detailed.
  */
inline
void SpectralDistribution::fill(const double value)
{
  distribution_.fill(value);
}

/*!
  \details
  No detailed.
  */
inline
double SpectralDistribution::get(const std::size_t index) const
{
  return distribution_[index];
}

/*!
  \details
  No detailed.
  */
inline
double SpectralDistribution::getByWavelength(const std::size_t wavelength) const
{
  return get(getIndex(wavelength));
}

/*!
  \details
  No detailed.
  */
inline
bool SpectralDistribution::isZero() const
{
  return distribution_.isZero();
}

/*!
  \details
  No detailed.
  */
inline
double SpectralDistribution::max() const
{
  return distribution_.max();
}

/*!
  \details
  No detailed.
  */
inline
double SpectralDistribution::min() const
{
  return distribution_.min();
}

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution SpectralDistribution::normalized() const
{
  const double k = 1.0 / sum();
  return *this * k;
}

/*!
  \details
  No detailed.
  */
inline
auto SpectralDistribution::distribution() const 
    -> const zisc::ArithmeticArray<double, kDistributionSize>&
{
  return distribution_;
}

/*!
  \details
  No detailed.
  */
inline
void SpectralDistribution::set(const std::size_t index, const double intensity)
{
  distribution_[index] = intensity;
}

/*!
  \details
  No detailed.
  */
inline
void SpectralDistribution::setByWavelength(const std::size_t wavelength,
                                           const double intensity)
{
  return set(getIndex(wavelength), intensity);
}

/*!
  \details
  No detailed.
  */
inline
double SpectralDistribution::sum() const
{
  return distribution_.sum();
}

} // namespace reflect

#endif // _REFLECT_SPECTRAL_DISTRIBUTION_INL_HPP_
