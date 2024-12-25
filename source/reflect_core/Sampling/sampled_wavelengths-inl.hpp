/*!
  \file sampled_wavelengths-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_WAVELENGTHS_INL_HPP_
#define _REFLECT_SAMPLED_WAVELENGTHS_INL_HPP_

#include "sampled_wavelengths.hpp"
// Standard C++ library
#include <iostream>
#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
// Qt
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "cumulative_distribution_function.hpp"
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/wavelength_samples.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"
#include <fstream> 

namespace reflect {

// Forward declaration
class World;

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledWavelengths<kSampleSize>::SampledWavelengths()
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledWavelengths<kSampleSize>::inverseProbabilities() const
    -> const Intensities&
{
  return inverse_probabilities_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> template <std::size_t kMax> inline
void SampledWavelengths<kSampleSize>::selectPrimaryWavelength(Sampler& sampler)
{
  constexpr std::size_t min = 0;
  const std::size_t selected_index = sampler.sample(min, kMax);
  // const std::size_t selected_index = 0;
  wavelengths_.setPrimaryWavelength(selected_index);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void SampledWavelengths<kSampleSize>::set(const std::size_t index, 
                                          const std::size_t wavelength,
                                          const double inverse_probability)
{
  wavelengths_[index] = wavelength;
  inverse_probabilities_[index] = inverse_probability;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SampledWavelengths<kSampleSize>::wavelengths() const -> const Wavelengths&
{
  return wavelengths_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightBasedImportanceSampler(const World& world)
{
 const auto pdf = calculateLightPdf(world);
 pdf.save("light_distribution.csv");
 SpectralDistribution inverse_pdf;
 for (std::size_t i = 0; i < pdf.size(); ++i)
   inverse_pdf[i] = 1.0 / pdf[i];
 CumulativeDistributionFunction cdf{pdf};

 return makeImportanceSampler<kSampleSize>(inverse_pdf, cdf);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightsBasedStratifiedSampler(const World& world)
{
  const auto pdf = calculateLightPdf(world);
  pdf.save("lights_distribution.csv");
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];

  // // For TestScene9 only
  // for( std::size_t i = 0; i < pdf.size(); ++i)
  //   inverse_pdf[i] = 167818.596/ pdf.size();

  inverse_pdf.save("inverse_pdf.csv");
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightAndReflectanceBasedImportanceSampler(
   const World& world)
{
 constexpr double weight_l = 0.5;
 constexpr double weight_r = 1.0 - weight_l;

 const auto pdf = calculateLightPdf(world) * weight_l +
                  calculateReflectancePdf(world) * weight_r;
 pdf.save("light_and_reflectance_distribution.csv");
 SpectralDistribution inverse_pdf;
 for (std::size_t i = 0; i < pdf.size(); ++i)
   inverse_pdf[i] = 1.0 / pdf[i];
 CumulativeDistributionFunction cdf{pdf};

 return makeImportanceSampler<kSampleSize>(inverse_pdf, cdf);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightsAndMaterialsPlusBasedStratifiedSampler(
    const World& world)
{
  constexpr double weight_l = 0.5;
  constexpr double weight_r = 1.0 - weight_l;

  const auto pdf = calculateLightPdf(world) * weight_l +
                   calculateReflectancePdf(world) * weight_r;
  pdf.save("lights_and_materials_plus_distribution.csv");
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightsAndMaterialsMultiBasedStratifiedSampler(
    const World& world)
{
  const auto pdf = (calculateLightPdf(world) * calculateReflectancePdf(world)).normalized();
  pdf.save("lights_and_materials_multi_distribution.csv");
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);
}

template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeLightAndTSVmMultiBasedStratifiedSampler(
    const World& world
) {
  constexpr double weight_l = 0.5;
  constexpr double weight_r = 1.0 - weight_l;

  const auto pdfx = makeSpectra(":/property/cie_sco_2degree_xbar.csv").normalized();
  const auto pdfy = makeSpectra(":/property/cie_sco_2degree_ybar.csv").normalized();
  const auto pdfz = makeSpectra(":property/cie_sco_2degree_zbar.csv").normalized();

  const auto pdfxyz = (pdfx + pdfy + pdfz).normalized();

  const auto pdf = calculateLightPdf(world) * weight_l + pdfxyz * weight_r;
  SpectralDistribution inverse_pdf;
  for(std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);                  
}
/*!
  \details
  No detailed.
  */
