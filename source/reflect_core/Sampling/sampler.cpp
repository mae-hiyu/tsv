/*!
  \file sampler.cpp
  \author takemura
  */

#include "sampler.hpp"
// Standard C++ library
#include <cstdint>
// Reflect
#include "reflect_config.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
Sampler::Sampler()
{
}

/*!
  \details
  No detailed.
  */
void Sampler::setSeed(const std::uint32_t seed)
{
  sampler_.setSeed(seed);
}

} // namespace reflect
