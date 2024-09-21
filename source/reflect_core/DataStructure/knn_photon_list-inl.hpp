/*!
  \file knn_photon_list-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_KNN_PHOTON_LIST_INL_HPP_
#define _REFLECT_KNN_PHOTON_LIST_INL_HPP_

#include "knn_photon_list.hpp"
// Standard C++ library
#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>
// Reflect
#include "Data/photon_cache.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
KnnPhotonList<kSampleSize>::KnnPhotonList()
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto KnnPhotonList<kSampleSize>::operator[](const std::size_t index) const 
    -> const PhotonPoint&
{
  return photon_list_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void KnnPhotonList<kSampleSize>::clear()
{
  photon_list_.clear();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void KnnPhotonList<kSampleSize>::insert(const double square_distance,
                                        const Cache* photon)    
{
  const auto compare = [](const PhotonPoint& a, const PhotonPoint& b)
  {
    return a.first < b.first;
  };

  if (photon_list_.size() != k_) {
    photon_list_.emplace_back(square_distance, photon);
  }
  else {
    if (square_distance < photon_list_.front().first)
      return;
    std::pop_heap(photon_list_.begin(), photon_list_.end(), compare);
    photon_list_.back() = std::make_pair(square_distance, photon);
  }
  std::push_heap(photon_list_.begin(), photon_list_.end(), compare);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
double KnnPhotonList<kSampleSize>::inverseLongestDistance() const
{
  return zisc::invSqrt(photon_list_.front().first);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t KnnPhotonList<kSampleSize>::k() const
{
  return k_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void KnnPhotonList<kSampleSize>::setK(const std::size_t k)
{
  clear();
  k_ = k;
  photon_list_.reserve(k);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t KnnPhotonList<kSampleSize>::size() const
{
  return photon_list_.size();
}

} // namespace reflect

#endif // _REFLECT_KNN_PHOTON_LIST_INL_HPP_
