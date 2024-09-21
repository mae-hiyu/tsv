/*!
  \file light_source_sampler-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_LIGHT_SOURCE_SAMPLER_INL_HPP_
#define _REFLECT_LIGHT_SOURCE_SAMPLER_INL_HPP_

#include "light_source_sampler.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
#include <iostream>
// Reflect
#include "cumulative_distribution_function.hpp"
#include "sampler.hpp"
#include "Data/light_source_reference.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
const LightSourceReference& LightSourceSampler::sample(Sampler& sampler) const
{
  const double y = sampler.sample(0.0, 1.0);
  const std::size_t index = cdf_->inverseFunction(y);
  
  return *light_source_list_[index];
}

} // namespace reflect

#endif // _REFLECT_LIGHT_SOURCE_SAMPLER_INL_HPP_