//template <std::size_t kSampleSize> inline
//WavelengthSampler<kSampleSize> makeReflectanceBasedImportanceSampler(
//    const World& world)
//{
//  const auto pdf = calculateReflectancePdf(world);
//  pdf.save("reflectance_distribution.csv");
//  SpectralDistribution inverse_pdf;
//  for (std::size_t i = 0; i < pdf.size(); ++i)
//    inverse_pdf[i] = 1.0 / pdf[i];
//  CumulativeDistributionFunction cdf{pdf};
//
//  return makeImportanceSampler<kSampleSize>(inverse_pdf, cdf);
//}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeMaterialsBasedStratifiedSampler(
    const World& world)
{
  const auto pdf = calculateReflectancePdf(world);
  pdf.save("materials_distribution.csv");
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);
}


/*!
  \details
  No detailed.
*/

// template <std::size_t kSampleSize>
// WavelengthSampler<kSampleSize> makeTSVLightStratifiedSampler(const World& world) {
//   // 各サンプルソースの数を計算
//   constexpr std::size_t tsv_samples = kSampleSize / 6; // X, Y, Z それぞれのためのサンプル数
//   constexpr std::size_t light_samples = kSampleSize / 2; // 光源のためのサンプル数
//   constexpr std::size_t remaining_samples = kSampleSize - 3 * tsv_samples - light_samples; // 残りのサンプル

//   auto tsv_x_sampler = makeTSVXStratifiedSampler<tsv_samples>();
//   auto tsv_y_sampler = makeTSVYStratifiedSampler<tsv_samples>();
//   auto tsv_z_sampler = makeTSVZStratifiedSampler<tsv_samples>();
//   auto light_sampler = makeLightBasedImportanceSampler<light_samples>(world);

//   return [&tsv_x_sampler, &tsv_y_sampler, &tsv_z_sampler, &light_sampler, &world](Sampler& sampler) -> SampledWavelengths<kSampleSize> {
//     SampledWavelengths<kSampleSize> sampled_wavelengths;
//     // TSV X, Y, Zサンプルを取得
//     auto sampled_tsv_x = tsv_x_sampler(sampler);
//     auto sampled_tsv_y = tsv_y_sampler(sampler);
//     auto sampled_tsv_z = tsv_z_sampler(sampler);
//     // Light source samples
//     auto sampled_light = light_sampler(sampler);

//     // Combine samples into a single SampledWavelengths object
//     for (std::size_t i = 0; i < tsv_samples; ++i) {
//       sampled_wavelengths.set(i, sampled_tsv_x.wavelengths()[i], sampled_tsv_x.inverseProbabilities()[i]/6);
//       sampled_wavelengths.set(tsv_samples + i, sampled_tsv_y.wavelengths()[i], sampled_tsv_y.inverseProbabilities()[i]/6);
//       sampled_wavelengths.set(2 * tsv_samples + i, sampled_tsv_z.wavelengths()[i], sampled_tsv_z.inverseProbabilities()[i]/6);
//     }
//     for (std::size_t i = 0; i < light_samples; ++i) {
//       sampled_wavelengths.set(3 * tsv_samples + i, sampled_light.wavelengths()[i], sampled_light.inverseProbabilities()[i]/2);
//     }

//     return sampled_wavelengths;
//   };
// }

template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeTristimulusValuesBasedStratifiedSampler()
{

  const auto pdfx = makeSpectra(":/property/cie_sco_2degree_xbar.csv").normalized();
  const auto pdfy = makeSpectra(":/property/cie_sco_2degree_ybar.csv").normalized();
  const auto pdfz = makeSpectra(":property/cie_sco_2degree_zbar.csv").normalized();

  const auto pdf = (pdfx + pdfy + pdfz).normalized();
  pdfx.save("x.csv");
  pdfy.save("y.csv");
  pdfz.save("z.csv");
  pdf.save("xyz.csv");
  // reflectance_pdf.save("materials_distribution.csv");
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kSampleSize>(inverse_pdf, cdf);
}


/*!
  \details
  No detailed.
  */
template <std::size_t kXYZSampleSize> inline
WavelengthSampler<kXYZSampleSize> makeTSVXStratifiedSampler()
{
  const auto pdf = makeSpectra(":/property/cie_sco_2degree_xbar.csv").normalized();
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kXYZSampleSize>(inverse_pdf, cdf);
}
template <std::size_t kXYZSampleSize> inline
WavelengthSampler<kXYZSampleSize> makeTSVYStratifiedSampler()
{
  const auto pdf = makeSpectra(":/property/cie_sco_2degree_ybar.csv").normalized();
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kXYZSampleSize>(inverse_pdf, cdf);
}

