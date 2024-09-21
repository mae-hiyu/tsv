/*!
  \file cl_scene.cpp
  \author takemura
  */

#include "cl_scene.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
// Reflect
#include "cl.hpp"
#include "cl_core.hpp"
#include "reflect_config.hpp"
#include "Color/cl_spectra_image.hpp"
#include "Color/cl_spectral_distribution.hpp"
#include "Data/object.hpp"
#include "Data/light_source_reference.hpp"
#include "DataStructure/bvh.hpp"
#include "Material/weight.hpp"
#include "Material/Emitter/emitter_model.hpp"
#include "Material/SurfaceScattering/surface_scattering_model.hpp"
#include "OpenCL/Data/cl_light_source_reference.hpp"
#include "OpenCL/Data/cl_object.hpp"
#include "OpenCL/DataStructure/cl_bvh_node.hpp"
#include "OpenCL/Material/cl_emitter_model.hpp"
#include "OpenCL/Material/cl_surface_scattering_model.hpp"
#include "OpenCL/Material/cl_weight.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClScene::ClScene()
{
}

/*!
  \details
  No detailed.
  */
ClScene::ClScene(ClScene&& scene) :
    build_options_{std::move(scene.build_options_)},
    // Weight
    weight_list_{std::move(scene.weight_list_)},
    weight_color_index_array_{std::move(scene.weight_color_index_array_)},
    weight_float_array_{std::move(scene.weight_float_array_)},
    weight_spectra_array_{std::move(scene.weight_spectra_array_)},
    // Surface scattering model
    surface_scattering_list_{std::move(scene.surface_scattering_list_)},
    surface_spectra_array_{std::move(scene.surface_spectra_array_)},
    // Emitter model
    emitter_list_{std::move(scene.emitter_list_)},
    // OBject
    object_list_{std::move(scene.object_list_)},
    light_source_list_{std::move(scene.light_source_list_)},
    // BVH
    bvh_{std::move(scene.bvh_)},
    // Weight buffer
    weight_buffer_{std::move(scene.weight_buffer_)},
    weight_color_index_buffer_{std::move(scene.weight_color_index_buffer_)},
    weight_float_buffer_{std::move(scene.weight_float_buffer_)},
    weight_spectra_buffer_{std::move(scene.weight_spectra_buffer_)},
    // Surface scattering buffer
    surface_scattering_buffer_{std::move(scene.surface_scattering_buffer_)},
    surface_spectra_buffer_{std::move(scene.surface_spectra_buffer_)},
    // Emitter buffer
    emitter_buffer_{std::move(scene.emitter_buffer_)},
    // Object buffer
    object_buffer_{std::move(scene.object_buffer_)},
    light_source_buffer_{std::move(scene.light_source_buffer_)},
    // BVH buffer
    bvh_buffer_{std::move(scene.bvh_buffer_)},
    // Image buffer
    image_{std::move(scene.image_)},
    width_{scene.width_},
    height_{scene.height_}
{
}

/*!
  \details
  No detailed.
  */
void ClScene::addBuildOptions(const std::string& options)
{
  build_options_ += options;
}

/*!
  \details
  No detailed.
  */
const std::string& ClScene::buildOptions() const
{
  return build_options_;
}

/*!
  \details
  No detailed.
  */
