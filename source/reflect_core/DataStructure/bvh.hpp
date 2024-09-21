/*!
  \file bvh.hpp
  \author takemura
  */

#ifndef _REFLECT_BVH_HPP_
#define _REFLECT_BVH_HPP_

// Standard C++ library
#include <vector>
// Reflect
#include "bvh_node.hpp"
#include "reflect_config.hpp"
#include "Data/object.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class IntersectionInfo;
class Ray;
class RendererSystem;

//! \addtogroup DataStructure
//! \{

/*!
  \details
  No detailed.
  */
class Bvh
{
 public:
  //! Create a BVH
  Bvh(const QSettings& settings, const QString& prefix);

  virtual ~Bvh() {}


  //! Find the intersection closest to the ray origin
  IntersectionInfo findClosestIntersection(const Ray& ray) const;

  //! Build BVH
  void construct(RendererSystem& system, const std::vector<Object>& object_list);

 protected:
  //! Build BVH
  virtual void constructBvh(RendererSystem& system,
                            const std::vector<Object>& object_list) = 0;

  //! Set the bounding boxes of the node and child nodes
  void setBoundingBox(BvhNode& node);                                     


  std::vector<BvhNode> tree_;
};

//! Make bvh
UniquePointer<Bvh> makeBvh(const QSettings& settings);

//! \} DataStructure

} // namespace reflect

#endif // _REFLECT_BVH_HPP_
