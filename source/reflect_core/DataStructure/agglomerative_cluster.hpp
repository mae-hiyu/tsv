/*!
  \file agglomerative_cluster.hpp
  \author takemura
  */

#ifndef _REFLECT_AGGLOMERATIVE_CLUSTER_HPP_
#define _REFLECT_AGGLOMERATIVE_CLUSTER_HPP_

// Standard C++ library
#include <cstddef>
#include <memory>
#include <vector>
// Reflect
#include "aabb.hpp"

namespace reflect {

// Forward declaration
class BvhNode;
class Object;

/*!
  \details
  No detailed.
  */
class AgglomerativeCluster
{
 public:
  //! Create a singleton cluster
  AgglomerativeCluster(BvhNode* leaf_node);

  //! Create a cluster
  AgglomerativeCluster(std::unique_ptr<AgglomerativeCluster>&& left_child_cluster,
                       std::unique_ptr<AgglomerativeCluster>&& right_child_cluster);


  //! Return the bounding box
  const Aabb& boundingBox() const;

  //! Return the cluster cost
  double cost() const;

  //! Check if the cluster is leaf
  bool isLeaf() const;

  //! Check is the cluster is singleton
  bool isSingleton() const;

  //! Return the left child cluster
  const AgglomerativeCluster& leftChildCluster() const;

  //! Return the number of primitives
  std::size_t numOfPrimitives() const;

  //! Return the object list
  std::vector<const Object*> objectList() const;

  //! Return the right child cluster
  const AgglomerativeCluster& rightChildCluster() const;

 private:
  // Prohibit copy
  AgglomerativeCluster(const AgglomerativeCluster&) = delete;
  AgglomerativeCluster& operator=(const AgglomerativeCluster&) = delete;


  //! Evaluate the flatting cost
  void evaluateFlattingCost();

  //! Calculate and set the cluster cost
  void setCost();


  static constexpr double kRayBoxCost = 1.2;
  static constexpr double kRayTriangleCost = 1.0;


  bool is_flattened_;
  std::size_t num_of_primitives_;
  double cost_;
  BvhNode* leaf_node_;
  Aabb bounding_box_;
  std::unique_ptr<AgglomerativeCluster> left_child_cluster_,
                                        right_child_cluster_;
};

using ClusterIterator = std::vector<AgglomerativeCluster>::iterator;

//! Evaluate distance functionn
double distance(const AgglomerativeCluster& a, const AgglomerativeCluster& b);

} // namespace reflect

#include "agglomerative_cluster-inl.hpp"

#endif // _REFLECT_AGGLOMERATIVE_CLUSTER_HPP_
