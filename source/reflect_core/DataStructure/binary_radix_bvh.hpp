/*!
  \file binary_radix_bvh.hpp
  \author takemura
  */

#ifndef _REFLECT_BINARY_RADIX_BVH_HPP_
#define _REFLECT_BINARY_RADIX_BVH_HPP_

// Standard C++ library
#include <cstdint>
#include <vector>
#include <utility>
// Reflect
#include "bvh.hpp"

// Forward declaration
class QSettings;
class QString;
class RendererSystem;

namespace reflect {

//! \addtogroup DataStructure
//! \{

/*!
  \details
  For the details of this algorithm,
  please see the paper entitled 
  "Maximizing Parallelism in the Construction of BVHs, Octrees, and k-d Trees"
  https://research.nvidia.com/sites/default/files/publications/karras2012hpg_paper.pdf
  */
class BinaryRadixBvh : public Bvh
{
 public:
  //! Create a binary radix BVH
  BinaryRadixBvh(const QSettings& settings, const QString& prefix);

 private:
  //! Build binary radix bvh
  void constructBvh(RendererSystem& system,
                    const std::vector<Object>& object_list) override;

  //! Split leaf node list in the morton code
  void splitInMortonCode(const std::uint64_t bit,
                         const std::size_t index,
                         MortonCodeIterator first,
                         MortonCodeIterator begin,
                         MortonCodeIterator end);
};

//! \} DataStructure

} // namespace reflect

#endif // _REFLECT_BINARY_RADIX_BVH_HPP_
