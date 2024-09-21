/*!
  \file light_source_sampler.cpp
  \author takemura
  */

#include "light_source_sampler.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "cumulative_distribution_function.hpp"
#include "Data/light_source_reference.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
LightSourceSampler::LightSourceSampler(
    const std::vector<LightSourceReference>& light_source_list)
{
  initialize(light_source_list);
}

/*!
  \details
  No detailed.
  */
void LightSourceSampler::initialize(
    const std::vector<LightSourceReference>& light_source_list)
{
  std::vector<double> pdf;

  light_source_list_.reserve(light_source_list.size());
  pdf.reserve(light_source_list.size());

  for (const auto& light_source : light_source_list) {
    light_source_list_.emplace_back(&light_source);
    pdf.emplace_back(light_source.weight());
  }

  cdf_ = new CumulativeDistributionFunction{pdf};
}

} // namespace reflect
