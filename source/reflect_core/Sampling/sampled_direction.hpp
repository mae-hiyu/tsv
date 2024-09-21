/*!
  \file sampled_direction.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_DIRECTION_HPP_
#define _REFLECT_SAMPLED_DIRECTION_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "LinearAlgebra/vector.hpp"

namespace reflect {

// Forward declaration
class Sampler;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class SampledDirection
{
 public:
  //! Create sample
  SampledDirection();

  //! Create sample
  SampledDirection(const Vector3& direction, const double inverse_pdf);


  //! Return the sampled direction
  Vector3& direction();

  //! Return the sampled direction
  const Vector3& direction() const;

  //! Return the inverse pdf
  double inversePdf() const;

  //! Return the pdf (probability density function) of the sampled direction
  double pdf() const;

  //! Set direction
  void setDirection(const Vector3& direction);

  //! Set inverse pdf
  void setInversePdf(const double inverse_pdf);

  //! Set pdf of the sampled direction
  void setPdf(const double pdf);

 private:
  Vector3 direction_;
  double inverse_pdf_;
};

//! Sample direction on hemisphere following cos theta pdf
template <std::size_t kN>
SampledDirection sampleDirectionOnHemisphere(Sampler& sampler);

//! Sample direction on hemisphere following cos theta pdf
template <std::size_t kN>
SampledDirection sampleDirectionOnHemisphere(const Vector3& normal,
                                             Sampler& sampler);

//! \} Sampling

} // namespace reflect

#include "sampled_direction-inl.hpp"

#endif // _REFLECT_SAMPLED_DIRECTION_HPP_
