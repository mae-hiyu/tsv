/*!
  \file sampled_direction-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_DIRECTION_INL_HPP_
#define _REFLECT_SAMPLED_DIRECTION_INL_HPP_

#include "sampled_direction.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
// Zisc
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
SampledDirection::SampledDirection() :
    inverse_pdf_{0.0}
{
}

/*!
  \details
  No detailed.
  */
inline
SampledDirection::SampledDirection(const Vector3& direction, 
                                   const double inverse_pdf) :
    direction_{direction},
    inverse_pdf_{inverse_pdf}
{
}

/*!
  \details
  No detailed.
  */
inline
Vector3& SampledDirection::direction()
{
  return direction_;
}

/*!
  \details
  No detailed.
  */
inline
const Vector3& SampledDirection::direction() const
{
  return direction_;
}

/*!
  \details
  No detailed.
  */
inline
double SampledDirection::inversePdf() const
{
  return inverse_pdf_;
}

/*!
  \details
  No detailed.
  */
inline
double SampledDirection::pdf() const
{
  return 1.0 / inverse_pdf_;
}

/*!
  \details
  No detailed.
  */
inline
void SampledDirection::setDirection(const Vector3& direction)
{
  direction_ = direction;
}

/*!
  \details
  No detailed.
  */
inline
void SampledDirection::setInversePdf(const double inverse_pdf)
{
  inverse_pdf_ = inverse_pdf;
}

/*!
  \details
  No detailed.
  */
inline
void SampledDirection::setPdf(const double pdf)
{
  inverse_pdf_ = 1.0 / pdf;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kCosineWeight> inline
SampledDirection sampleDirectionOnHemisphere(Sampler& sampler)
{
  // Calculate phi and theta using inverse function method

  const double phi = zisc::kPi * sampler.sample(-1.0, 1.0);

  constexpr double exponent = 1.0 / cast<double>(kCosineWeight + 1);
  const double cos_theta = std::pow(1.0 - sampler.sample(0.0, 1.0), exponent);
  const double sin_theta = zisc::sqrt(1.0 - cos_theta * cos_theta);

  const Vector3 direction{sin_theta * zisc::cos(phi), 
                          sin_theta * zisc::sin(phi), 
                          cos_theta};
  REFLECT_CHECK_UNIT_VECTOR(direction);
  REFLECT_CHECK_NON_ZERO_FLOAT(direction);

  constexpr double t = (2.0 * zisc::kPi) / cast<double>(kCosineWeight + 1);
  const double inverse_pdf = t / zisc::power<kCosineWeight>(cos_theta);

  return SampledDirection{direction, inverse_pdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kCosineWeight> inline
SampledDirection sampleDirectionOnHemisphere(const Vector3& normal,
                                             Sampler& sampler)
{
  auto sampled_direction = sampleDirectionOnHemisphere<kCosineWeight>(sampler);
  changeBasis(normal, &(sampled_direction.direction()));
  return sampled_direction;
}

} // namespace reflect

#endif // _REFLECT_SAMPLED_DIRECTION_INL_HPP_
