/*!
  \file wavelength_samples.hpp
  \author takemura
  */

#ifndef _REFLECT_WAVELENGTH_SAMPLE_HPP_
#define _REFLECT_WAVELENGTH_SAMPLE_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"

namespace reflect {

//! \addtogroup Data
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class WavelengthSamples
{
 public:
  //! Create wavelengths
  WavelengthSamples();

  //! Return the wavelength by the index
  std::size_t& operator[](const std::size_t index);

  //! Return the wavelength by the index
  const std::size_t& operator[](const std::size_t index) const;


  //! Return the inverse probability of selection of primary wavelength
  static constexpr double primaryInverseProbability()
  {
    return static_cast<double>(kSampleSize);
  }

  //! Return the primary wavelength index
  std::size_t primaryWavelengthIndex() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Set primary wavelength
  void setPrimaryWavelength(const std::size_t index);

  // for TSV rendering only kSampleSize = 3
  void setXYZwavelength(const std::size_t wavelength, const std::size_t index);


  //! Return the size
  static constexpr std::size_t size()
  {
    return kSampleSize;
  }
 private:
  std::size_t wavelengths_[kSampleSize];
  std::size_t primary_index_; //!< The index of primary wavelength
};

//! \} Data

} // namespace reflect

#include "wavelength_samples-inl.hpp"

#endif // _REFLECT_WAVELENGTH_SAMPLE_HPP_