std::size_t ClScene::initializeBuffer(const ClCore& core)
{
  const auto& context = core.context();
  std::size_t memory_size = 0;
  std::size_t n = 0;
  std::string options;

  constexpr auto buffer_flag = CL_MEM_READ_ONLY | 
                               CL_MEM_HOST_NO_ACCESS | 
                               CL_MEM_COPY_HOST_PTR;

  // Weight buffer
  n = weight_list_.size();
  options += " -D REFLECT_WEIGHT_SIZE=" + std::to_string(n);
  const std::size_t weight_memory = sizeof(ClWeight) * n;
  weight_buffer_ = makeBuffer("WeightBuffer",
                              context,
                              buffer_flag,
                              weight_memory,
                              weight_list_.data());
  memory_size += weight_memory;

  n = weight_color_index_array_.size();
  options += " -D REFLECT_COLOR_INDEX_ARRAY_SIZE=" + std::to_string(n);
  const std::size_t weight_color_index_memory = sizeof(cl_uint) * n;
  weight_color_index_buffer_ = makeBuffer("WeightColorIndex",
                                          context,
                                          buffer_flag,
                                          weight_color_index_memory,
                                          weight_color_index_array_.data());
  memory_size += weight_color_index_memory;

  n = weight_float_array_.size();
  options += " -D REFLECT_WEIGHT_COLOR_ARRAY_SIZE=" + std::to_string(n);
  const std::size_t weight_float_memory = sizeof(cl_half) * n;
  weight_float_buffer_ = makeBuffer("WeightFloat",
                                    context,
                                    buffer_flag,
                                    weight_float_memory,
                                    weight_float_array_.data());
  memory_size += weight_float_memory;

  n = weight_spectra_array_.size();
  const std::size_t weight_spectra_memory = sizeof(ClSpectralDistribution) * n;
  weight_spectra_buffer_ = makeBuffer("WeightSpectra",
                                      context,
                                      buffer_flag,
                                      weight_spectra_memory,
                                      weight_spectra_array_.data());
  memory_size += weight_spectra_memory;

  // Surface scattering buffer
  n = surface_scattering_list_.size();
  options += " -D REFLECT_SURFACE_SCATTERING_SIZE=" + std::to_string(n);
  const std::size_t surface_scattering_memory = sizeof(ClSurfaceScatteringModel) * n;
  surface_scattering_buffer_ = makeBuffer("SurfaceScattering",
                                          context,
                                          buffer_flag,
                                          surface_scattering_memory,
                                          surface_scattering_list_.data());
  memory_size += surface_scattering_memory;

  n = surface_spectra_array_.size();
  options += " -D REFLECT_SURFACE_SPECTRA_ARRAY_SIZE=" + std::to_string(n);
  const std::size_t surface_spectra_memory = sizeof(ClSpectralDistribution) * n;
  surface_spectra_buffer_ = makeBuffer("SurfaceSpectra",
                                       context,
                                       buffer_flag,
                                       surface_scattering_memory,
                                       surface_scattering_list_.data());
  memory_size += surface_spectra_memory;

  // Emitter buffer
  n = emitter_list_.size();
  options += " -D REFLECT_EMITTER_SIZE=" + std::to_string(n);
  const std::size_t emitter_memory = sizeof(ClEmitterModel) * n;
  emitter_buffer_ = makeBuffer("Emitter",
                               context,
                               buffer_flag,
                               emitter_memory,
                               emitter_list_.data());
  memory_size += emitter_memory;

  // Object buffer
  n = object_list_.size();
  options += " -D REFLECT_OBJECT_SIZE=" + std::to_string(n);
  const std::size_t object_memory = sizeof(ClObject) * n;
  object_buffer_ = makeBuffer("Object",
                              context,
                              buffer_flag,
                              object_memory,
                              object_list_.data());
  memory_size += object_memory;

  n = light_source_list_.size();
  options += " -D REFLECT_LIGHT_SOURCE_SIZE=" + std::to_string(n);
  const std::size_t light_source_memory = sizeof(ClLightSourceReference) * n;
  light_source_buffer_ = makeBuffer("LightSource",
                                    context,
                                    buffer_flag,
                                    light_source_memory,
                                    light_source_list_.data());
  memory_size += light_source_memory;

  // BVH buffer
  n = bvh_.size();
  options += " -D REFLECT_BVH_NODE_SIZE=" + std::to_string(n);
  const std::size_t bvh_memory = sizeof(ClBvhNode) * n;
  bvh_buffer_ = makeBuffer("Bvh",
                           context,
                           buffer_flag,
                           bvh_memory,
                           bvh_.data());
  memory_size += bvh_memory;

  // Image buffer
  const std::size_t device_size = core.deviceList().size();
  options += " -D REFLECT_DEVICE_SIZE=" + std::to_string(device_size);
  image_ = new ClSpectraImage{core, width_, height_};
  memory_size += image_->memorySize();

  addBuildOptions(options);
  return memory_size;
}

