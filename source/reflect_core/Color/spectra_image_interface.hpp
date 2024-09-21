/*!
  \file spectra_image_interface.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRA_IMAGE_INTERFACE_HPP_
#define _REFLECT_SPECTRA_IMAGE_INTERFACE_HPP_

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
enum class SpectraImageType
{
  Spectra = 0,
  Rgb
};

/*!
  \details
  No detailed.
  */
class SpectraImageInterface
{
 public:
  //! Creaet a spectra image
  SpectraImageInterface(const std::size_t width, const std::size_t height);

  virtual ~SpectraImageInterface() {};


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

  //! Save spectra image
  virtual void save(const std::size_t pass, const QString& file_path) const = 0;

  //! Convert spectra image to hdr image
  virtual void toHdrImage(RendererSystem& system,
                          const ColorSystem& color_system,
                          const std::size_t pass, 
                          HdrImage& hdr_image) const = 0;

  //! Return the spectra image type
  virtual SpectraImageType type() const = 0;

  //! Return the width resolution
  std::size_t widthResolution() const;

 private:
  std::size_t width_,
              height_;
};

//! Add spectra contribution to image buffer
template <std::size_t kSampleSize>
void addSpectraContribution(SpectraImageInterface* image,
                            const std::size_t x,
                            const std::size_t y,
                            const SampledSpectra<kSampleSize>& contribution);

//! Add spectra contribution to image buffer
template <std::size_t kSampleSize>
void addRgbContribution(SpectraImageInterface* image,
                        const std::size_t x,
                        const std::size_t y,
                        const SampledSpectra<kSampleSize>& contribution);

//! \} Color

} // namespace reflect

#include "spectra_image_interface-inl.hpp"

#endif // _REFLECT_SPECTRA_IMAGE_INTERFACE_HPP_