template <std::size_t kXYZSampleSize> inline
WavelengthSampler<kXYZSampleSize> makeTSVZStratifiedSampler()
{
  const auto pdf = makeSpectra(":property/cie_sco_2degree_zbar.csv").normalized();
  SpectralDistribution inverse_pdf;
  for (std::size_t i = 0; i < pdf.size(); ++i)
    inverse_pdf[i] = 1.0 / pdf[i];
  CumulativeDistributionFunction cdf{pdf};

  return makeStratifiedSampler<kXYZSampleSize>(inverse_pdf, cdf);
}





/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeImportanceSampler(
    const SpectralDistribution& inverse_pdf,
    const CumulativeDistributionFunction& cdf)
{
  WavelengthSampler<kSampleSize> wavelength_sampler{
  [inverse_pdf, cdf](Sampler& sampler)
  {
    std::array<std::size_t, kSampleSize> wavelengths;
    for (std::size_t i = 0; i < kSampleSize; ++i) {
      const double y = sampler.sample(0.0, 1.0);
      const std::size_t wavelength = getWavelength(cdf.inverseFunction(y));
      wavelengths[i] = wavelength;
    }
    std::sort(wavelengths.begin(), wavelengths.end());

    SampledWavelengths<kSampleSize> sampled_wavelengths;
    for (std::size_t i = 0; i < kSampleSize; ++i) {
      const std::size_t wavelength = wavelengths[i];
      constexpr double k = 1.0 / cast<double>(kSampleSize);
      const double inverse_probability = k * inverse_pdf.getByWavelength(wavelength);
      sampled_wavelengths.set(i, wavelengths[i], inverse_probability);
    }
    sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);
    return sampled_wavelengths;
  }};
  return wavelength_sampler;
}


template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeStratifiedSampler(
    const SpectralDistribution& inverse_pdf,
    const CumulativeDistributionFunction& cdf)
{
  // ファイル出力用のストリーム

  WavelengthSampler<kSampleSize> wavelength_sampler{
  [inverse_pdf, cdf](Sampler& sampler)
  {
    constexpr double k = 1.0 / cast<double>(kSampleSize);
    std::array<std::size_t, kSampleSize> wavelengths;
    for (std::size_t i = 0; i < kSampleSize; ++i) {
      // 乱数を生成
      const double sample = sampler.sample(0.0, 1.0);

      std::ofstream sample_file("./samples.txt", std::ios::app); // 追記モードで開く

      if (!sample_file.is_open()) {
        std::cerr << "Error: Unable to open samples.txt" << std::endl;
        throw std::runtime_error("File open error");
      }
      // ファイルに出力
      if (!sample_file) {
        std::cerr << "Error: Unable to write to samples.txt" << std::endl;
        throw std::runtime_error("File write error");
      }
      sample_file << sample << "\n";
      sample_file.flush();

      // 波長を計算
      const double y = k * (cast<double>(i) + sample);
      const std::size_t wavelength = getWavelength(cdf.inverseFunction(y));
      wavelengths[i] = wavelength;
      sample_file.close();
    }
    SampledWavelengths<kSampleSize> sampled_wavelengths;
    for (std::size_t i = 0; i < kSampleSize; ++i) {
      const std::size_t wavelength = wavelengths[i];
      const double inverse_probability = k * inverse_pdf.getByWavelength(wavelength);
      sampled_wavelengths.set(i, wavelengths[i], inverse_probability);
    }
    sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);
    return sampled_wavelengths;
  }};
  return wavelength_sampler;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
