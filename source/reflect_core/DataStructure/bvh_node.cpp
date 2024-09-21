/*!
 \file bvh_node.cpp
 \author takemura
 */

#include "bvh_node.hpp"
// Standard C++ library
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <vector>
#include <utility>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "aabb.hpp"
#include "Data/object.hpp"
#include "Geometry/geometry.hpp"
#include "LinearAlgebra/point.hpp"
#include "Utility/size.hpp"
#ifdef REFLECT_OPENCL
#include "OpenCL/cl.hpp"
#include "OpenCL/DataStructure/cl_bvh_node.hpp"
#endif // REFLECT_OPENCL

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
BvhNode::BvhNode() :
    parent_index_{cast<IndexType>(kNonObjectIndex)},
    left_child_index_{cast<IndexType>(kNonObjectIndex)},
    right_child_index_{cast<IndexType>(kNonObjectIndex)},
    num_of_objects_{0},
    is_left_node_{false}
{
}

/*!
  \details
  No detailed.
  */
BvhNode::BvhNode(const Object* object) :
    bounding_box_{object->geometry().boundingBox()},
    object_list_{{object}},
    parent_index_{cast<IndexType>(kNonObjectIndex)},
    left_child_index_{cast<IndexType>(kNonObjectIndex)},
    right_child_index_{cast<IndexType>(kNonObjectIndex)},
    num_of_objects_{1},
    is_left_node_{false}
{
}

/*!
  \details
  No detailed.
  */
std::size_t BvhNode::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(bounding_box_);
  size += PRINT_VARIABLE_DATA(object_list_);
  size += PRINT_VARIABLE_DATA(parent_index_);
  size += PRINT_VARIABLE_DATA(left_child_index_);
  size += PRINT_VARIABLE_DATA(right_child_index_);
  size += PRINT_VARIABLE_DATA(num_of_objects_);
  size += PRINT_VARIABLE_DATA(is_left_node_);
  return size;
}

#ifdef REFLECT_OPENCL

/*!
  \details
  No detailed.
  */
ClBvhNode BvhNode::toClType(const std::vector<Object>& object_list) const
{
  ClBvhNode cl_node;
  // Bounding box
  cl_node.bounding_box_ = boundingBox().toClType();
  // Objects
  cl_node.num_of_objects_ = cast<cl_ushort>(numOfObjects());
  const auto& list = objectList();
  const auto compare = [](const Object& a, const Object* b)
  {
    return &a < b;
  };
  for (std::size_t i = 0; i < numOfObjects(); ++i) {
    auto position = std::lower_bound(object_list.begin(),   
                                     object_list.end(),
                                     list[i], 
                                     compare);
    const std::size_t index = std::distance(object_list.begin(), position);
    cl_node.object_index_list_[i] = cast<cl_uint>(index);
  }
  // Index
  cl_node.parent_index_ = cast<cl_uint>(parentIndex());
  cl_node.left_child_index_ = cast<cl_uint>(leftChildIndex());
  cl_node.right_child_index_ = cast<cl_uint>(rightChildIndex());
  cl_node.is_left_node_ = cast<cl_uchar>(isLeftNode());

  return cl_node;
}

#endif // REFLECT_OPENCL

/*!
  \details
  For the details of this algorithm,
  please see the web page entitled 
  "Morton encoding/decoding through bit interleaving: Implementations"
  http://www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
  */
std::uint64_t calculate63bitMortonCode(const double x,
                                       const double y,
                                       const double z)
{
  const auto expand_bit = [](const double value)
  {
    constexpr double max = cast<double>(cast<std::uint64_t>(1) << 21);
    std::uint64_t v = cast<std::uint64_t>(std::min(std::max(value * max, 0.0), max));
    v = (v | v << 32) & 0x1f00000000ffff;
    v = (v | v << 16) & 0x1f0000ff0000ff;
    v = (v | v <<  8) & 0x100f00f00f00f00f;
    v = (v | v <<  4) & 0x10c30c30c30c30c3;
    v = (v | v <<  2) & 0x1249249249249249;
    return v;
  };
  return (expand_bit(x) << 2) | (expand_bit(y) << 1) | expand_bit(z);
}

/*!
  \details
  No detailed.
  */
Aabb combineBoundingBoxs(std::vector<BvhNode>::const_iterator begin, 
                         std::vector<BvhNode>::const_iterator end)
{
  auto iterator = begin;
  auto min_point = iterator->boundingBox().minPoint().data();
  auto max_point = iterator->boundingBox().maxPoint().data();
  ++iterator;
  while (iterator != end) {
    min_point = zisc::minElements(min_point, 
                                  iterator->boundingBox().minPoint().data());
    max_point = zisc::maxElements(max_point, 
                                  iterator->boundingBox().maxPoint().data());
    ++iterator;
  }
  return Aabb{Point3{min_point}, Point3{max_point}};
}

/*!
  \details
  No detailed.
  */
Aabb combineBoundingBoxs(NodeIterator begin, NodeIterator end)
{
  auto iterator = begin;
  auto min_point = (*iterator)->boundingBox().minPoint().data();
  auto max_point = (*iterator)->boundingBox().maxPoint().data();
  ++iterator;
  while (iterator != end) {
    min_point = zisc::minElements(min_point, 
                                  (*iterator)->boundingBox().minPoint().data());
    max_point = zisc::maxElements(max_point, 
                                  (*iterator)->boundingBox().maxPoint().data());
    ++iterator;
  }
  return Aabb{Point3{min_point}, Point3{max_point}};
}

/*!
  \details
  No detailed.
  */
MortonCodeIterator findSplitPosition(const std::uint64_t bit,
                                     MortonCodeIterator begin,
                                     MortonCodeIterator end)
{
  const std::uint64_t significant_bit = (cast<std::uint64_t>(1) << (bit - 1));
  const auto is_less = [significant_bit](const MortonCode& a, const std::uint64_t& b)
  {
    return (a.second & significant_bit) < b;
  };
  const std::uint64_t threshold = significant_bit - 1;
  return std::lower_bound(begin, end, threshold, is_less);
}

/*!
  \details
  No detailed.
  */
std::vector<MortonCode> makeMortonCodeList(std::vector<BvhNode>& leaf_node_list)
{
  const std::size_t num_of_objects = leaf_node_list.size();

  const auto scene_box = combineBoundingBoxs(leaf_node_list.cbegin(),
                                             leaf_node_list.cend());
  const auto& min_point = scene_box.minPoint();
  const auto range = scene_box.maxPoint() - min_point;
  const double inverse_x = 1.0 / range[0];
  const double inverse_y = 1.0 / range[1];
  const double inverse_z = 1.0 / range[2];

  // Sort by the morton code
  std::vector<MortonCode> morton_code_list;
  morton_code_list.reserve(num_of_objects);
  for (auto& node : leaf_node_list) {
    const auto position = node.boundingBox().centroid() - min_point;
    const auto morton_code = calculate63bitMortonCode(position[0] * inverse_x,
                                                      position[1] * inverse_y,
                                                      position[2] * inverse_z);
    morton_code_list.emplace_back(&node, morton_code);
  }
  const auto is_less = [](const MortonCode& a, const MortonCode& b)
  {
    return a.second < b.second;
  };
  std::sort(morton_code_list.begin(), morton_code_list.end(), is_less);

  return std::move(morton_code_list);
}

} // namespace reflect
