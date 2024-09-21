/*!
  \file cl_bvh_node.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_BVH_NODE_HPP_
#define _REFLECT_CL_BVH_NODE_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "cl_aabb.hpp"
#include "reflect_config.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
struct ClBvhNode
{
  ClAabb bounding_box_;
  cl_uint object_index_list_[kMaxNodeObjects];
  cl_uint parent_index_,
          left_child_index_,
          right_child_index_;
  cl_ushort num_of_objects_;
  cl_uchar is_left_node_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClBvhNode>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClBvhNode::bounding_box_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::object_index_list_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::parent_index_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::left_child_index_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::right_child_index_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::num_of_objects_);
  size += PRINT_VARIABLE_DATA(ClBvhNode::is_left_node_);
  return size;
}

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_BVH_NODE_HPP_
