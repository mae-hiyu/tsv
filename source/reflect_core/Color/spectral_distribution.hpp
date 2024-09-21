/*!
  \file spectral_distribution.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRAL_DISTRIBUTION_HPP_
#define _REFLECT_SPECTRAL_DISTRIBUTION_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "xyz_color.hpp"

// Forward decralation
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
class RgbColor;

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class SpectralDistribution
{
  static constexpr std::size_t kDistributionSize = kSpectraSize;

 public:
  //! Create empty distribution 
  SpectralDistribution();

  //! Create a distribution
  SpectralDistribution(const zisc::ArithmeticArray<double, kDistributionSize>& property);


  //! Apply addition operation to each element
  SpectralDistribution operator+(const SpectralDistribution& other) const;

  //! Apply subtraction operation to each element
  SpectralDistribution operator-(const SpectralDistribution& other) const;

  //!
  SpectralDistribution operator*(const double scalar) const;

  //! Apply multiplication operation to each element
  SpectralDistribution operator*(const SpectralDistribution& other) const;

  //!
  SpectralDistribution operator/(const double scalar) const;

  //! Apply division operation to each element
  SpectralDistribution operator/(const SpectralDistribution& other) const;

  //!
  SpectralDistribution& operator+=(const SpectralDistribution& other);

  //!
  SpectralDistribution& operator-=(const SpectralDistribution& other);

  //! Apply multiplication operation to each element and asign the result
  SpectralDistribution& operator*=(const double scalar);

  //!
  SpectralDistribution& operator*=(const SpectralDistribution& other);

  //!
  SpectralDistribution& operator/=(const double scalar);

  //!
  SpectralDistribution& operator/=(const SpectralDistribution& other);

  //! Return the point of the distribution by the index
  double& operator[](const std::size_t index);

  //! Return the point of the distribution by the index
  const double& operator[](const std::size_t index) const;


  //! Clamp all elements to the range [min, max]
  void clamp(const double min, const double max);

  //! Fill all elements by the value
  void fill(const double value);

  //! Return the element by the index
  double get(const std::size_t index) const;

  //! Return the element by the wavelength
  double getByWavelength(const std::size_t wavelength) const;

  //! Check if all components are zero
  bool isZero() const;

  //! Return the largest element
  double max() const;

  //! Return the smallest element
  double min() const;

  //! Return the normalized distribution
  SpectralDistribution normalized() const;

  //! Return the spectral distribution 
  const zisc::ArithmeticArray<double, kDistributionSize>& distribution() const;

  //! Save spectral distribution
  void save(const QString& file_name) const;

  //! Set value by the index
  void set(const std::size_t index, const double intensity);

  //! Set value by the wavelength
  void setByWavelength(const std::size_t wavelength, const double intensity);

  //! Get the size of property
  static constexpr std::size_t size()
  {
    return kDistributionSize;
  }

  //! Get sum of intensities
  double sum() const;

  //! Return the emissive xyz color
  XyzColor toEmissiveXyz(const ColorSystem& color_system) const; 

  //! Return the reflective xyz color
  XyzColor toReflectiveXyz(const ColorSystem& color_system) const;

 private:

  zisc::ArithmeticArray<double, kDistributionSize> distribution_;
};

//! Make a emissive spectra
SpectralDistribution makeEmissiveDistribution(const ColorSystem& color_system,
                                              const QSettings& settings,
                                              const QString& prefix);

//! Make a reflective spectra
SpectralDistribution makeReflectiveDistribution(const ColorSystem& color_system,
                                                const QSettings& settings,
                                                const QString& prefix);

//! Make a spectral property
SpectralDistribution makeSpectra(const QSettings& settings, const QString& prefix);

//! Make a spectral property
SpectralDistribution makeSpectra(const QString& file_path);

//! Convert RGB to RGB spectra
SpectralDistribution toRgbSpectra(const RgbColor& color);

//! Convert RGB to spectra
SpectralDistribution toSpectra(const ColorSystem& color_system, 
                               const RgbColor& color);

//! \} Color

} // namespace reflect

#include "spectral_distribution-inl.hpp"

#endif // _REFLECT_SPECTRAL_DISTRIBUTION_HPP_
