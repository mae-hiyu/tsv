/*!
  \file knn_photon_list.hpp
  \author takemura
  */

#ifndef _REFLECT_KNN_PHOTON_LIST_HPP_
#define _REFLECT_KNN_PHOTON_LIST_HPP_

// Standard C++ library
#include <cstddef>
#include <utility>
#include <vector>
// Reflect
#include "Data/photon_cache.hpp"

namespace reflect {

//! \addtogroup DataStructure
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class KnnPhotonList
{
 public:
  using Cache = PhotonCache<kSampleSize>;
  using PhotonPoint = std::pair<double, const Cache*>;
  using PhotonList = std::vector<PhotonPoint>;


  //! Create knn photon list
  KnnPhotonList();


  //! Return the photon cache and distance by the index
  const PhotonPoint& operator[](const std::size_t index) const;


  //! Clear the contents
  void clear();

  //! Insert a photon point if the distance is included in knn
  void insert(const double square_distance, const Cache* photon);

  //! Return the inverse longest distance of contents
  double inverseLongestDistance() const;

  //! Return the k
  std::size_t k() const;

  //! Set k
  void setK(const std::size_t k);

  //! Return the size of list
  std::size_t size() const;

 private:
  PhotonList photon_list_;
  std::size_t k_;
};

//! \}

} // namespace reflect

#include "knn_photon_list-inl.hpp"

#endif // _REFLECT_KNN_PHOTON_LIST_HPP_
