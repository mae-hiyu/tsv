/*!
 \file bvh_node.hpp
 \author takemura
 */

#ifndef _REFLECT_BVH_NODE_HPP_
#define _REFLECT_BVH_NODE_HPP_

// Standard C++ library
#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>
// Zisc
#include "reflect_config.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "aabb.hpp"
#ifdef REFLECT_OPENCL
#include "OpenCL/DataStructure/cl_bvh_node.hpp"
#endif // REFLECT_OPENCL

namespace reflect {

// Forward declaration
class Object;
class Ray;

using zisc::cast;

//! \addtogroup DataStructure
//! \{

/*!
 \brief BVH node
 \details
 No detailed.
 */
class BvhNode
{
  using IndexType = std::uint32_t;


 public:
  static constexpr std::size_t kNonObjectIndex =
      cast<std::size_t>(std::numeric_limits<IndexType>::max());


  //! Create empty node
  BvhNode();

  //! Create a leaf node
  BvhNode(const Object* object);


  //! Add object
  void addObject(const Object* object);

  //! Add object without updating the BoundingBox
  void addObjectWithoutBoundingBox(const Object* object);

  //! Return the bounding box
  const Aabb& boundingBox() const;

  //! Check whether node is leaf node
  bool isLeafNode() const;

  //! Check if this node is left node
  bool isLeftNode() const;

  //! Check if this node is right node
  bool isRightNode() const;

  //! Return the left child index
  std::size_t leftChildIndex() const;

  //! Return the number of objects
  std::size_t numOfObjects() const;

  //! Return the parent node index
  std::size_t parentIndex() const;

  //! Return the right child node index
  std::size_t rightChildIndex() const;

  //! Return the object list
  const std::array<const Object*, kMaxNodeObjects>& objectList() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Set this node as left node
  void setAsLeftNode();

  //! Set this node as right node
  void setAsRightNode();

  //! Set the bounding box
  void setBoundingBox(const Aabb& bounding_box);

  //! Set left child node index
  void setLeftChildIndex(const std::size_t left_child_index);

  //! Set parent node index
  void setParentIndex(const std::size_t parent_index);

  //! Set right child node index
  void setRightChildIndex(const std::size_t right_child_index);

#ifdef REFLECT_OPENCL
  //! Convert to OpenCL data type
  ClBvhNode toClType(const std::vector<Object>& object_list) const;
#endif // REFLECT_OPENCL

 private:
  Aabb bounding_box_;
  std::array<const Object*, kMaxNodeObjects> object_list_;
  IndexType parent_index_,
            left_child_index_,
            right_child_index_;
  std::uint16_t num_of_objects_;
  bool is_left_node_;
};

using MortonCode = std::pair<BvhNode*, std::uint64_t>;
using MortonCodeIterator = std::vector<MortonCode>::iterator;
using NodeIterator = std::vector<BvhNode*>::iterator;

//! Calculate the morton code of the node
std::uint64_t calculate63bitMortonCode(const double x, 
                                       const double y, 
                                       const double z);

//! Get the bounding box overlapping nodes
Aabb combineBoundingBoxs(std::vector<BvhNode>::const_iterator begin,
                         std::vector<BvhNode>::const_iterator end);

//! Get the bounding box overlapping nodes
Aabb combineBoundingBoxs(NodeIterator begin, NodeIterator end);

//! Find the split position
MortonCodeIterator findSplitPosition(const std::uint64_t bit,
                                     MortonCodeIterator begin,
                                     MortonCodeIterator end);

//! Make a morton code list
std::vector<MortonCode> makeMortonCodeList(std::vector<BvhNode>& leaf_node_list);

//! \} DataStructure

} // namespace reflect

#include "bvh_node-inl.hpp"

#endif // _REFLECT_BVH_NODE_HPP_
