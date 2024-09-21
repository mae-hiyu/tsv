/*!
  \file light_source_sampler.hpp
  \author takemura
  */

#ifndef _REFLECT_LIGHT_SOURCE_SAMPLER_HPP_
#define _REFLECT_LIGHT_SOURCE_SAMPLER_HPP_

// Standard C++ library
#include <vector>
// Reflect
#include "cumulative_distribution_function.hpp"
#include "Data/light_source_reference.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

// Forward declaration
class Sampler;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class LightSourceSampler
{
 public:
  //! Create a light source sampler
  LightSourceSampler(const std::vector<LightSourceReference>& light_source_list);


  //! Sample a light source
  const LightSourceReference& sample(Sampler& sampler) const;

 private:
  //! Initialize
  void initialize(const std::vector<LightSourceReference>& light_source_list);


  std::vector<const LightSourceReference*> light_source_list_;
  UniquePointer<CumulativeDistributionFunction> cdf_;
};

//! \} Sampling

} // namespace reflect

#include "light_source_sampler-inl.hpp"

#endif // _REFLECT_LIGHT_SOURCE_SAMPLER_HPP_
