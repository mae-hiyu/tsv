/*!
  \file sampled_spectra-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_SPECTRA_INL_HPP_
#define _REFLECT_SAMPLED_SPECTRA_INL_HPP_

#include "sampled_spectra.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "sampled_wavelengths.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/wavelength_samples.hpp"
#include "Utility/size.hpp"



namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra()
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths) :
    wavelengths_{&wavelengths}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths,
                                            const double intensity) :
    wavelengths_{&wavelengths}
{
  intensities_.fill(intensity);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths,
                                            const Intensities& intensities) :
    intensities_{intensities},
    wavelengths_{&wavelengths}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+(const double scalar) const 
    -> SampledSpectra
{
  return *this + SampledSpectra{*wavelengths_, scalar};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+(const SampledSpectra& samples) const
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_,  intensities_ + samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-(const double scalar) const
    -> SampledSpectra
{
  return *this - SampledSpectra{*wavelengths_, scalar};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-(const SampledSpectra& samples) const
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ - samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*(const double scalar) const
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ * scalar};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*(const SampledSpectra& samples) const
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ * samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator/(const SampledSpectra& samples) const
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ / samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+=(const SampledSpectra& samples)
    -> SampledSpectra&
{
  intensities_ += samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-=(const SampledSpectra& samples)
    -> SampledSpectra&
{
  intensities_ -= samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*=(const SampledSpectra& samples)
    -> SampledSpectra&
{
  intensities_ *= samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
double SampledSpectra<kSampleSize>::average() const
{
  constexpr double averager = 1.0 / cast<double>(kSampleSize);
  return intensities_.sum() * averager;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
double SampledSpectra<kSampleSize>::intensity(const std::size_t index) const
{
  return intensities_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool SampledSpectra<kSampleSize>::isZero() const
{
  return intensities_.isZero();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
double SampledSpectra<kSampleSize>::max() const
{
  return intensities_.max();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t SampledSpectra<kSampleSize>::wavelength(const std::size_t index) const
{
  return (*wavelengths_)[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledSpectra<kSampleSize>::wavelengths() const -> const Wavelengths&
{
  return *wavelengths_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t SampledSpectra<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(intensities_);
  size += PRINT_VARIABLE_DATA(wavelengths_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void SampledSpectra<kSampleSize>::setIntensity(const std::size_t index, 
                                               const double intensity)
{
  intensities_.set(index, intensity);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> operator*(const double scalar, 
                                      const SampledSpectra<kSampleSize>& samples)
{
  return samples * scalar;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> makeSampledSpectra(
    const SampledWavelengths<kSampleSize>& sampled_wavelengths)
{

  return SampledSpectra<kSampleSize>{sampled_wavelengths.wavelengths(),
                                     sampled_wavelengths.inverseProbabilities()};
}


/*!
  \details
  for TSV rendering
*/
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> makeSampledSpectra(
    const std::tuple<SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>>
    sampled_wavelengthsXYZ)
{
  SampledWavelengths<kSampleSize> sampled_wavelengths;
  for (std::size_t i = 0; i < kXYZSampleSize; ++i)
  {
    sampled_wavelengths.set(i, std::get<0>(sampled_wavelengthsXYZ).wavelengths()[i]
                     , std::get<0>(sampled_wavelengthsXYZ).inverseProbabilities()[i]/3);
    sampled_wavelengths.set(i+kXYZSampleSize, std::get<1>(sampled_wavelengthsXYZ).wavelengths()[i]
                     , std::get<1>(sampled_wavelengthsXYZ).inverseProbabilities()[i]/3);
    sampled_wavelengths.set(i+kXYZSampleSize*2, std::get<2>(sampled_wavelengthsXYZ).wavelengths()[i]
                     , std::get<2>(sampled_wavelengthsXYZ).inverseProbabilities()[i]/3);
  }


  return SampledSpectra<kSampleSize>{sampled_wavelengths.wavelengths(),
                                     sampled_wavelengths.inverseProbabilities()};
}

template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> makeSampledSpectraXYZLight(
    const std::tuple<SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kXYZSampleSize>, SampledWavelengths<kLightSampleSize>>
     sampled_wavelengthsXYZLight)
{
  SampledWavelengths<kSampleSize> sampled_wavelengths;
  for (std::size_t i = 0; i < kXYZSampleSize; ++i)
  {
    sampled_wavelengths.set(i, std::get<0>(sampled_wavelengthsXYZLight).wavelengths()[i]
                     , std::get<0>(sampled_wavelengthsXYZLight).inverseProbabilities()[i]/6);
    sampled_wavelengths.set(i+kXYZSampleSize, std::get<1>(sampled_wavelengthsXYZLight).wavelengths()[i]
                     , std::get<1>(sampled_wavelengthsXYZLight).inverseProbabilities()[i]/6);
    sampled_wavelengths.set(i+kXYZSampleSize*2, std::get<2>(sampled_wavelengthsXYZLight).wavelengths()[i]
                     , std::get<2>(sampled_wavelengthsXYZLight).inverseProbabilities()[i]/6);
  }
  for (std::size_t i = 0; i < kLightSampleSize; ++i)
  {
    sampled_wavelengths.set(i + 3 * kXYZSampleSize, std::get<3>(sampled_wavelengthsXYZLight).wavelengths()[i], std::get<3>(sampled_wavelengthsXYZLight).inverseProbabilities()[i]/2);
  }

  return SampledSpectra<kSampleSize>{sampled_wavelengths.wavelengths(),
                                     sampled_wavelengths.inverseProbabilities()};
}

/*!
  \details
  No detailed.
  */
//inline
//SampledSpectra sqrt(const SampledSpectra& samples)
//{
//  SampledSpectra spectra{samples.wavelengths()};
//  for (std::size_t index = 0; index < kNumOfSpectraSamples; ++index)
//    spectra.setIntensity(index, zisc::sqrt(samples.intensity(index)));
//  return spectra;
//}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> sample(const SpectralDistribution& distribution,
                                   const WavelengthSamples<kSampleSize>& wavelengths)
{
  IntensitySamples<kSampleSize> intensities;
  for (std::size_t index = 0; index < kSampleSize; ++index)
    intensities.set(index, distribution.getByWavelength(wavelengths[index]));
  return SampledSpectra<kSampleSize>{wavelengths, intensities};
}

} // namespace reflect

#endif // _REFLECT_SAMPLED_SPECTRA_INL_HPP_
