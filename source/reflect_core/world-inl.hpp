/*!
  \file world-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_WORLD_INL_HPP_
#define _REFLECT_WORLD_INL_HPP_

#include "world.hpp"
// Standard C++ library
#include <vector>
// Reflect
#include "Data/light_source_reference.hpp"
#include "DataStructure/bvh.hpp"
#include "Sampling/light_source_sampler.hpp"

namespace reflect {

/*!
  \details
  No detailed.

  \return BVH
  */
inline
const Bvh& World::bvh() const
{
  return *bvh_;
}

/*!
  \details
  No detailed.
  */
inline
const std::vector<LightSourceReference>& World::lightSourceList() const
{
  return light_source_list_;
}

/*!
  \details
  No detailed.
  */
inline
const LightSourceSampler& World::lightSourceSampler() const
{
  return *light_source_sampler_;
}

/*!
  \details
  No detailed.
  */
inline
const std::vector<Object>& World::objectList() const
{
  return object_list_;
}

} // namespace reflect

#endif // _REFLECT_WORLD_INL_HPP_
