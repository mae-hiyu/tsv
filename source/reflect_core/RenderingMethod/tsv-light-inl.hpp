/*!
  \file    tsv_light.hpp
  \author maeda
*/

#pragma once

#include "path_tracing.hpp"
// Standard C++ library
#include <iostream>
#include <fstream>
#include <typeinfo>


#include <cstddef>
#include <cstdint>
#include <functional>
#include <future>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/algorithm.hpp"
#include "zisc/arithmetic_array.hpp"
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/thread_pool.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "scene.hpp"
#include "world.hpp"
#include "CameraModel/camera_model.hpp"
#include "Data/intersection_info.hpp"
#include "Data/light_source_reference.hpp"
#include "Data/ray.hpp"
#include "Data/wavelength_samples.hpp"
#include "DataStructure/bvh.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/material.hpp"
#include "Material/shader_model.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Material/SurfaceModel/surface_model.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Sampling/light_source_sampler.hpp"
#include "Sampling/russian_roulette.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Sampling/sampled_wavelengths.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
TSVLightPathTracing<kSampleSize>::TSVLightPathTracing(RendererSystem& system,
                                      const ColorSystem& color_system,
                                      const QSettings& settings, 
                                      Scene* scene) :
    RenderingMethod<kSampleSize>(system, color_system, settings, scene)
{
  initialize(settings);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
void TSVLightPathTracing<kSampleSize>::render(RendererSystem& system)
{
  traceCameraPath(system);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
void TSVLightPathTracing<kSampleSize>::evaluateExplicitConnection(
    const double mis_weight,
    const Ray& ray,
    const ShaderPointer& bxdf,
    const IntersectionInfo& intersection,
    const Spectra& ray_weight,
    Sampler& sampler,
    MemoryPool& memory_pool,
    Spectra* contribution) const
{
  if (mis_weight == 0.0)
    return;

  const auto& world = Method::sceneData().world();
  const auto& wavelengths = ray_weight.wavelengths();
  // Select light source and sample a point
  const auto& light_source_sampler = world.lightSourceSampler();
  const auto& sampled_light_source = light_source_sampler.sample(sampler);
  const auto light_source = sampled_light_source.object();
  const auto light_point = light_source->geometry().samplePoint(intersection, sampler);

  // Make next ray
  const auto ray_epsilon = Method::rayCastEpsilon() * intersection.normal();
  const auto ray_point = intersection.point() + ray_epsilon;
  const auto diff = light_point.first.point() - ray_point;
  const auto ray_direction = diff.normalized();
  REFLECT_CHECK_UNIT_VECTOR(ray_direction);
  REFLECT_CHECK_NON_ZERO_FLOAT(ray_direction);
  const double cos_theta_o = zisc::dot(intersection.normal(), ray_direction);
  if (cos_theta_o < 0.0)
    return;
  const Ray next_ray{ray_point, ray_direction};

  // Evaluate reflectance
  const auto f = bxdf->evaluateRadiance(&ray.direction(), 
                                        &ray_direction, 
                                        wavelengths);
  if (f.isZero())
    return;

  // Evaluate visibility
  const auto& bvh = world.bvh();
  const auto next_intersection = bvh.findClosestIntersection(next_ray);
  if (next_intersection.object() != light_source || next_intersection.isReverseFace())
    return;

  // Evaluate the light radiance
  const auto& emitter = light_source->material().emitter();
  const auto light = emitter.makeLight(next_intersection, wavelengths, 
                                       sampler, memory_pool);
  const auto radiance = light->evaluateRadiance(&ray_direction, nullptr, wavelengths);

  // Calculate geometry factor
  const double square_distance = diff.squareNorm();
  REFLECT_CHECK_NON_ZERO_FLOAT(square_distance);
//  const double cos_theta_o = zisc::dot(intersection.normal(), ray_direction);
  const double cos_theta_i = -zisc::dot(next_intersection.normal(), ray_direction);
  const double geometry_term = cos_theta_i * cos_theta_o / square_distance;
//  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_o);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_i);
  REFLECT_CHECK_POSITIVE_FLOAT(geometry_term);

  // Calculate the contribution
  const double inverse_probability = light_point.first.inversePdf() * 
                                     sampled_light_source.inverseWeight();
  const auto c = ray_weight * f * radiance * (geometry_term * inverse_probability);
  REFLECT_CHECK_POSITIVE_FLOAT(c);
  *contribution += c; 
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void TSVLightPathTracing<kSampleSize>::evaluateImplicitConnection(
    const double mis_weight,
    const Ray& ray,
    const Material& material,
    const IntersectionInfo& intersection,
    const Spectra& ray_weight,
    Sampler& sampler,
    MemoryPool& memory_pool,
    Spectra* contribution) const
{
  if (mis_weight == 0.0)
    return;

  if (material.isLightSource() && !intersection.isReverseFace()) {
    const auto& vin = ray.direction();
    const auto& wavelengths = ray_weight.wavelengths();

    // Get a light
    const auto& emitter = material.emitter();
    const auto light = emitter.makeLight(intersection, wavelengths, 
                                         sampler, memory_pool);

    // Evaluate the radiance
    const auto radiance = light->evaluateRadiance(&vin, nullptr, wavelengths);
    const auto c = radiance * ray_weight;
    REFLECT_CHECK_POSITIVE_FLOAT(c);
    *contribution += c;
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
Ray TSVLightPathTracing<kSampleSize>::generateRay(const std::size_t x, 
                                          const std::size_t y,
                                          Sampler& sampler,
                                          MemoryPool& memory_pool,
                                          Spectra* ray_weight) const
{
  const auto& camera = Method::sceneData().camera();
  const auto& wavelengths = ray_weight->wavelengths();
  const auto& lens_point = camera.sampledLensPoint();

  const auto sensor = camera.makeSensor(x, y, wavelengths, sampler, memory_pool);
  const auto vout = sensor->sampleDirection(sampler);

  *ray_weight = sensor->evaluateWeight(nullptr, &vout, wavelengths);
  return Ray{lens_point, vout.direction()};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void TSVLightPathTracing<kSampleSize>::initialize(const QSettings& /* settings */)
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
Ray TSVLightPathTracing<kSampleSize>::sampleNextRay(const std::size_t path_length,
                                            const Ray& ray,
                                            const ShaderPointer& bxdf,
                                            const IntersectionInfo& intersection,
                                            Sampler& sampler,
                                            Spectra* ray_weight,
                                            Spectra* next_ray_weight,
                                            bool* wavelength_is_selected) const
{
  // Sample next direction 
  const auto& vin = ray.direction();
  const auto vout = bxdf->sampleDirection(sampler);
  if (vout.inversePdf() == 0.0)
    return Ray{};

  // Evaluate BxDF weight
  const auto& wavelengths = ray_weight->wavelengths();
  const auto weight = bxdf->evaluateWeight(&vin, &vout, wavelengths);
  REFLECT_CHECK_POSITIVE_FLOAT(weight);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(weight);

  // Play russian roulette
  const auto roulette_result = this->playRussianRoulette(path_length, weight, sampler);
  if (!roulette_result.result())
    return Ray{};

  // Update ray weight
  if (!(*wavelength_is_selected) && bxdf->wavelengthIsSelected()) {
    *ray_weight = *ray_weight * wavelengths.primaryInverseProbability();
    *wavelength_is_selected = true;
  }
  const double inverse_probability = 1.0 / roulette_result.probability();
  *next_ray_weight = *ray_weight * weight * inverse_probability;

  // Update ray
  const double cos_theta = zisc::dot(intersection.normal(), vout.direction());
  const auto ray_epsilon = (cos_theta > 0.0)
      ? Method::rayCastEpsilon() * intersection.normal()
      : -Method::rayCastEpsilon() * intersection.normal();

  return Ray{intersection.point() + ray_epsilon, vout.direction()};
}

/*!
フォトン1つ1つに波長を割り当てる
  */
template <std::size_t kSampleSize> inline
void TSVLightPathTracing<kSampleSize>::traceCameraPath(RendererSystem& system)
{
  auto& sampler = system.globalSampler();
  // Set wavelengths
  // const auto sampled_wavelengths = Method::sampleWavelengths(sampler);
  auto& scene = Method::sceneData();
  auto& world = scene.world();

  // Set wavelenths X, Y, Z
  const auto sampled_wavelengthsX = makeTSVXStratifiedSampler<kXYZSampleSize>()(sampler);
  const auto sampled_wavelengthsY = makeTSVYStratifiedSampler<kXYZSampleSize>()(sampler);
  const auto sampled_wavelengthsZ = makeTSVZStratifiedSampler<kXYZSampleSize>()(sampler);
  const auto sampled_wavelengthsLight = makeLightsBasedStratifiedSampler<kLightSampleSize>(world)(sampler);

  const std::tuple<SamplesXYZ, SamplesXYZ, SamplesXYZ, SamplesLight> sampled_wavelengthsXYZLight
    (sampled_wavelengthsX, sampled_wavelengthsY, sampled_wavelengthsZ, sampled_wavelengthsLight);

  // Set camera
  auto& camera = Method::sceneData().camera();
  camera.sampleLensPoint(sampler);
  camera.jitter(sampler);

  std::function<void (const int, const std::size_t)>  trace_camera_path{
  [this, &system, &sampled_wavelengthsXYZLight](const int thread_id, const std::size_t y)
  {
    traceCameraPath(system, thread_id, y, sampled_wavelengthsXYZLight);
  }};

  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  const std::size_t end = camera.heightResolution();
  auto result = thread_pool.loop(std::move(trace_camera_path), start, end);
  result.get();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
void TSVLightPathTracing<kSampleSize>::traceCameraPath(RendererSystem& system,
                                               const int thread_id,
                                               const std::size_t y,
                                               const std::tuple<SamplesXYZ, SamplesXYZ, SamplesXYZ, SamplesLight>& sampled_wavelengthsXYZLight)
{
  auto& scene = Method::sceneData();
  const auto& world = scene.world();




  WavelengthSamples<kSampleSize> wavelengths;

  for (std::size_t i = 0; i < kXYZSampleSize; ++i)
  {
    wavelengths.setXYZwavelength(std::get<0>(sampled_wavelengthsXYZLight).wavelengths()[i], i);
    wavelengths.setXYZwavelength(std::get<1>(sampled_wavelengthsXYZLight).wavelengths()[i], i+kXYZSampleSize);
    wavelengths.setXYZwavelength(std::get<2>(sampled_wavelengthsXYZLight).wavelengths()[i], i+kXYZSampleSize*2);
  }
for (std::size_t i = 0; i < kLightSampleSize; ++i) {
    wavelengths.setXYZwavelength(std::get<3>(sampled_wavelengthsXYZLight).wavelengths()[i], i + kXYZSampleSize * 3);
}

  const auto wavelength_weight = makeSampledSpectraXYZLight<kSampleSize>(sampled_wavelengthsXYZLight);

  auto& sampler = system.threadSampler(thread_id);
  auto& memory_pool = system.threadMemoryPool(thread_id);

  for (std::size_t x = 0; x < scene.camera().widthResolution(); ++x) {
    IntersectionInfo intersection;
    Spectra contribution{wavelengths};
    ShaderPointer bxdf;
    std::size_t path_length = 0;
    double implicit_mis_weight = 1.0,
           explicit_mis_weight = 0.0;
    bool wavelength_is_selected = false;

    // Generate a camera ray
    Spectra next_ray_weight{wavelengths};
    auto next_ray = generateRay(x, y, sampler, memory_pool, &next_ray_weight);
    next_ray_weight = next_ray_weight * wavelength_weight;

    auto ray = next_ray;
    auto ray_weight = next_ray_weight;

    while (true) {
      ++path_length;

      evaluateExplicitConnection(explicit_mis_weight, ray, bxdf, intersection, 
                                 ray_weight, sampler, memory_pool, &contribution);

      if (!next_ray.isAlive())
        break;

      bxdf.reset();
      memory_pool.reset();

      ray = next_ray;
      ray_weight = next_ray_weight;

      // Ray object intersection test
      const auto& bvh = world.bvh();
      intersection = bvh.findClosestIntersection(ray);
      if (!intersection.isIntersected())
        break;

      // Evaluate material
      const auto& material = intersection.object()->material();

      evaluateImplicitConnection(implicit_mis_weight, ray, material, intersection, 
                                 ray_weight, sampler, memory_pool, &contribution);

      // Evaluate surface
      const auto& vin = ray.direction();
      const auto& surface = material.surface();
      bxdf = surface.makeBxdf(&vin, intersection, wavelengths, sampler, memory_pool);

      next_ray = sampleNextRay(path_length, ray, bxdf, intersection, sampler, 
                               &ray_weight, &next_ray_weight, &wavelength_is_selected);

      // Update variables
      const bool implicit_flag = material.isLightSource() || 
                                 (bxdf->type() == ShaderType::Specular);
      implicit_mis_weight = implicit_flag ? 1.0 : 0.0;
      explicit_mis_weight = implicit_flag ? 0.0 : 1.0;
    }
    scene.camera().addContribution(x, y, contribution);
  }
}

} // namespace reflect