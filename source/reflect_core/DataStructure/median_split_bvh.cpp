/*!
  \file median_split_bvh.cpp
  \author takemura
  */

#include "median_split_bvh.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <future>
#include <functional>
#include <iterator>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/thread_pool.hpp"
// Reflect
#include "aabb.hpp"
#include "bvh.hpp"
#include "bvh_node.hpp"
#include "reflect_config.hpp"
#include "Data/object.hpp"
#include "LinearAlgebra/point.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
MedianSplitBvh::MedianSplitBvh(const QSettings& settings, const QString& prefix) :
    Bvh(settings, prefix)
{
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvh::constructBvh(RendererSystem& system,
                                  const std::vector<Object>& object_list)
{
  tree_.clear();

  // Allocate memory 
  std::size_t num_of_nodes = 1;
  while (num_of_nodes < object_list.size())
    num_of_nodes = num_of_nodes << 1;
  num_of_nodes = (num_of_nodes << 1) - 1;
  tree_.resize(num_of_nodes);

  // Cereate leaf node list
  std::vector<BvhNode> leaf_node_list;
  leaf_node_list.reserve(object_list.size());
  for (const auto& object : object_list)
    leaf_node_list.emplace_back(&object);

  std::vector<BvhNode*> leaf_distribution;
  leaf_distribution.reserve(leaf_node_list.size());
  for (auto& leaf_node : leaf_node_list)
    leaf_distribution.emplace_back(&leaf_node);

  std::vector<std::future<void>> result_list;
  result_list.resize(tree_.size());

  splitInMedian(system, 1, leaf_distribution.begin(), leaf_distribution.end(), result_list);
          
  for (auto& result : result_list) {
    if (result.valid())
      result.get();
  }
  tree_[0].setParentIndex(BvhNode::kNonObjectIndex);
  tree_[0].setAsRightNode();
}

/*!
  \details
  No detailed.
  */
void MedianSplitBvh::splitInMedian(RendererSystem& system,
                                   const std::size_t number,
                                   NodeIterator begin, 
                                   NodeIterator end,
                                   std::vector<std::future<void>>& result_list)
{
  tree_[number - 1].setParentIndex((number >> 1) - 1);
  if ((number & 1) == 1)
    tree_[number - 1].setAsRightNode();
  else
    tree_[number - 1].setAsLeftNode();

  const auto bounding_box = combineBoundingBoxs(begin, end);
  tree_[number - 1].setBoundingBox(bounding_box);
  const std::size_t axis = bounding_box.longestAxis();

  // Sort by centroid
  auto compare = [axis](const BvhNode* a, const BvhNode* b)
  {
    const auto centroid_a = a->boundingBox().centroid();
    const auto centroid_b = b->boundingBox().centroid();
    return centroid_a[axis] < centroid_b[axis];
  };
  std::sort(begin, end, compare);

  // Split leaf node distribution at median
  auto median = begin;
  const std::size_t size = std::distance(begin, end);
  std::advance(median, size >> 1);

  auto& thread_pool = system.threadPool();
  constexpr std::size_t non_thread_line = 1 << kNonThreadLevel;

  // Operate the left group
  const std::size_t left_size = std::distance(begin, median);
  const std::size_t left_number = number << 1;
  tree_[number - 1].setLeftChildIndex(left_number - 1);
  if (left_size == 1) {
    tree_[left_number - 1] = std::move(*(*begin));
    tree_[left_number - 1].setParentIndex(number - 1);
    tree_[left_number - 1].setAsLeftNode();
  }
  else if (1 < left_size && left_size <= non_thread_line) {
    splitInMedian(system, left_number, begin, median, result_list);
  }
  else if (non_thread_line < left_size) {
    std::function<void ()> split_group{
    [this, left_number, begin, median, &result_list, &system]()
    {
      splitInMedian(system, left_number, begin, median, result_list);
    }};
    result_list[left_number - 1] = thread_pool.enqueue(std::move(split_group));
  }

  // Operate the right group
  const std::size_t right_size = std::distance(median, end);
  const std::size_t right_number = left_number + 1;
  tree_[number - 1].setRightChildIndex(right_number - 1);
  if (right_size == 1) {
    tree_[right_number - 1] = std::move(*(*median));
    tree_[right_number - 1].setParentIndex(number - 1);
    tree_[right_number - 1].setAsRightNode();
  }
  else if (1 < right_size && right_size <= non_thread_line) {
    splitInMedian(system, right_number, median, end, result_list);
  }
  else if (non_thread_line < right_size) {
    std::function<void ()> split_group{
    [this, right_number, median, end, &result_list, &system]()
    {
      splitInMedian(system, right_number, median, end, result_list);
    }};
    result_list[right_number - 1] = thread_pool.enqueue(std::move(split_group));
  }
}

} // namespace reflect
