/*!
  \file spectral_distribution.cpp
  \author takemura
  */

#include "spectral_distribution.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <utility>
// Qt
#include <QColor>
#include <QFile>
#include <QIODevice>
#include <QSettings>
#include <QString>
#include <QTextStream>
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/csv.hpp"
#include "zisc/linear_interp.hpp"
#include "zisc/math.hpp"
#include "zisc/matrix.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "color_space.hpp"
#include "keyword.hpp"
#include "rgb_color.hpp"
#include "reflect_config.hpp"
#include "xyz_color.hpp"
#include "xyz_color_matching_function.hpp"
//#include "Data/wavelength_samples.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
//#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

//! Check if the data is RGB
bool isRgbData(const QSettings& settings, const QString& prefix);

//! Load spectra data from a spectra file
zisc::LinearInterp<double> loadSpectraData(const QString& file_path);

//! Make a rgb
RgbColor makeRgb(const QSettings& settings, const QString& prefix);

//! Convert emissive spectra to RGB spectra
SpectralDistribution toEmissiveRgbSpectra(const ColorSystem& color_system,
                                          const SpectralDistribution& spectra);

//! Convert reflective spectra to RGB spectra
SpectralDistribution toReflectiveRgbSpectra(const ColorSystem& color_system,
                                            const SpectralDistribution& spectra);

/*!
  \details
  No detailed.
  */
void SpectralDistribution::clamp(const double min, const double max)
{
  distribution_.clamp(min, max);
}

/*!
  \details
  No detailed.
  */
void SpectralDistribution::save(const QString& file_name) const
{
  // Spectra information
  constexpr std::size_t lambda_min = kShortestWavelength;
  constexpr std::size_t delta_lambda = kWavelengthResolution;
  constexpr std::size_t n = kSpectraSize;

  // Open distribution file
  QFile distribution_file{file_name};
  distribution_file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream distribution_text{&distribution_file};

  for (std::size_t i = 0; i < n; ++i) {
    const std::size_t lambda = lambda_min + i * delta_lambda;
    distribution_text << lambda << ", " << distribution_[i] << endl;
  }
}

/*!
  \details
  No detailed.
  */
XyzColor SpectralDistribution::toEmissiveXyz(const ColorSystem& color_system) const
{
  if (color_system.isRgbRenderingMode()) {
    const RgbColor rgb{getByWavelength(kRedWavelength),
                       getByWavelength(kGreenWavelength),
                       getByWavelength(kBlueWavelength)};
    return rgb.toXyz(getRgbToXyzMatrix(color_system.colorSpace()));
  }
  else {
    const auto& cmf = color_system.xyzColorMatchingFunction();
    return cmf.toXyzInEmissiveCase(*this);
  }
}

/*!
  \details
  No detailed.
  */
XyzColor SpectralDistribution::toReflectiveXyz(const ColorSystem& color_system) const
{
  if (color_system.isRgbRenderingMode()) {
    const RgbColor rgb{getByWavelength(kRedWavelength),
                       getByWavelength(kGreenWavelength),
                       getByWavelength(kBlueWavelength)};
    return rgb.toXyz(getRgbToXyzMatrix(color_system.colorSpace()));
  }
  else {
    const auto& cmf = color_system.xyzColorMatchingFunction();
    return cmf.toXyzInReflectiveCase(*this);
  }
}

/*!
  \details
  No detailed.
  */
bool isRgbData(const QSettings& settings, const QString& prefix)
{
  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  return type == keyword::rgb;
}

/*!
  \details
  No detailed.
  */
zisc::LinearInterp<double> loadSpectraData(const QString& file_path)
{
  // Open distribution file
  QFile csv_file{file_path};
  csv_file.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream csv_text{&csv_file};

  // Remove header
  csv_text.readLine();
  csv_text.readLine();

  // Load distribution
  zisc::Csv<double, double> csv;
  for (auto line = csv_text.readLine(); !line.isNull(); line = csv_text.readLine())
    csv.append(line.toStdString());

  // Set distribution
  zisc::LinearInterp<double> spectra_data;
  for (std::size_t i = 0; i < csv.rowSize(); ++i)
    spectra_data.add(csv.get<0>(i), csv.get<1>(i));
  return spectra_data;
}

/*!
  \details
  No detailed.
  */
SpectralDistribution makeEmissiveDistribution(const ColorSystem& color_system,
                                              const QSettings& settings, 
                                              const QString& prefix)
{
  if (isRgbData(settings, prefix)) {
    const auto rgb = makeRgb(settings, prefix);
    return (color_system.isRgbRenderingMode())
        ? toRgbSpectra(rgb)
        : toSpectra(color_system, rgb);
  }
  else {
    auto spectra = makeSpectra(settings, prefix);
    spectra.clamp(0.0, spectra.max());
    spectra = spectra.normalized();
    return (color_system.isRgbRenderingMode())
        ? toEmissiveRgbSpectra(color_system, spectra)
        : spectra;
  }
}

/*!
  \details
  No detailed.
  */
SpectralDistribution makeReflectiveDistribution(const ColorSystem& color_system,
                                                const QSettings& settings, 
                                                const QString& prefix)
{
  if (isRgbData(settings, prefix)) {
    const auto rgb = makeRgb(settings, prefix);
    return (color_system.isRgbRenderingMode())
        ? toRgbSpectra(rgb)
        : toSpectra(color_system, rgb);
  }
  else {
    auto spectra = makeSpectra(settings, prefix);
    spectra.clamp(0.0, 1.0);
    return (color_system.isRgbRenderingMode())
        ? toReflectiveRgbSpectra(color_system, spectra)
        : spectra;
  }
}

