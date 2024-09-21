/*!
  \file sampler.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLER_HPP_
#define _REFLECT_SAMPLER_HPP_

// Standard C++ library
#include <cstdint>
// Reflect
#include "reflect_config.hpp"

namespace reflect {

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class Sampler
{
 public:
  //! Create a sampler
  Sampler();


  //! Sample random number x uniformly satisfying min <= x < max
  template <typename Arithmetic>
  Arithmetic sample(const Arithmetic min, const Arithmetic max);

  //! Set seed
  void setSeed(const std::uint32_t seed);

 private:
  ReflectSamplerType sampler_;
};

//! \} Sampling

} // namespace reflect

#include "sampler-inl.hpp"

#endif // _REFLECT_SAMPLER_HPP_
