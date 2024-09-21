/*!
  \file photon_map.hpp
  \author takemura
  */

#ifndef _REFLECT_PHOTON_MAP_HPP_
#define _REFLECT_PHOTON_MAP_HPP_

// Standard C++ library
#include <cstddef>
#include <future>
#include <list>
#include <vector>
#include <utility>
// Reflect
#include "keyword.hpp"
#include "photon_map_node.hpp"
#include "Data/photon_cache.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class KnnPhotonList;
class RendererSystem;
template <std::size_t> class SampledSpectra;

//! \addtogroup DataStructure
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class PhotonMap
{
 public:
  using Cache = PhotonCache<kSampleSize>;
  using MapNode = PhotonMapNode<kSampleSize>;
  using PhotonList = KnnPhotonList<kSampleSize>;
  using Spectra = SampledSpectra<kSampleSize>;


  //! Create a photon map
  PhotonMap(RendererSystem& system);


  //! Clear the contents
  void clear();

  //! Construct the photon map
  void construct(RendererSystem& system);

  //! Reserve storage
  void reserve(RendererSystem& system, const std::size_t size);

  //! Search photons inside the circle
  void search(const Point3& point, 
              const Vector3& normal,
              const double square_radius, 
              PhotonList& photon_list) const;

  //! Store a photon cache
  void store(const int thread_id,
             const Point3& point,
             const Vector3& vin,
             const Spectra& photon_energy,
             const bool wavelength_is_selected);

 private:
  using NodeIterator = typename std::vector<MapNode*>::iterator;


  //! Return the level of tree
  std::size_t getTreeLevel(std::size_t num_of_nodes) const;

  //! Return the longest axis
  std::size_t getLongestAxis(NodeIterator begin, NodeIterator end) const;

  //! Initialize
  void initialize(RendererSystem& system);

  //! Split at median
  void splitMedian(RendererSystem& system, 
                   const std::size_t number, 
                   NodeIterator begin, 
                   NodeIterator end);


  static constexpr std::size_t kNonThreadLevel = 8;

  std::vector<std::vector<Cache>> thread_photon_cache_list_;
  std::vector<std::vector<MapNode>> thread_node_list_;
  std::vector<MapNode*> node_reference_list_;
  std::vector<const MapNode*> tree_;
  std::vector<std::future<void>> result_list_;
};

//! \} DataStructure

} // namespace reflect

#include "photon_map-inl.hpp"

#endif // _REFLECT_PHOTON_MAP_HPP_
