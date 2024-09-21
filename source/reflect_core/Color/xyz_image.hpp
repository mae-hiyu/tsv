/*!
  \file xyz_image.hpp
  \author takemura
  */

#pragma once

// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"
#include "xyz_image_interface.hpp"

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
class XyzImage : public XyzImageInterface
{
 public:
  //! Create a xyz image
  XyzImage(const std::size_t width, const std::size_t height);


  //! Add radiance from a sample
  template <std::size_t kSampleSize>
  void addXyzContribution(
      const std::size_t x,
      const std::size_t y,
      const SampledSpectra<kSampleSize>& contribution);

  //! Clear xyz image buffer
  void clear() override;

  //! Save xyz image
  void save(const std::size_t pass, const QString& file_path) const override;

  //! Convert xyz image to hdr image
  void toHdrImage(RendererSystem& system,
                  const ColorSystem& color_system,
                  const std::size_t pass, 
                  HdrImage& hdr_image) const override;

  //! Return the xyz image type
  XyzImageType type() const override;

 private:
  //! Initialize
  void initialize();


  std::vector<SpectralDistribution> buffer_;
};

//! \} Color

} // namespace reflect

#include "xyz_image-inl.hpp"

