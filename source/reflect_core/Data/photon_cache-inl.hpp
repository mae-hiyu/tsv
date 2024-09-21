/*!
  \file photon_cache-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_PHOTON_CACHE_INL_HPP_
#define _REFLECT_PHOTON_CACHE_INL_HPP_

#include "photon_cache.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
PhotonCache<kSampleSize>::PhotonCache(const Spectra& energy,
                                      const Point3& point,
                                      const Vector3& vin,
                                      const bool wavelength_is_selected) :
    energy_{energy},
    point_{point},
    vin_{vin},
    wavelength_is_selected_{wavelength_is_selected}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
const Vector3& PhotonCache<kSampleSize>::incidentDirection() const
{
  return vin_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
const Point3& PhotonCache<kSampleSize>::point() const
{
  return point_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t PhotonCache<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(energy_);
  size += PRINT_VARIABLE_DATA(point_);
  size += PRINT_VARIABLE_DATA(vin_);
  size += PRINT_VARIABLE_DATA(wavelength_is_selected_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto PhotonCache<kSampleSize>::energy() const -> const Spectra&
{
  return energy_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool PhotonCache<kSampleSize>::wavelengthIsSelected() const
{
  return wavelength_is_selected_;
}

} // namespace reflect

#endif // _REFLECT_PHOTON_CACHE_INL_HPP_
