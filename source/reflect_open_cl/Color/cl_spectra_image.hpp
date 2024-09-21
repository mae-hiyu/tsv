/*!
  \file cl_spectra_image.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SPECTRA_IMAGE_HPP_
#define _REFLECT_CL_SPECTRA_IMAGE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "Color/spectra_image_interface.hpp"
#include "OpenCL/cl.hpp"
#include "OpenCL/Color/cl_spectral_distribution.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QString;

namespace reflect {

// Forward declaration
class ClCore;
class HdrImage;
class SampledSpectra;

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
class ClSpectraImage : public SpectraImageInterface
{
 public:
  //! Create a spectra image
  ClSpectraImage(const ClCore& core,
                 const std::size_t width, 
                 const std::size_t height);


  //! Add radiance from a sample
  void addRadiance(const std::size_t x, 
                   const std::size_t y,
                   const SampledSpectra& sample) override;

  //! Return the buffer reference
  cl::Buffer& buffer();

  //! Return the memory size
  std::size_t memorySize() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Save spectra image
  void save(const std::size_t pass, const QString& file_path) const override;

  //! Convert spectra image to hdr image
  void toHdrImage(const std::size_t pass, HdrImage& hdr_image) const override;

  //! Update spectra data
  void updateBuffer();

 private:
  //! Initialize
  void initialize();


  std::vector<ClSpectralDistribution> spectra_;
  UniquePointer<cl::Buffer> buffer_;
  const ClCore* core_;
};

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_SPECTRA_IMAGE_HPP_
