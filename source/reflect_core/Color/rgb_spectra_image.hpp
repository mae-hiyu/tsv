/*!
  \file rgb_spectra_image.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_SPECTRA_IMAGE_HPP_
#define _REFLECT_RGB_SPECTRA_IMAGE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "rgb_color.hpp"
#include "spectra_image_interface.hpp"

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
class RgbSpectraImage : public SpectraImageInterface
{
 public:
  //! Create a rgb spectra image
  RgbSpectraImage(const std::size_t width, const std::size_t height);


  //! Add radiance from a sample
  template <std::size_t kSampleSize>
  void addRgbContribution(const std::size_t x,
                          const std::size_t y,
                          const SampledSpectra<kSampleSize>& contribution);

  //! Clear RGB image buffer
  void clear() override;

  //! Save spectra image
  void save(const std::size_t pass, const QString& file_path) const override;

  void toHdrImage(RendererSystem& system,
                  const ColorSystem& color_system,
                  const std::size_t pass, 
                  HdrImage& hdr_image) const override;

  //! Return the rgb spectra image type
  SpectraImageType type() const override;

 private:
  //! Initialize
  void initialize();


  std::vector<RgbColor> buffer_;
};

//! \} Color

} // namespace reflect

#include "rgb_spectra_image-inl.hpp"

#endif // _REFLECT_RGB_SPECTRA_IMAGE_HPP_
