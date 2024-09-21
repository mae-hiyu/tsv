/*!
  \file spectra_image.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRA_IMAGE_HPP_
#define _REFLECT_SPECTRA_IMAGE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"
#include "spectra_image_interface.hpp"

// Forward declaration
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
class HdrImage;
class RendererSystem;
template <std::size_t> class SampledSpectra;

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class SpectraImage : public SpectraImageInterface
{
 public:
  //! Create a spectra image
  SpectraImage(const std::size_t width, const std::size_t height);


  //! Add radiance from a sample
  template <std::size_t kSampleSize>
  void addSpectraContribution(
      const std::size_t x,
      const std::size_t y,
      const SampledSpectra<kSampleSize>& contribution);

  //! Clear spectra image buffer
  void clear() override;

  //! Save spectra image
  void save(const std::size_t pass, const QString& file_path) const override;

  //! Convert spectra image to hdr image
  void toHdrImage(RendererSystem& system,
                  const ColorSystem& color_system,
                  const std::size_t pass, 
                  HdrImage& hdr_image) const override;

  //! Return the spectra image type
  SpectraImageType type() const override;

 private:
  //! Initialize
  void initialize();


  std::vector<SpectralDistribution> buffer_;
};

//! \} Color

} // namespace reflect

#include "spectra_image-inl.hpp"

#endif // _REFLECT_SPECTRA_IMAGE_HPP_
