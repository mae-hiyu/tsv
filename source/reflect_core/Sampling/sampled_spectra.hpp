/*!
  \file sampled_spectra.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_SPECTRA_HPP_
#define _REFLECT_SAMPLED_SPECTRA_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "Data/wavelength_samples.hpp"


namespace reflect {

// Forward declaration
template <std::size_t> class SampledWavelengths;
class SpectralDistribution;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class SampledSpectra
{
 public:
  using Intensities = IntensitySamples<kSampleSize>;
  using Wavelengths = WavelengthSamples<kSampleSize>;

  //! Create samples
  SampledSpectra();

  //! Create samples
  SampledSpectra(const Wavelengths& wavelengths);

  //! Create samples
  SampledSpectra(const Wavelengths& wavelengths, const double intensity);

  //! Create samples
  SampledSpectra(const Wavelengths& wavelengths, const Intensities& intensities);


  //! Apply addition operation
  SampledSpectra operator+(const double scalar) const;

  //! Apply addition operation to each sample
  SampledSpectra operator+(const SampledSpectra& samples) const;

  //! Apply subtraction operation
  SampledSpectra operator-(const double scalar) const;

  //! Apply subtraction operation to each sample
  SampledSpectra operator-(const SampledSpectra& samples) const;

  //! Multiply each sample with a scalar
  SampledSpectra operator*(const double scalar) const;

  //! Apply multiplication operation to each sample
  SampledSpectra operator*(const SampledSpectra& samples) const;

  //! Apply division operation
  SampledSpectra operator/(const SampledSpectra& samples) const;

  //! Add samples
  SampledSpectra& operator+=(const SampledSpectra& samples);

  //!
  SampledSpectra& operator-=(const SampledSpectra& samples);

  //!
  SampledSpectra& operator*=(const double scalar);

  //! Multiply samples
  SampledSpectra& operator*=(const SampledSpectra& samples);


  // Get the average of intensities
  double average() const;

  //! Get the intensity of wavelength by the index.
  double intensity(const std::size_t index) const;

  //! Check whether intensities of all elements are zero
  bool isZero() const;

  //! Get max intensity
  double max() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Get the number of samples
  static constexpr std::size_t size() 
  {
    return kSampleSize;
  }

  //! Set a intensity.
  void setIntensity(const std::size_t index, const double intensity);

  //! Get a wavelength by index.
  std::size_t wavelength(const std::size_t index) const;

  //! Get a sampled wavelength array.
  const Wavelengths& wavelengths() const;

 private:
  Intensities intensities_;
  const Wavelengths* wavelengths_;
};

//! Multiply each sample with a scalar
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> operator*(const double scalar, 
                                      const SampledSpectra<kSampleSize>& samples);

//! Make a sampled spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> makeSampledSpectra(
    const SampledWavelengths<kSampleSize>& sampled_wavelengths);
// for TSV rendering
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> makeSampledSpectra(
    const std::tuple<SampledWavelengths<kXYZSampleSize>,SampledWavelengths<kXYZSampleSize>,SampledWavelengths<kXYZSampleSize>>
     sampled_wavelengthsXYZ);
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> makeSampledSpectraXYZLight(
    const std::tuple<SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kLightSampleSize>> sampled_wavelengthsXYZLight);



//! Return the sqrt of sample
//SampledSpectra sqrt(const SampledSpectra& samples);

//! Return the sampled spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> sample(const SpectralDistribution& distribution,
                                   const WavelengthSamples<kSampleSize>& wavelengths);

//! \} Sampling

} // namespace reflect

#include "sampled_spectra-inl.hpp"

#endif // _REFLECT_SAMPLED_SPECTRA_HPP_
