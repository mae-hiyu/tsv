/*!
  \file sampled_wavelengths.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_WAVELENGTHS_HPP_
#define _REFLECT_SAMPLED_WAVELENGTHS_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
// Reflect
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/wavelength_samples.hpp"

// Forward declaration
class QString;

namespace reflect {

// Forward declaration
class CumulativeSpectralDistribution;
class ColorSystem;
class Sampler;
class World;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class SampledWavelengths
{
 public:
  using Intensities = IntensitySamples<kSampleSize>;
  using Wavelengths = WavelengthSamples<kSampleSize>;


  //! Create a sampled wavelengths
  SampledWavelengths();


  //! Return the inverse probability array
  const Intensities& inverseProbabilities() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Select primary wavelength randomly
  template <std::size_t kMax>
  void selectPrimaryWavelength(Sampler& sampler);

  //! Set wavelength
  void set(const std::size_t index, 
           const std::size_t wavelength, 
           const double inverse_probability);

  //! Return the size
  static constexpr std::size_t size() 
  {
    return kSampleSize;
  }

  //! Return the wavelength array
  const Wavelengths& wavelengths() const;

 private:
  Intensities inverse_probabilities_;
  Wavelengths wavelengths_;
};

template <std::size_t kSampleSize>
using WavelengthSampler = std::function<SampledWavelengths<kSampleSize> (Sampler&)>;

//! Combine all light pdf
SpectralDistribution calculateLightPdf(const World& world);

//! Combine all reflectance pdf
SpectralDistribution calculateReflectancePdf(const World& world);

//! Make light based wavelngth importance sampler
//template <std::size_t kSampleSize>
//WavelengthSampler<kSampleSize> makeLightBasedImportanceSampler(const World& world);

//! Make light based wavelength stratified sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeLightsBasedStratifiedSampler(const World& world);

//! Make light and reflectance based wavelength importance sampler
//template <std::size_t kSampleSize>
//WavelengthSampler<kSampleSize> makeLightAndReflectanceBasedImportanceSampler(
//    const World& world);

//! Make light and reflectance based wavelength stratified sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeLightsAndMaterialsPlusBasedStratifiedSampler(
    const World& world);

//! Make light and reflectance based wavelength stratified sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeLightsAndMaterialsMultiBasedStratifiedSampler(
    const World& world);

//! Make reflectance based wavelngth importance sampler
//template <std::size_t kSampleSize>
//WavelengthSampler<kSampleSize> makeReflectanceBasedImportanceSampler(
//    const World& world);

//! Make reflectance based wavelength stratified sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeMateirlasBasedStratifiedSampler(
    const World& world);


template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightAndTSVmMultiBasedStratifiedSampler(const World& world);


//!Make tristimulus values based wavelengt importance sampler
template<std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTristimulusValuesBasedStratifiedSampler();
template<std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVXStratifiedSampler();
template<std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVYStratifiedSampler();
template<std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVZStratifiedSampler();

// template <std::size_t kSampleSize>
// WavelengthSampler<kSampleSize> makeTSVLightStratifiedSampler(const World& world);

template <std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVXLightStratifiedSampler(const World& world);
template <std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVXLightStratifiedSampler(const World& world);
template <std::size_t kXYZSampleSize>
WavelengthSampler<kXYZSampleSize> makeTSVXLightStratifiedSampler(const World& world);



//! Make wavelngth importance sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeImportanceSampler(
    const SpectralDistribution& inverse_pdf,
    const CumulativeSpectralDistribution& cdf);

//! Make wavelngth stratified sampler
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeStratifiedSampler(
    const SpectralDistribution& inverse_pdf,
    const CumulativeSpectralDistribution& cdf);

//! Make wavelengths sampling method
template <std::size_t kSampleSize>
WavelengthSampler<kSampleSize> makeWavelengthSampler(
    const ColorSystem& color_system,
    const QString& method,
    const World& world);

//! Sample RGB wavelengths
template <std::size_t kSampleSize>
SampledWavelengths<kSampleSize> sampleRgbWavelengths(Sampler& sampler);

//! Sample wavelengths using stratified sampling method
template <std::size_t kSampleSize>
SampledWavelengths<kSampleSize> sampleStratifiedWavelengths(Sampler& sampler);

//! Sample wavelengths randomly
template <std::size_t kSampleSize>
SampledWavelengths<kSampleSize> sampleWavelengthsRandomly(Sampler& sampler);

//! Sample wavelengths regularly
template <std::size_t kSampleSize>
SampledWavelengths<kSampleSize> sampleWavelengthsRegularly(Sampler& sampler);

//! \} Sampling

} // namespace reflect

#include "sampled_wavelengths-inl.hpp"

#endif // _REFLECT_SAMPLED_WAVELENGTHS_HPP_
