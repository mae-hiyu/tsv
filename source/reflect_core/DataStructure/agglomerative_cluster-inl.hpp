/*!
  \file agglomerative_cluster-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_AGGLOMERATIVE_CLUSTER_INL_HPP_
#define _REFLECT_AGGLOMERATIVE_CLUSTER_INL_HPP_

#include "agglomerative_cluster.hpp"
// Standard C++ library
#include <cstddef>
#include <memory>
#include <utility>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "aabb.hpp"
#include "bvh_node.hpp"
#include "reflect_config.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
AgglomerativeCluster::AgglomerativeCluster(BvhNode* leaf_node) :
    is_flattened_{false},
    num_of_primitives_{1},
    leaf_node_{leaf_node},
    bounding_box_{leaf_node->boundingBox()}
{
  setCost();
}

/*!
  \details
  No detailed.
  */
inline
AgglomerativeCluster::AgglomerativeCluster(
    std::unique_ptr<AgglomerativeCluster>&& left_child_cluster,
    std::unique_ptr<AgglomerativeCluster>&& right_child_cluster) :
        is_flattened_{false},
        leaf_node_{nullptr},
        left_child_cluster_{std::move(left_child_cluster)},
        right_child_cluster_{std::move(right_child_cluster)}
{
  num_of_primitives_ = left_child_cluster_->numOfPrimitives() +
                       right_child_cluster_->numOfPrimitives();
  bounding_box_ = combine(left_child_cluster_->boundingBox(),
                          right_child_cluster_->boundingBox());
  setCost();
  evaluateFlattingCost();
}

/*!
  \details
  No detailed.
  */
inline
const Aabb& AgglomerativeCluster::boundingBox() const
{
  return bounding_box_;
}

/*!
  \details
  No detailed.
  */
inline
double AgglomerativeCluster::cost() const
{
  return cost_;
}

/*!
  \details
  No detailed.
  */
inline
bool AgglomerativeCluster::isLeaf() const
{
  return isSingleton() || is_flattened_;
}

/*!
  \details
  No detailed.
  */
inline
bool AgglomerativeCluster::isSingleton() const
{
  return leaf_node_ != nullptr;
}

/*!
  \details
  No detailed.
  */
inline
const AgglomerativeCluster& AgglomerativeCluster::leftChildCluster() const
{
  return *left_child_cluster_;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t AgglomerativeCluster::numOfPrimitives() const
{
  return num_of_primitives_;
}

/*!
  \details
  No detailed.
  */
inline
std::vector<const Object*> AgglomerativeCluster::objectList() const
{
  std::vector<const Object*> object_list;
  if (isSingleton()) {
    const std::size_t num_of_objects = leaf_node_->numOfObjects();
    object_list.resize(num_of_objects);
    const auto& list = leaf_node_->objectList();
    for (std::size_t i = 0; i < num_of_objects; ++i)
      object_list[i] = list[i];
  }
  else {
    auto left_object_list = leftChildCluster().objectList();
    auto right_object_list = rightChildCluster().objectList();
    object_list.reserve(left_object_list.size() + right_object_list.size());
    for (const auto object : left_object_list)
      object_list.emplace_back(object);
    for (const auto object : right_object_list)
      object_list.emplace_back(object);
  }
  return object_list;
}

/*!
  \details
  No detailed.
  */
inline
const AgglomerativeCluster& AgglomerativeCluster::rightChildCluster() const
{
  return *right_child_cluster_;
}

/*!
  \details
  No detailed.
  */
inline
void AgglomerativeCluster::evaluateFlattingCost()
{
  if (numOfPrimitives() >= kMaxNodeObjects)
    return;

  const double flatting_cost = kRayTriangleCost * cast<double>(numOfPrimitives());
  if (flatting_cost < cost()) {
    is_flattened_ = true;
    cost_ = flatting_cost;
  }
}

/*!
  \details
  No detailed.
  */
inline
void AgglomerativeCluster::setCost()
{
  if (isSingleton()) {
    cost_ = kRayTriangleCost;
  }
  else {
    const double inverse_surface_area = 1.0 / boundingBox().surfaceArea();
    const double left_surface_area = 
        left_child_cluster_->boundingBox().surfaceArea();
    const double right_surface_area = 
        right_child_cluster_->boundingBox().surfaceArea();

    cost_ = (left_surface_area * inverse_surface_area) * 
            (kRayBoxCost + left_child_cluster_->cost()) +
            (right_surface_area * inverse_surface_area) *
            (kRayBoxCost + right_child_cluster_->cost());
  }
}

/*!
  \details
  No detailed.
  */
inline
double distance(const AgglomerativeCluster& a, const AgglomerativeCluster& b)
{
  return combine(a.boundingBox(), b.boundingBox()).surfaceArea();
}

} // namespace reflect

#endif // _REFLECT_AGGLOMERATIVE_CLUSTER_INL_HPP_
