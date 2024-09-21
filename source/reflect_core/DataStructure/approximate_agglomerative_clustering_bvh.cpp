/*!
  \file approximate_agglomerative_clustering_bvh.cpp
  \author takemura
  */

#include "approximate_agglomerative_clustering_bvh.hpp"
// Standard C++ library
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <future>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "aabb.hpp"
#include "bvh.hpp"
#include "bvh_node.hpp"
#include "agglomerative_cluster.hpp"
#include "keyword.hpp"
#include "Data/object.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ApproximateAgglomerativeClusteringBvh::ApproximateAgglomerativeClusteringBvh(
    const QSettings& settings, const QString& prefix) :
        Bvh(settings, prefix)
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
auto ApproximateAgglomerativeClusteringBvh::buildTree(const std::uint64_t bit,
                                                      MortonCodeIterator begin,
                                                      MortonCodeIterator end) const
    -> ClusterArray 
{
  const std::size_t num_of_primitives = std::distance(begin, end);

  if (num_of_primitives < delta_) {
    ClusterArray cluster_list;
    cluster_list.reserve(num_of_primitives);
    for (auto iterator = begin; iterator != end; ++iterator)
      cluster_list.emplace_back(new AgglomerativeCluster{iterator->first});
    combineClusters(cluster_list, f(delta_));
    return cluster_list;
  }

  auto split_position = findSplitPosition(bit, begin, end);
  if (split_position == begin || split_position == end) {
    if (bit != 1) {
      return buildTree(bit - 1, begin, end);
    }
    else {
      const std::size_t length = std::distance(begin, end);
      split_position = begin + (length >> 1);
    }
  }

  const std::uint64_t next_bit = (bit != 1) ? bit - 1 : bit;
  auto left_cluster_list = buildTree(next_bit, begin, split_position);
  auto right_cluster_list = buildTree(next_bit, split_position, end);

  ClusterArray cluster_list;
  cluster_list.reserve(left_cluster_list.size() + right_cluster_list.size());
  for (auto& cluster : left_cluster_list)
    cluster_list.emplace_back(std::move(cluster));
  for (auto& cluster : right_cluster_list)
    cluster_list.emplace_back(std::move(cluster));

  combineClusters(cluster_list, f(num_of_primitives));
  return cluster_list;
}

/*!
  \details
  No detailed.
  */
