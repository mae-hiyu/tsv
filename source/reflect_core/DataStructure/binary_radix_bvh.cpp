/*!
  \file binary_radix_bvh.cpp
  \author takemura
  */

#include "binary_radix_bvh.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "aabb.hpp"
#include "bvh.hpp"
#include "bvh_node.hpp"
#include "Data/object.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
BinaryRadixBvh::BinaryRadixBvh(const QSettings& settings, const QString& prefix) :
    Bvh(settings, prefix)
{
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvh::constructBvh(RendererSystem& /* system */,
                                  const std::vector<Object>& object_list)
{
  tree_.clear();

  // Allocate memory
  const std::size_t num_of_objects = object_list.size();
  const std::size_t num_of_nodes = num_of_objects * 2;
  tree_.resize(num_of_nodes);

  // Create leaf node list
  std::vector<BvhNode> leaf_node_list;
  leaf_node_list.reserve(num_of_objects);
  for (const auto& object : object_list)
    leaf_node_list.emplace_back(&object);

  auto morton_code_list = makeMortonCodeList(leaf_node_list);

  splitInMortonCode(63, 0, morton_code_list.begin(), 
                    morton_code_list.begin(), morton_code_list.end());
  tree_[0].setParentIndex(BvhNode::kNonObjectIndex);
  tree_[0].setAsRightNode();

  setBoundingBox(tree_[0]);
}

/*!
  \details
  No detailed.
  */
void BinaryRadixBvh::splitInMortonCode(const std::uint64_t bit,
                                       const std::size_t index,
                                       MortonCodeIterator first,
                                       MortonCodeIterator begin,
                                       MortonCodeIterator end)
{
  // Split leaf node list in the morton code
  auto split_position = findSplitPosition(bit, begin, end);
  if (split_position == begin || split_position == end) {
    if (bit != 1) {
      splitInMortonCode(bit - 1, index, first, begin, end);
      return;
    }
    else {
      const std::size_t length = std::distance(begin, end);
      split_position = begin + (length >> 1);
    }
  }

  const std::uint64_t next_bit = (bit != 1) ? bit - 1 : bit;
  std::size_t right_child_index = std::distance(first, split_position);
  std::size_t left_child_index = right_child_index - 1;
  // Left child node
  const bool left_child_is_leaf = (std::distance(begin, split_position) == 1);
  if (left_child_is_leaf) {
    left_child_index = left_child_index + (tree_.size() >> 1);
    tree_[left_child_index] = std::move(*begin->first);
  }
  else {
    splitInMortonCode(next_bit, left_child_index, first, begin, split_position);
  }
  tree_[index].setLeftChildIndex(left_child_index);
  tree_[left_child_index].setParentIndex(index);
  tree_[left_child_index].setAsLeftNode();

  // Right child node
  const bool right_child_is_leaf = (std::distance(split_position, end) == 1);
  if (right_child_is_leaf) {
    right_child_index = right_child_index + (tree_.size() >> 1);
    tree_[right_child_index] = std::move(*split_position->first);
  }
  else {
    splitInMortonCode(next_bit, right_child_index, first, split_position, end);
  }
  tree_[index].setRightChildIndex(right_child_index);
  tree_[right_child_index].setParentIndex(index);
  tree_[right_child_index].setAsRightNode();
}

} // namespace reflect
