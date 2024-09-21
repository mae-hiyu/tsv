/*!
  \file photon_map_node-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_PHOTON_MAP_NODE_INL_HPP_
#define _REFLECT_PHOTON_MAP_NODE_INL_HPP_

#include "photon_map_node.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "Data/photon_cache.hpp"
#include "LinearAlgebra/point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
PhotonMapNode<kSampleSize>::PhotonMapNode(const Cache* cache) :
    point_{&(cache->point())},
    cache_{cache},
    flag_{0}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t PhotonMapNode<kSampleSize>::flag() const
{
  return flag_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto PhotonMapNode<kSampleSize>::photonCache() const -> const Cache*
{
  return cache_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
const Point3& PhotonMapNode<kSampleSize>::point() const
{
  return *point_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void PhotonMapNode<kSampleSize>::setFlag(const std::size_t flag)
{
  flag_ = flag;
}

} // namespace reflect

#endif // _REFLECT_PHOTON_MAP_NODE_INL_HPP_