template <>
auto ApproximateAgglomerativeClusteringBvh::
    buildTreeInParallel<ApproximateAgglomerativeClusteringBvh::kMaxThreadLevel>(
        RendererSystem& system,
        MortonCodeArray<kMaxThreadLevel - 1>& array) const -> ClusterArray
{
  auto code_array = splitMortonCodeArray<kMaxThreadLevel - 1>(array);
  constexpr std::size_t kNumOfThreads = code_array.size();

  auto& thread_pool = system.threadPool();
  std::array<std::future<ClusterArray>, kNumOfThreads> result_list;

  // Build tree in parallel
  for (std::size_t i = 0; i < kNumOfThreads; ++i) {
    std::function<ClusterArray ()> build_tree{[this, i, &code_array]()
    {
      auto& morton_code_set = code_array[i];
      const std::uint64_t bit = std::get<2>(morton_code_set);
      auto begin = std::get<0>(morton_code_set);
      auto end = std::get<1>(morton_code_set);
      if (begin != end)
        return buildTree(bit, begin, end);
      else
        return ClusterArray{};
    }};
    result_list[i] = thread_pool.enqueue(std::move(build_tree));
  }

  std::array<ClusterArray, kNumOfThreads> cluster_array;
  for (std::size_t i = 0; i < kNumOfThreads; ++i)
    cluster_array[i] = result_list[i].get();

  // Combine clusters in parallel
  for (std::size_t level = kMaxThreadLevel; level > 0; --level) {
    const std::size_t num_of_threads = 1 << (level - 1);
    for (std::size_t i = 0; i < num_of_threads; ++i) {
      std::function<ClusterArray ()> combine_clusters{[this, i, &cluster_array]()
      {
        auto& left = cluster_array[2 * i];
        auto& right = cluster_array[2 * i + 1];
        ClusterArray clusters;
        clusters.reserve(left.size() + right.size());
        std::size_t num_of_primitives = 0;
        for (auto& cluster : left) {
          num_of_primitives += cluster->numOfPrimitives();
          clusters.emplace_back(std::move(cluster));
        }
        for (auto& cluster : right)  {
          num_of_primitives += cluster->numOfPrimitives();
          clusters.emplace_back(std::move(cluster));
        }
        if (num_of_primitives != 0)
          combineClusters(clusters, f(num_of_primitives));
        return clusters;
      }};
      result_list[i] = thread_pool.enqueue(std::move(combine_clusters));
    }
    for (std::size_t i = 0; i < num_of_threads; ++i)
      cluster_array[i] = result_list[i].get();
  }

  return std::move(cluster_array[0]);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kThreadLevel>
auto ApproximateAgglomerativeClusteringBvh::buildTreeInParallel(
    RendererSystem& system,
    MortonCodeArray<kThreadLevel - 1>& array) const -> ClusterArray
{
  auto code_array = splitMortonCodeArray<kThreadLevel - 1>(array);
  return buildTreeInParallel<kThreadLevel + 1>(system, code_array);
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvh::combineClusters(
    ClusterArray& cluster_list,
    const std::size_t n) const
{
  while (cluster_list.size() > n) {
    const auto best_match = findBestMatch(cluster_list);
    // Take left cluster
    ClusterPointer left_cluster;
    for (std::size_t i = 0; i < cluster_list.size(); ++i) {
      if (best_match.first == cluster_list[i].get()) {
        left_cluster = std::move(cluster_list[i]);
        cluster_list.erase(cluster_list.begin() + i);
        break;
      }
    }
    // Take right cluster
    ClusterPointer right_cluster;
    for (std::size_t i = 0; i < cluster_list.size(); ++i) {
      if (best_match.second == cluster_list[i].get()) {
        right_cluster = std::move(cluster_list[i]);
        cluster_list.erase(cluster_list.begin() + i);
        break;
      }
    }
    // Combine clusters
    cluster_list.emplace_back(new AgglomerativeCluster{std::move(left_cluster),
                                                       std::move(right_cluster)});
  }
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvh::constructBvh(
    RendererSystem& system,
    const std::vector<Object>& object_list)
{
  tree_.clear();

  // Allocate memory
  const std::size_t num_of_objects = object_list.size();
  tree_.resize(num_of_objects << 1);
  
  // Create leaf node list
  std::vector<BvhNode> leaf_node_list;
  leaf_node_list.reserve(num_of_objects);
  for (const auto& object : object_list)
    leaf_node_list.emplace_back(&object);

  auto code_list = makeMortonCodeList(leaf_node_list);
  MortonCodeArray<0> code_array{{std::make_tuple(code_list.begin(), 
                                                 code_list.end(), 
                                                 63)}};
//  auto cluster_list = buildTree(63, code_list.begin(), code_list.end());
  auto cluster_list = buildTreeInParallel<1>(system, code_array);
  combineClusters(cluster_list, 1);

  std::size_t number = 0;
  setNode(*cluster_list[0], number);
  tree_[0].setParentIndex(BvhNode::kNonObjectIndex);
  tree_[0].setAsRightNode();
}

/*!
  \details
  No detailed.
  */
std::size_t ApproximateAgglomerativeClusteringBvh::f(const std::size_t n) const
{
  return cast<std::size_t>(c_ * std::pow(cast<double>(n), kAlpha));
}

/*!
  \details
  No detailed.
  */
std::pair<const AgglomerativeCluster*, const AgglomerativeCluster*>
ApproximateAgglomerativeClusteringBvh::findBestMatch(
    const std::vector<ClusterPointer>& cluster_list) const
{
  std::pair<const AgglomerativeCluster*, const AgglomerativeCluster*> best_match;
  double best = std::numeric_limits<double>::max();
  for (std::size_t i = 0; i < cluster_list.size(); ++i) {
    for (std::size_t j = i + 1; j < cluster_list.size(); ++j) {
      const auto& left = cluster_list[i];
      const auto& right = cluster_list[j];
      const double d = distance(*left, *right);
      if (d < best) {
        best = d;
        best_match.first = left.get();
        best_match.second = right.get();
      }
    }
  }
  return best_match;
}

/*!
  \details
  No detailed.
  */
void ApproximateAgglomerativeClusteringBvh::initialize(
    const QSettings& settings, const QString& prefix)
{
  delta_ = value<std::size_t>(settings, prefix + "/" + keyword::delta);
  const double epsilon = value<double>(settings, prefix + "/" + keyword::epsilon);
  c_ = std::pow(cast<double>(delta_), kAlpha + epsilon) * 0.5;
}

/*!
  \details
  No detailed.
  */
std::size_t ApproximateAgglomerativeClusteringBvh::setNode(
    const AgglomerativeCluster& cluster, std::size_t& number)
{
  const std::size_t index = number;
  ++number;

  auto& node = tree_[index];
  if (cluster.isLeaf()) {
    auto object_list = cluster.objectList();
    for (const auto object : object_list)
      node.addObjectWithoutBoundingBox(object);
  }
  else {
    const std::size_t left_child_index = 
        setNode(cluster.leftChildCluster(), number);
    const std::size_t right_child_index = 
        setNode(cluster.rightChildCluster(), number);
    tree_[left_child_index].setParentIndex(index);
    tree_[left_child_index].setAsLeftNode();
    tree_[right_child_index].setParentIndex(index);
    tree_[right_child_index].setAsRightNode();
    node.setLeftChildIndex(left_child_index);
    node.setRightChildIndex(right_child_index);
  }
  node.setBoundingBox(cluster.boundingBox());

  return index;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kLevel>
auto ApproximateAgglomerativeClusteringBvh::splitMortonCodeArray(
    MortonCodeArray<kLevel>& array) const -> MortonCodeArray<kLevel + 1>
{
  MortonCodeArray<kLevel + 1> code_array;

  // Split morton code
  for (std::size_t i = 0; i < array.size(); ++i) {
    // Initialize
    auto& morton_code_set = array[i];
    auto begin = std::get<0>(morton_code_set);
    auto end = std::get<1>(morton_code_set);
    std::uint64_t bit = std::get<2>(morton_code_set);

    const std::size_t num_of_primitives = std::distance(begin, end);
    if (num_of_primitives < delta_) {
      code_array[2 * i    ] = morton_code_set;
      code_array[2 * i + 1] = std::make_tuple(end, end, bit);
    }
    else {
      auto split_position = end;
      while (true) {
        split_position = findSplitPosition(bit, begin, end);
        if (split_position == begin || split_position == end) {
          if (bit != 1) {
            --bit;
            continue;
          }
          else {
            const std::size_t length = std::distance(begin, end);
            split_position = begin + (length >> 1);
          }
        }
        break;
      }
      const std::uint64_t next_bit = (bit != 1) ? bit - 1 : bit;
      code_array[2 * i    ] = std::make_tuple(begin, split_position, next_bit);
      code_array[2 * i + 1] = std::make_tuple(split_position, end, next_bit);
    }
  }

  return code_array;
}

} // namespace reflect
