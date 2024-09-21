/*!
  \file bvh.cpp
  \author takemura
  */

#include "bvh.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zics
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "approximate_agglomerative_clustering_bvh.hpp"
#include "binary_radix_bvh.hpp"
#include "bvh_node.hpp"
#include "keyword.hpp"
#include "median_split_bvh.hpp"
#include "reflect_config.hpp"
#include "Data/intersection_info.hpp"
#include "Data/object.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
Bvh::Bvh(const QSettings& /* settings */, const QString& /* prefix */)
{
}

/*!
  \details
  No detailed.
  */
IntersectionInfo Bvh::findClosestIntersection(const Ray& ray) const
{
  double distance = std::numeric_limits<double>::max(),
         shortest_distance = distance;
  IntersectionInfo intersection,
                    current_data;
  std::size_t index = 0;
  while (true) {
    const auto& node = tree_[index];
    const auto result = node.boundingBox().isIntersected(ray);
    if (result.first) {
      distance = result.second * result.second;
      if (distance < shortest_distance) {
        // A case of leaf node
        if (node.isLeafNode()) {
          const auto& object_list = node.objectList();
          for (std::size_t i = 0; i < node.numOfObjects(); ++i) {
            const auto object = object_list[i];
            if (object->geometry().isIntersected(ray, &current_data)) {
              distance = (current_data.point() - ray.origin()).squareNorm();
              if (distance < shortest_distance) {
                intersection = current_data;
                intersection.setObject(object);
                shortest_distance = distance;
              }
            }
          }
        }
        // A case of internal node
        else {
          index = node.leftChildIndex();
          continue;
        }
      }
    }

    // Back to the parent node until the current node is left node
    while (tree_[index].isRightNode()) {
      index = tree_[index].parentIndex();
      // After searching, return the closest intersection data
      if (index == BvhNode::kNonObjectIndex)
        return intersection;
    }

    // If the current node is left node, move to the right node
    const auto parent_index = tree_[index].parentIndex();
    index = tree_[parent_index].rightChildIndex();
  }
  zisc::raiseError("BvhError: Ray travers falied.");
  return IntersectionInfo{};
}

/*!
  \details
  No detailed.
  */
void Bvh::construct(RendererSystem& system, const std::vector<Object>& object_list)
{
  if (object_list.size() == 1) {
    tree_.emplace_back(&object_list[0]);
    tree_[0].setParentIndex(BvhNode::kNonObjectIndex);
    tree_[0].setAsRightNode();
  }
  else {
    constructBvh(system, object_list);
  }
}

/*!
  \details
  No detailed.
  */
void Bvh::setBoundingBox(BvhNode& node)
{
  if (!node.isLeafNode()) {
    auto& left_node = tree_[node.leftChildIndex()];
    setBoundingBox(left_node);
    auto& right_node = tree_[node.rightChildIndex()];
    setBoundingBox(right_node);
    node.setBoundingBox(combine(left_node.boundingBox(), right_node.boundingBox()));
  }
}

/*!
  \details
  No detailed.
  */
UniquePointer<Bvh> makeBvh(const QSettings& settings)
{
  Bvh* bvh = nullptr;

  const QString prefix = keyword::bvh_group;
  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::binary_radix_bvh):
    bvh = new BinaryRadixBvh{settings, prefix};
    break;
   case zisc::toHash32(keyword::median_split_bvh):
    bvh = new MedianSplitBvh{settings, prefix};
    break;
   case zisc::toHash32(keyword::approximate_agglomerative_clustering_bvh):
    bvh = new ApproximateAgglomerativeClusteringBvh{settings, prefix};
    break;
   default:
    zisc::raiseError("BvhError: Unsupported type is specified.");
    break;
  }
  return UniquePointer<Bvh>{bvh};
}

} // namespace reflect
