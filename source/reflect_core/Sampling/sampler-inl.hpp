/*!
  \file sampler-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLER_INL_HPP_
#define _REFLECT_SAMPLER_INL_HPP_

#include "sampler.hpp"
// Reflect
#include "reflect_config.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic> inline
Arithmetic Sampler::sample(const Arithmetic min, const Arithmetic max)
{
  return sampler_.distribute(min, max);
}

} // namespace reflect

#endif // _REFLECT_SAMPLER_INL_HPP_
