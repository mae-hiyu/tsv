/*!
  \file cl_path_tracing.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_PATH_TRACING_HPP_
#define _REFLECT_CL_PATH_TRACING_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "cl_rendering_method.hpp"
#include "OpenCL/cl.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class ClCore;
class ClScene;
class Scene;

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
class ClPathTracing : public ClRenderingMethod
{
 public:
  // Create a path tracing
  ClPathTracing(const QSettings& settings,
                const ClCore& core,
                ClScene& cl_scene);


  //! Return the buffer memory size
  std::size_t bufferMemorySize() const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Render scene
  void render(ClCore& core) override;

 private:
  //! Initialize
  void initialize(const QSettings& settings, 
                  const ClCore& core,
                  ClScene& scene);


  UniquePointer<cl::Buffer> number_buffer_;
  UniquePointer<cl::Kernel> initializer_kernel_,
                            render_kernel_;
  cl::NDRange initializer_range_,
              render_range_;
};

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_PATH_TRACING_HPP_
