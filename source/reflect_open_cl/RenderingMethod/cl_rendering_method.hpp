/*!
  \file cl_rendering_method.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_RENDERING_METHOD_HPP_
#define _REFLECT_CL_RENDERING_METHOD_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
#include <string>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "OpenCL/cl.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declarationn
class ClCore;
class ClScene;
class Sampler;

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
class ClRenderingMethod
{
 public:
  //! Create a rendering method
  ClRenderingMethod(const QSettings& settings, 
                    const ClCore& core,
                    ClScene& scene);

  virtual ~ClRenderingMethod() {}


  //! Render scene
  void operator()(ClCore& core);


  //! Return the buffer memory size
  virtual std::size_t bufferMemorySize() const = 0;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Render scene
  virtual void render(ClCore& core) = 0;

 protected:
  //! Return the buffer memory size
  std::size_t methodBufferMemorySize() const;

  //! Return the sampler options
  const std::string& methodOptions() const;

  //! Return the OpenCL file directory
  std::string openClDirectory() const;

  //! Return the renderer source file list
  std::vector<std::string> sourceFileList() const;

  //! Return the sampler buffer
  cl::Buffer& samplerBuffer();

  //! Set sampler buffer
  void setSamplerBuffer(const QSettings& settings, 
                        const ClCore& core,
                        const std::size_t size);

  //! Return the wavelength sampler buffer
  const cl::Buffer& wavelengthSamplerBuffer() const;

 private:
  //! Get the russian roulette options
  std::string getRussianRouletteOptions(const QSettings& settings) const;

  //! Get the wavelength sampler options
  std::string getWavelengthSamplerOptions(const QSettings& settings) const;

  //! Initialize
  void initialize(const QSettings& settings,
                  const ClCore& core,
                  ClScene& scene);


  UniquePointer<cl::Buffer> sampler_buffer_;
  UniquePointer<cl::Buffer> wavelength_sampler_buffer_;
  std::string method_options_;
};

//! Make rendering method
UniquePointer<ClRenderingMethod> makeClRenderingMethod(
    const QSettings& settings,
    const ClCore& core,
    ClScene& scene);

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_RENDERING_METHOD_HPP_
