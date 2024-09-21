/*!
  \file median_split_bvh.hpp
  \author takemura
  */

#ifndef _REFLECT_MEDIAN_SPLIT_BVH_HPP_
#define _REFLECT_MEDIAN_SPLIT_BVH_HPP_

// Standard C++ library
#include <cstddef>
#include <future>
#include <vector>
// Reflect
#include "bvh.hpp"
#include "bvh_node.hpp"
#include "Data/object.hpp"

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
  please see "PBRT 2nd chapter 4"
  http://pbrt.org/chapters/pbrt-2ed-chap4.pdf
  */
class MedianSplitBvh : public Bvh
{
 public:
  //! Create a median split BVH
  MedianSplitBvh(const QSettings& settings, const QString& prefix);

 private:
  //! Build median split BVH
  void constructBvh(RendererSystem& system,
                    const std::vector<Object>& object_list) override;

  //! Split at median
  void splitInMedian(RendererSystem& system,
                     const std::size_t number, 
                     NodeIterator begin, 
                     NodeIterator end,
                     std::vector<std::future<void>>& result_list);


  static constexpr std::size_t kNonThreadLevel = 8;
};

//! \} DataStructure

} // namespace reflect

#endif // _REFLECT_MEDIAN_SPLIT_BVH_HPP_
