/*!
  \file bvh_node-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_BVH_NODE_INL_HPP_
#define _REFLECT_BVH_NODE_INL_HPP_

#include "bvh_node.hpp"
// Standard C++ library
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "aabb.hpp"
#include "reflect_config.hpp"
#include "Data/object.hpp"
#include "Data/ray.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
void BvhNode::addObject(const Object* object)
{
  const std::size_t index = numOfObjects();
  ++num_of_objects_;
  if (num_of_objects_ >= 4)
    zisc::raiseError("The number of objects exceeds the limit.");

  object_list_[index] = object;
  if (num_of_objects_ == 1)
    bounding_box_ = object->geometry().boundingBox();
  else
    bounding_box_ = combine(bounding_box_, object->geometry().boundingBox());
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::addObjectWithoutBoundingBox(const Object* object)
{
  const std::size_t index = numOfObjects();
  ++num_of_objects_;
  if (num_of_objects_ >= 4)
    zisc::raiseError("The number of objects exceeds the limit.");

  object_list_[index] = object;
}

/*!
  \details
  No detailed.
  */
inline
const Aabb& BvhNode::boundingBox() const
{
  return bounding_box_;
}

/*!
  \details
  No detailed.
  */
inline
bool BvhNode::isLeafNode() const
{
  return num_of_objects_ != 0;
}

/*!
  \details
  No detailed.
  */
inline
bool BvhNode::isLeftNode() const
{
  return is_left_node_;
}

/*!
  \details
  No detailed.
  */
inline
bool BvhNode::isRightNode() const
{
  return !isLeftNode();
}

/*!
  \details
  No detailed.
  */
inline
std::size_t BvhNode::leftChildIndex() const 
{
  return cast<std::size_t>(left_child_index_);
}

/*!
  \details
  No detailed.
  */
inline
std::size_t BvhNode::numOfObjects() const
{
  return cast<std::size_t>(num_of_objects_);
}

/*!
 \details
 No detailed.
 */
inline
auto BvhNode::objectList() const -> const std::array<const Object*, kMaxNodeObjects>& 
{
  return object_list_;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t BvhNode::parentIndex() const
{
  return cast<std::size_t>(parent_index_);
}

/*!
  \details
  No detailed.
  */
inline
std::size_t BvhNode::rightChildIndex() const
{
  return cast<std::size_t>(right_child_index_);
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setAsLeftNode()
{
  is_left_node_ = true;
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setAsRightNode()
{
  is_left_node_ = false;
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setBoundingBox(const Aabb& bounding_box)
{
  bounding_box_ = bounding_box;
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setLeftChildIndex(const std::size_t left_child_index)
{
  left_child_index_ = cast<IndexType>(left_child_index);
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setParentIndex(const std::size_t parent_index)
{
  parent_index_ = cast<IndexType>(parent_index);
}

/*!
  \details
  No detailed.
  */
inline
void BvhNode::setRightChildIndex(const std::size_t right_child_index)
{
  right_child_index_ = cast<IndexType>(right_child_index);
}

} // namespace reflect

#endif // _REFLECT_BVH_NODE_INL_HPP_