/*!
  \details
  No detailed.
  */
RgbColor makeRgb(const QSettings& settings, const QString& prefix)
{
  const auto color = value<QColor>(settings, prefix + "/" + keyword::color);
  return RgbColor{color};
}

/*!
  \details
  No detailed.
  */
SpectralDistribution makeSpectra(const QSettings& settings, const QString& prefix)
{
  const auto key = prefix + "/" + keyword::spectra_file;
  const auto file_path = value<QString>(settings, key);
  return makeSpectra(file_path);
}

/*!
  \details
  No detailed.
  */
SpectralDistribution makeSpectra(const QString& file_path)
{
  auto spectra_data = loadSpectraData(file_path);
  SpectralDistribution spectra;
  for (std::size_t index = 0; index < kSpectraSize; ++index) {
    const double lambda = cast<double>(getWavelength(index));
    spectra.set(index, spectra_data(lambda));
  }
  return spectra;
}

/*!
  \details
  No detailed.
  */
SpectralDistribution toEmissiveRgbSpectra(const ColorSystem& color_system,
                                          const SpectralDistribution& spectra)
{
  const auto& cmf = color_system.xyzColorMatchingFunction();
  const auto xyz = cmf.toXyzInEmissiveCase(spectra);
  auto rgb = xyz.toRgb(getXyzToRgbMatrix(color_system.colorSpace()));
  rgb.clamp();
  return toRgbSpectra(rgb);
}

/*!
  \details
  No detailed.
  */
SpectralDistribution toReflectiveRgbSpectra(const ColorSystem& color_system,
                                            const SpectralDistribution& spectra)
{
  const auto& cmf = color_system.xyzColorMatchingFunction();
  const auto xyz = cmf.toXyzInReflectiveCase(spectra);
  auto rgb = xyz.toRgb(getXyzToRgbMatrix(color_system.colorSpace()));
  rgb.clamp();
  return toRgbSpectra(rgb);
}

/*!
  \details
  No detailed.
  */
SpectralDistribution toRgbSpectra(const RgbColor& rgb)
{
  SpectralDistribution rgb_spectra;
  rgb_spectra.setByWavelength(kBlueWavelength, rgb.blue());
  rgb_spectra.setByWavelength(kGreenWavelength, rgb.green());
  rgb_spectra.setByWavelength(kRedWavelength, rgb.red());
  return rgb_spectra;
}

/*!
  \details
  No detailed.
  */
SpectralDistribution toSpectra(const ColorSystem& color_system, const RgbColor& color)
{
  constexpr double sigma_min = 80.0;
  constexpr double sigma_max = 150.0;
  const double chi_rg = (color.red() + color.green() != 0.0)
      ? zisc::abs(color.red() - color.green()) / (color.red() + color.green())
      : 0.0;
  const double chi_bg = (color.blue() + color.green() != 0.0)
      ? zisc::abs(color.blue() - color.green()) / (color.blue() + color.green())
      : 0.0;
  const double sigma1 = chi_rg * sigma_min + (1.0 - chi_rg) * sigma_max,
               sigma2 = chi_bg * sigma_min + (1.0 - chi_bg) * sigma_max,
               sigma3 = zisc::min(sigma1, sigma2);
  const double tmp1[] = {1.0 / (2.0 * sigma1 * sigma1),
                         1.0 / (2.0 * sigma2 * sigma2),
                         1.0 / (2.0 * sigma3 * sigma3)};
  const double tmp2[] = {1.0 / std::sqrt(2.0 * zisc::kPi * sigma1),
                         1.0 / std::sqrt(2.0 * zisc::kPi * sigma2),
                         1.0 / std::sqrt(2.0 * zisc::kPi * sigma3)};
  const int lambda_list[] = {641, 508, 426};

  const auto f = [&tmp1, &tmp2, &lambda_list](const std::size_t i, const int lambda)
  {
    const int diff_lambda = lambda - lambda_list[i];
    return std::exp(-cast<double>(diff_lambda * diff_lambda) * tmp1[i]) * tmp2[i];
  };

  SpectralDistribution f_bar[3];
  for (std::size_t i = 0; i < 3; ++i) {
    for (std::size_t index = 0; index < kSpectraSize; ++index) {
      const std::size_t wavelength = getWavelength(index);
      f_bar[i].set(index, f(i, cast<int>(wavelength)));
    }
  }

  constexpr double k = cast<double>(kWavelengthResolution) / 19.15;
  const auto& cmf = color_system.rgbColorMatchingFunction();
  const SpectralDistribution* bar[] = {&cmf.redBar(), &cmf.greenBar(), &cmf.blueBar()};
  zisc::Matrix<double, 3, 3> t;
  for (std::size_t i = 0; i < 3; ++i) {
    for (std::size_t j = 0; j < 3; ++j) {
      t(i, j) = k * (*bar[i] * f_bar[j]).sum();
    }
  }
  const auto inverse_t = t.inverseMatrix();
  const auto x = inverse_t * color.data();


  auto spectra = f_bar[0] * x[0] + f_bar[1] * x[1] + f_bar[2] * x[2];
  spectra.clamp(0.0, 1.0);

  return spectra;
}

} // namespace reflect
