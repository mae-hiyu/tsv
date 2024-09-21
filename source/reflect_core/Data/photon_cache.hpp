/*!
  \file photon_cache.hpp
  \author takemura
  */

#ifndef _REFLECT_PHOTON_CACHE_HPP_
#define _REFLECT_PHOTON_CACHE_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

//! \addtogroup Data
//! \{

/*!
  \details
  No detailed.

  \todo memory optimization
  */
template <std::size_t kSampleSize>
class PhotonCache
{
 public:
  using Spectra = SampledSpectra<kSampleSize>;


  //! Create a photon cache
  PhotonCache(const Spectra& energy,
              const Point3& point, 
              const Vector3& vin, 
              const bool wavelength_is_selected);


  //! Return the incident direction to the cached point
  const Vector3& incidentDirection() const;

  //! Return the cached point
  const Point3& point() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the cached radiance
  const Spectra& energy() const;

  //! Check if wavelength selection occured
  bool wavelengthIsSelected() const;

 private:
  const Spectra energy_;
  const Point3 point_;
  const Vector3 vin_;
  bool wavelength_is_selected_;
};

//! \} Data

} // namespace reflect

#include "photon_cache-inl.hpp"

#endif // _REFLECT_PHOTON_CACHE_HPP_
