/*!
  \file xyz_image_interface.hpp
  \author takemura
  */

#pragma once

// Standard C++ library
#include <cstddef>

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
enum class XyzImageType
{
  Spectra = 0,
  Rgb
};

/*!
  \details
  No detailed.
  */
class XyzImageInterface
{
 public:
  //! Creaet a xyz image
  XyzImageInterface(const std::size_t width, const std::size_t height);

  virtual ~XyzImageInterface() {};

  //! Add radiance from a sample
  template <std::size_t kSampleSize>
  void addContribution(const std::size_t x,
                       const std::size_t y,
                       const SampledSpectra<kSampleSize>& contribution);

  //! Clear image buffer
  virtual void clear() = 0;

  //! Return the height resolution
  std::size_t heightResolution() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Save xyz image
  virtual void save(const std::size_t pass, const QString& file_path) const = 0;

  //! Convert xyz image to hdr image
  virtual void toHdrImage(RendererSystem& system,
                          const ColorSystem& color_system,
                          const std::size_t pass, 
                          HdrImage& hdr_image) const = 0;

  //! Return the xyz image type
  virtual XyzImageType type() const = 0;

  //! Return the width resolution
  std::size_t widthResolution() const;

 private:
  std::size_t width_,
              height_;
};

//! Add xyz contribution to image buffer
template <std::size_t kSampleSize>
void addSpectraContribution(XyzImageInterface* image,
                            const std::size_t x,
                            const std::size_t y,
                            const SampledSpectra<kSampleSize>& contribution);

//! Add xyz contribution to image buffer
template <std::size_t kSampleSize>
void addRgbContribution(XyzImageInterface* image,
                        const std::size_t x,
                        const std::size_t y,
                        const SampledSpectra<kSampleSize>& contribution);

//! \} Color

} // namespace reflect

#include "xyz_image_interface-inl.hpp"