/*!
  \details
  No detailed.
  */
void ClScene::setBvh(const Bvh& bvh, const std::vector<Object>& object_list)
{
  bvh_ = bvh.toClType(object_list);
}

/*!
  \details
  No detailed.
  */
void ClScene::setEmitter(const std::vector<const EmitterModel*>& emitter_list)
{
  emitter_list_.reserve(emitter_list.size());
  for (const auto* emitter_model : emitter_list)
    emitter_list_.emplace_back(emitter_model->toClType());
}

/*!
  \details
  No detailed.
  */
void ClScene::setLightSource(
    const std::vector<LightSourceReference>& light_source_list,
    const std::vector<Object>& object_list)
{
  light_source_list_.reserve(light_source_list.size());
  for (const auto& light_source_reference : light_source_list) {
    light_source_list_.emplace_back(
        light_source_reference.toClType(object_list));
  }
}

/*!
  \details
  No detailed.
  */
void ClScene::setObject(
    const std::vector<Object>& object_list,
    const std::vector<const SurfaceScatteringModel*>& surface_scattering_list,
    const std::vector<const EmitterModel*>& emitter_list)
{
  object_list_.reserve(object_list.size());
  for (const auto& object : object_list) {
    object_list_.emplace_back(object.toClType(surface_scattering_list,
                                              emitter_list));
  }
}

/*!
  \details
  No detailed.
  */
void ClScene::setResolution(const std::size_t width, const std::size_t height)
{
  width_ = width;
  height_ = height;
}

/*!
  \details
  No detailed.
  */
void ClScene::setSurfaceScattering(
    const std::vector<const SurfaceScatteringModel*>& surface_scattering_list,
    const std::vector<const Weight*>& weight_list)
{
  // Allocate surface spectra array memory
  std::size_t surface_spectra_array_size = 0;
  for (const auto* surface_scattering_model : surface_scattering_list)
    surface_spectra_array_size += surface_scattering_model->spectraArraySize();
  surface_spectra_array_.reserve(surface_spectra_array_size);

  // Make surface scattering list
  for (const auto* surface_scattering_model : surface_scattering_list) {
    auto cl_surface = surface_scattering_model->toClType(weight_list,
                                                         surface_spectra_array_);
    surface_scattering_list_.emplace_back(cl_surface);
  }
}

/*!
  \details
  No detailed.
  */
void ClScene::setWeight(const std::vector<const Weight*>& weight_list)
{
  // Allocate weight list memory
  weight_list_.reserve(weight_list.size());
  std::size_t color_index_array_size = 0;
  std::size_t color_array_size = 0;
  for (const auto* weight : weight_list) {
    color_index_array_size += weight->colorIndexArraySize();
    color_array_size += weight->colorArraySize();
  }
  weight_color_index_array_.reserve(color_index_array_size);
  weight_float_array_.reserve(color_array_size);
  weight_spectra_array_.reserve(color_array_size);

  // Make weight list
  for (const auto* weight : weight_list) {
    auto cl_weight = weight->toClType(weight_color_index_array_,
                                      weight_float_array_,
                                      weight_spectra_array_);
    weight_list_.emplace_back(std::move(cl_weight));
  }
}

/*!
  \details
  No detailed.
  */
const std::vector<cl::CommandQueue>& ClCore::queueList() const
{
  return queue_list_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::weightBuffer() const
{
  return *weight_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::weightColorIndexBuffer() const
{
  return *weight_color_index_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::weightFloatBuffer() const
{
  return *weight_float_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::weightSpectraBuffer() const
{
  return *weight_spectra_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::surfaceScatteringBuffer() const
{
  return *surface_scattering_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::surfaceSpectraBuffer() const
{
  return *surface_spectra_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::emitterBuffer() const
{
  return *emitter_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::objectBuffer() const
{
  return *object_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::lightSourceBuffer() const
{
  return *light_source_buffer_;
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClScene::bvhBuffer() const
{
  return *bvh_buffer_;
}

/*!
  \details
  No detailed.
  */
ClSpectraImage& ClScene::spectraImageBuffer()
{
  return *image_;
}

} // namespace reflect
