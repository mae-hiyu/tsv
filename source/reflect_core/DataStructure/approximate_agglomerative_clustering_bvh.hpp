/*!
  \file approximate_agglomerative_clustering_bvh.hpp
  \author takemura
  */

#ifndef _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_HPP_
#define _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_HPP_

// Standard C++ library
#include <array>
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>
#include <utility>
// Reflect
#include "agglomerative_cluster.hpp"
#include "bvh.hpp"
#include "bvh_node.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class RendererSystem;

//! \addtogroup DataStructure
//! \{

/*!
  \details
  For the details of this algorithm,
  please see the paper entitled
  "Efficient BVH Construction via Approximate Agglomerative Clustering"
  http://graphics.cs.cmu.edu/projects/aac/aac_build.pdf
  */
class ApproximateAgglomerativeClusteringBvh : public Bvh
{
 public:
  //! Create a approximate agglomerative clustering BVH
  ApproximateAgglomerativeClusteringBvh(const QSettings& settings, 
                                        const QString& prefix);


  static constexpr std::size_t kMaxThreadLevel = 4;

 private:
  using ClusterPointer = std::unique_ptr<AgglomerativeCluster>;
  using ClusterArray = std::vector<ClusterPointer>;
  using MortonCodeSet = 
      std::tuple<MortonCodeIterator, MortonCodeIterator, std::uint64_t>;
  template <std::size_t kThreadLevel>
  using MortonCodeArray = std::array<MortonCodeSet, (1 << kThreadLevel)>;


  //! Build the tree
  std::vector<ClusterPointer> buildTree(const std::uint64_t bit,
                                        MortonCodeIterator begin,
                                        MortonCodeIterator end) const;

  //! Build the tree in parallel
  template <std::size_t kThreadLevel>
  ClusterArray buildTreeInParallel(RendererSystem& system,
                                   MortonCodeArray<kThreadLevel - 1>& array) const;

  //! Combine clusters
  void combineClusters(std::vector<ClusterPointer>& cluster_list,
                       const std::size_t n) const;

  //! Build AAC BVH
  void constructBvh(RendererSystem& system,
                    const std::vector<Object>& object_list) override;

  //! Evaluate the reduction function
  std::size_t f(const std::size_t n) const;

  //! Find best match
  std::pair<const AgglomerativeCluster*, const AgglomerativeCluster*> 
      findBestMatch(const std::vector<ClusterPointer>& cluster_list) const;

  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);

  //! Set node
  std::size_t setNode(const AgglomerativeCluster& cluster, std::size_t& number);

  //! Split morton code array
  template <std::size_t kLevel>
  MortonCodeArray<kLevel + 1> splitMortonCodeArray(MortonCodeArray<kLevel>& array) const;


  static constexpr double kAlpha = 0.5;
  static_assert((0.0 <= kAlpha) && (kAlpha <= 1.0), 
                "## Alpha must be 0.0 <= a <= 1.0 .");


  std::size_t delta_;
  double c_;
};

//! \} DataStructure

} // namespace reflect

#endif // _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_HPP_
