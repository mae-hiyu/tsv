/*!
  \file photon_map_node.hpp
  \author takemura
  */

#ifndef _REFLECT_PHOTON_MAP_NODE_HPP_
#define _REFLECT_PHOTON_MAP_NODE_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class PhotonCache;

//! \addtogroup DataStructure
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class PhotonMapNode
{
 public:
  using Cache = PhotonCache<kSampleSize>;


  //! Create a photon map node
  PhotonMapNode(const Cache* cache);


  //! Return the flag
  std::size_t flag() const;

  //! Return the photon cache
  const Cache* photonCache() const;

  //! Return the point
  const Point3& point() const;

  //! Set the node information
  void setFlag(const std::size_t flag);


  static constexpr std::size_t kXAxisFlag = 0;
  static constexpr std::size_t kYAxisFlag = 1;
  static constexpr std::size_t kZAxisFlag = 2;
  static constexpr std::size_t kLeafNodeFlag = 3;

 private:
  const Point3* point_;
  const Cache* cache_;
  std::size_t flag_;
};

//! \} DataStructure

} // namespace reflect

#include "photon_map_node-inl.hpp"

#endif // _REFLECT_PHOTON_MAP_NODE_HPP_
