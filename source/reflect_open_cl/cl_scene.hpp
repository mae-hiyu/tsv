/*!
  \file sl_scene.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SCENE_HPP_
#define _REFLECT_CL_SCENE_HPP_

// Standard C++ library
#include <cstddef>
#include <string>
#include <vector>
// Reflect 
#include "cl.hpp"
#include "Color/cl_spectra_image.hpp"
#include "Data/object.hpp"
#include "OpenCL/Color/cl_spectral_distribution.hpp"
#include "OpenCL/Data/cl_light_source_reference.hpp"
#include "OpenCL/Data/cl_object.hpp"
#include "OpenCL/DataStructure/cl_bvh_node.hpp"
#include "OpenCL/Material/cl_emitter_model.hpp"
#include "OpenCL/Material/cl_surface_scattering_model.hpp"
#include "OpenCL/Material/cl_weight.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

// Forward declaration
class Bvh;
class ClCore;
class EmitterModel;
class LightSourceReference;
class SurfaceScatteringModel;
class Weight;

/*!
  \details
  No detailed.
  */
class ClScene
{
 public:
  //! Make empty data
  ClScene();

  //! Move data
  ClScene(ClScene&& scene);


  //! Add build options
  void addBuildOptions(const std::string& options);

  //! Return the build options
  const std::string& buildOptions() const;

  //! Initialize buffers
  std::size_t initializeBuffer(const ClCore& core);

  //! Initialize BVH
  void setBvh(const Bvh& bvh, const std::vector<Object>& object_list);

  //! Initialize emitter list
  void setEmitter(const std::vector<const EmitterModel*>& emitter_list);

  //! Initialize light source list
  void setLightSource(
      const std::vector<LightSourceReference>& light_source_list,
      const std::vector<Object>& object_list);

  //! Initialize object list
  void setObject(
      const std::vector<Object>& object_list,
      const std::vector<const SurfaceScatteringModel*>& surface_scattering_list,
      const std::vector<const EmitterModel*>& emitter_list);

  //! Set image resolution
  void setResolution(const std::size_t width, const std::size_t height);

  //! Initialize surface scattering list
  void setSurfaceScattering(
      const std::vector<const SurfaceScatteringModel*>& surface_scattering_list,
      const std::vector<const Weight*>& weight_list);

  //! Initialize weight list
  void setWeight(const std::vector<const Weight*>& weight_list);

  //! Return the weight buffer
  const cl::Buffer& weightBuffer() const;

  //! Return the weight color index buffer
  const cl::Buffer& weightColorIndexBuffer() const;

  //! Return the weight float buffer
  const cl::Buffer& weightFloatBuffer() const;

  //! Return the weight spectra buffer
  const cl::Buffer& weightSpectraBuffer() const;

  //! Return the surface scattering buffer
  const cl::Buffer& surfaceScatteringBuffer() const;

  //! Return the dielectric surface buffer
  const cl::Buffer& surfaceSpectraBuffer() const;

  //! Return the emitter buffer
  const cl::Buffer& emitterBuffer() const;

  //! Return the object buffer
  const cl::Buffer& objectBuffer() const;

  //! Return the light source buffer
  const cl::Buffer& lightSourceBuffer() const;

  //! Return the BVH buffer
  const cl::Buffer& bvhBuffer() const;

  //! Return the image buffer
  ClSpectraImage& spectraImageBuffer();

 private:

  std::string build_options_;
  // Weight
  std::vector<ClWeight> weight_list_;
  std::vector<cl_uint> weight_color_index_array_;
  std::vector<cl_half> weight_float_array_;
  std::vector<ClSpectralDistribution> weight_spectra_array_;
  // Surface scattering
  std::vector<ClSurfaceScatteringModel> surface_scattering_list_;
  std::vector<ClSpectralDistribution> surface_spectra_array_;
  // Emitter model
  std::vector<ClEmitterModel> emitter_list_;
  // Object
  std::vector<ClObject> object_list_;
  std::vector<ClLightSourceReference> light_source_list_;
  // BVH
  std::vector<ClBvhNode> bvh_;
  // Weight buffer
  UniquePointer<cl::Buffer> weight_buffer_;
  UniquePointer<cl::Buffer> weight_color_index_buffer_;
  UniquePointer<cl::Buffer> weight_float_buffer_;
  UniquePointer<cl::Buffer> weight_spectra_buffer_;
  // Surface scattering buffer
  UniquePointer<cl::Buffer> surface_scattering_buffer_;
  UniquePointer<cl::Buffer> surface_spectra_buffer_;
  // Emitter buffer
  UniquePointer<cl::Buffer> emitter_buffer_;
  // Object buffer
  UniquePointer<cl::Buffer> object_buffer_;
  UniquePointer<cl::Buffer> light_source_buffer_;
  // BVH buffer
  UniquePointer<cl::Buffer> bvh_buffer_;
  // Image buffer
  UniquePointer<ClSpectraImage> image_;
  std::size_t width_,
              height_;
};

} // namespace reflect

#endif // _REFLECT_CL_SCENE_HPP_