WavelengthSampler<kSampleSize> makeWavelengthSampler(
    const ColorSystem& color_system,
    const QString& method, 
    const World& world)
{
  WavelengthSampler<kSampleSize> wavelength_sampler;

  if (color_system.isRgbRenderingMode()) {
    wavelength_sampler = [](Sampler& sampler)
    {
      return sampleRgbWavelengths<kSampleSize>(sampler);
    };
  }
  else {
    switch (zisc::toHash32(method.toStdString().c_str())) {
     case zisc::toHash32(keyword::regular_sampling):
      wavelength_sampler = sampleWavelengthsRegularly<kSampleSize>;
      break;
     case zisc::toHash32(keyword::random_sampling):
      wavelength_sampler = sampleWavelengthsRandomly<kSampleSize>;
      break;
     case zisc::toHash32(keyword::stratified_sampling):
      wavelength_sampler = sampleStratifiedWavelengths<kSampleSize>;
      break;
     case zisc::toHash32(keyword::lights_based_importance_sampling):
      wavelength_sampler = makeLightsBasedStratifiedSampler<kSampleSize>(world);
      // wavelength_sampler = makeLightBasedImportanceSampler<kSampleSize>(world);
      break;
     case zisc::toHash32(keyword::materials_based_importance_sampling):
      wavelength_sampler = makeMaterialsBasedStratifiedSampler<kSampleSize>(world);
      break;
     case zisc::toHash32(keyword::lights_and_materials_plus_based_importance_sampling):
      wavelength_sampler = makeLightsAndMaterialsPlusBasedStratifiedSampler<kSampleSize>(world);
      break;
     case zisc::toHash32(keyword::lights_and_materials_multi_based_importance_sampling):
      wavelength_sampler = makeLightsAndMaterialsMultiBasedStratifiedSampler<kSampleSize>(world);
      break;
      case zisc::toHash32(keyword::tristimulus_values_importance_sampling):
      wavelength_sampler = makeTristimulusValuesBasedStratifiedSampler<kSampleSize>();
      // wavelength_sampler = makeTSVZStratifiedSampler<kSampleSize>();
      break;
      case zisc::toHash32(keyword::lights_and_tsv_multi_based_importance_sampling):
      wavelength_sampler = makeLightAndTSVmMultiBasedStratifiedSampler<kSampleSize>(world);
      // wavelength_sampler = makeTSVZStratifiedSampler<kSampleSize>();
      break;
     default:
      zisc::raiseError("SystemError: Unsupported wavelength sampler is specified.");
      break;
    }
  }
  return wavelength_sampler;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t SampledWavelengths<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(inverse_probabilities_);
  size += PRINT_VARIABLE_DATA(wavelengths_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledWavelengths<kSampleSize> sampleRgbWavelengths(Sampler& sampler)
{
  SampledWavelengths<kSampleSize> sampled_wavelengths;
  sampled_wavelengths.set(0, kBlueWavelength, 1.0);
  sampled_wavelengths.set(1, kGreenWavelength, 1.0);
  sampled_wavelengths.set(2, kRedWavelength, 1.0);

  constexpr std::size_t n = 3;

  for (std::size_t i = n; i < SampledWavelengths<kSampleSize>::size(); ++i)
    sampled_wavelengths.set(i, kLongestWavelength - kWavelengthResolution, 0.0);

  sampled_wavelengths.template selectPrimaryWavelength<n>(sampler);
  return sampled_wavelengths;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledWavelengths<kSampleSize> sampleStratifiedWavelengths(Sampler& sampler)
{
  constexpr double interval = cast<double>(kSpectraSize) / 
                              cast<double>(kSampleSize);
  constexpr double inverse_probability = interval;

  SampledWavelengths<kSampleSize> sampled_wavelengths;
  for (std::size_t i = 0; i < SampledWavelengths<kSampleSize>::size(); ++i) {
    const double position = interval * (cast<double>(i) + sampler.sample(0.0, 1.0));
    const std::size_t index = cast<std::size_t>(position);
    const std::size_t wavelength = getWavelength(index);
    sampled_wavelengths.set(i, wavelength, inverse_probability);
  }
  sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);
  return sampled_wavelengths;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledWavelengths<kSampleSize> sampleWavelengthsRandomly(Sampler& sampler)
{
  constexpr double inverse_probability = cast<double>(kSpectraSize) / 
                                         cast<double>(kSampleSize);

  std::array<std::size_t, kSampleSize> wavelengths;
  for (std::size_t i = 0; i < SampledWavelengths<kSampleSize>::size(); ++i) {
    const double position = cast<double>(kSpectraSize) * sampler.sample(0.0, 1.0);
    const std::size_t index = cast<std::size_t>(position);
    const std::size_t wavelength = getWavelength(index);
    wavelengths[i] = wavelength;
  }
  std::sort(wavelengths.begin(), wavelengths.end());

  SampledWavelengths<kSampleSize> sampled_wavelengths;
  for (std::size_t i = 0; i < SampledWavelengths<kSampleSize>::size(); ++i)
    sampled_wavelengths.set(i, wavelengths[i], inverse_probability);
  sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);
  return sampled_wavelengths;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledWavelengths<kSampleSize> sampleWavelengthsRegularly(Sampler& sampler)
{
  constexpr double interval = cast<double>(kSpectraSize) / 
                              cast<double>(kSampleSize);
  constexpr double inverse_probability = interval;

  SampledWavelengths<kSampleSize> sampled_wavelengths;
  for (std::size_t i = 0; i < SampledWavelengths<kSampleSize>::size(); ++i) {
    const std::size_t index = cast<std::size_t>(interval * cast<double>(i));
    const std::size_t wavelength = getWavelength(index);
    sampled_wavelengths.set(i, wavelength, inverse_probability);
  }
  sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);
  return sampled_wavelengths;
}

} // namespace reflect

#endif // _REFLECT_SAMPLED_WAVELENGTHS_INL_HPP_
