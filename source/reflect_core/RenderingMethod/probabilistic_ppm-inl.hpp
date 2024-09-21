/*!
  \file probabilistic_ppm-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_PROBABILISTIC_PPM_INL_HPP_
#define _REFLECT_PROBABILISTIC_PPM_INL_HPP_

#include "probabilistic_ppm.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <future>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "rendering_method.hpp"
#include "scene.hpp"
#include "CameraModel/camera_model.hpp"
#include "Data/light_source_reference.hpp"
#include "Data/intersection_info.hpp"
#include "Data/ray.hpp"
#include "Data/wavelength_samples.hpp"
#include "DataStructure/bvh.hpp"
#include "DataStructure/photon_map.hpp"
#include "Material/material.hpp"
#include "Material/shader_model.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Material/SurfaceModel/surface_model.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Sampling/russian_roulette.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Sampling/sampled_wavelengths.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::ProbabilisticPpm(
    RendererSystem& system,
    const ColorSystem& color_system,
    const QSettings& settings, 
    Scene* scene) :
        RenderingMethod<kSampleSize>(system, color_system, settings, scene),
        photon_map_{system}
{
  initialize(system, settings);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::render(
    RendererSystem& system)
{
  photon_map_.clear();
  updateRadius();

  auto& sampler = system.globalSampler();
  // Sample wavelengths
  const auto sampled_wavelengths = Method::sampleWavelengths(sampler);

  // case for sample just once
  // static auto sampled_wavelengths = Method::sampleWavelengths(sampler);
  // sampled_wavelengths.template selectPrimaryWavelength<kSampleSize>(sampler);

  tracePhoton(system, sampled_wavelengths);
  traceRay(system, sampled_wavelengths);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
auto ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::estimateRadiance(
    const int thread_id,
    const Vector3& vin,
    const IntersectionInfo& intersection,
    const ShaderPointer& bxdf,
    const Wavelengths& wavelengths,
    const bool wavelength_is_selected) -> Spectra
{

  // Search photon cache
  auto& photon_list = thread_photon_list_[thread_id];
  photon_list.clear();
  photon_map_.search(intersection.point(), intersection.normal(),
                     square_radius_, photon_list);

  // Estimate radiance
  Spectra radiance{wavelengths};
  for (std::size_t i = 0; i < photon_list.size(); ++i) {
    const auto& photon_point = photon_list[i];
    // Evaluate reflectance
    const auto photon_cache = photon_point.second;
    const auto vout = -photon_cache->incidentDirection();
    const auto f = bxdf->evaluateRadiance(&vin, &vout, wavelengths);
    REFLECT_CHECK_POSITIVE_FLOAT(f);
    if (f.isZero())
      continue;

    // Calculate contribution
//    const double distance = zisc::sqrt(photon_point.first);
//    const auto k = kernel_(distance * inverse_radius_);
//    const auto contribution = k * f * photon_cache->energy();
    const auto contribution = f * photon_cache->energy();

    if (!wavelength_is_selected & photon_cache->wavelengthIsSelected())
      radiance += contribution * wavelengths.primaryInverseProbability();
    else
      radiance += contribution;
  }
  REFLECT_CHECK_POSITIVE_FLOAT(radiance);
  return radiance * inverse_estimation_area_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::evaluateImplicitConnection(
    const Ray& ray,
    const Material& material,
    const IntersectionInfo& intersection,
    const Spectra& ray_weight,
    Sampler& sampler,
    MemoryPool& memory_pool,
    Spectra* contribution) const
{
  if (material.isLightSource() && !intersection.isReverseFace()) {
    const auto& vin = ray.direction();
    const auto& wavelengths = ray_weight.wavelengths();

    const auto& emitter = material.emitter();
    const auto light = emitter.makeLight(intersection, wavelengths, 
                                         sampler, memory_pool);

    // Evaluate the radiance
    const auto radiance = light->evaluateRadiance(&vin, nullptr, wavelengths);
    const auto c = ray_weight * radiance;
    REFLECT_CHECK_POSITIVE_FLOAT(c);
    *contribution += c;
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
auto ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::generatePhoton(
    const Object* light_source,
    const double scale_factor,
    Sampler& sampler,
    MemoryPool& memory_pool,
    Spectra* photon_energy) const -> Photon
{
  const auto& wavelengths = photon_energy->wavelengths();

  // Generate a photon
  const auto& geometry = light_source->geometry();
  const auto light_point = geometry.samplePoint(sampler);
  const auto& point = light_point.first;
  const auto& normal = light_point.second;

  const auto& emitter = light_source->material().emitter();
  IntersectionInfo intersection{point.point(), normal, light_source, false};
  const auto light = emitter.makeLight(intersection, wavelengths, 
                                       sampler, memory_pool);
  auto vout = light->sampleDirection(sampler);

  *photon_energy = light->evaluateWeight(nullptr, &vout, wavelengths) *
                   (point.inversePdf() * scale_factor);

  const auto ray_epsilon = Method::rayCastEpsilon() * normal;
  return Photon{point.point() + ray_epsilon, vout.direction()};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
Ray ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::generateRay(
    const std::size_t x,
    const std::size_t y,
    Sampler& sampler,
    MemoryPool& memory_pool,
    Spectra* ray_weight) const
{
  const auto& wavelengths = ray_weight->wavelengths();
  const auto& camera = Method::sceneData().camera();

  const auto& lens_point = camera.sampledLensPoint();

  auto sensor = camera.makeSensor(x, y, wavelengths, sampler, memory_pool);
  const auto vout = sensor->sampleDirection(sampler);

  *ray_weight = sensor->evaluateWeight(nullptr, &vout, wavelengths);
  return Ray{lens_point, vout.direction()};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
bool ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::hasPhotonMapMaterial(
    const ShaderPointer& bxdf) const
{
  return bxdf->type() == ShaderType::Diffuse || 
         (kEnableGlossyMapping && bxdf->type() == ShaderType::Glossy);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::initialize(
    RendererSystem& system,
    const QSettings& settings)
{
  pass_ = 0;

  const QString prefix{keyword::rendering_method};

  auto key = prefix + "/" + keyword::num_of_photons;
  num_of_photons_ = value<std::size_t>(settings, key);

  key = prefix + "/" + keyword::alpha;
  alpha_ = value<double>(settings, key);

  key = prefix + "/" + keyword::initial_radius;
  const double initial_radius = value<double>(settings, key);
  square_radius_ = (initial_radius * initial_radius) / alpha_;

  auto& thread_pool = system.threadPool();
  thread_photon_list_.resize(thread_pool.numOfThreads());
  key = prefix + "/" + keyword::k;
  const std::size_t k = value<std::size_t>(settings, key);
  for (auto& photon_list : thread_photon_list_)
    photon_list.setK(k);

  key = prefix + "/" + keyword::filter_kernel;
  initializeFilterKernel(settings, key);

  photon_map_.reserve(system, num_of_photons_ * kMaxReflectionCountPrediction);

  const auto& world = Method::sceneData().world();
  const auto& light_source_list = world.lightSourceList();
  trace_result_list_.resize(light_source_list.size());
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::initializeFilterKernel(
    const QSettings& settings,
    const QString& key)
{
  const auto filter_type = value<QString>(settings, key);
  const auto type_hash = zisc::toHash32(filter_type.toStdString().c_str());
  if (type_hash == zisc::toHash32(keyword::no_kernel)) {
    kernel_ = [](const double /* t */)
    {
      return 1.0;
    };
  }
  else if (type_hash == zisc::toHash32(keyword::cone_kernel)) {
    constexpr double k = 1.1;
    const double normalizer = 1.0 / (k - 1.0 + (1.0 / (3.0 * k)));
    kernel_ = [k, normalizer](const double t)
    {
      return (k - t) * normalizer;
    };
  }
  else if (type_hash == zisc::toHash32(keyword::gauss_kernel)) {
    constexpr double a = 0.918;
    constexpr double b = 1.953;
    const double tmp = 1.0 / (1.0 - std::exp(-b));
    kernel_ = [a, b, tmp](const double t)
    {
      const double exponent = (-0.5 * b) * t * t;
      const double x = 1.0 - std::exp(exponent);
      return a * (1.0 - x * tmp);
    };
  }
  else if (type_hash == zisc::toHash32(keyword::perlin_kernel)) {
    kernel_ = [](const double t)
    {
      constexpr double normalizer = 
          1.0 / (100.0 / 7.0 - 37.5 + 345.0 / 9.0 - 18.0 + 36.0 / 11.0);
      constexpr double a = -6.0;
      constexpr double b = 15.0;
      constexpr double c = -10.0;
      const double t_2 = t * t;
      const double t_3 = t_2 * t;
      return (1.0 + t_3 * (a * t_2 + b * t + c)) * normalizer;
    };
  }
  else {
    zisc::raiseError("ProbabilisticPpmError: Unsupported kernel type is specified.");
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
auto ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::sampleNextPhoton(
    const std::size_t path_length,
    const Photon& photon,
    const ShaderPointer& bxdf,
    const IntersectionInfo& intersection,
    Sampler& sampler,
    Spectra* photon_energy,
    bool* wavelength_is_selected) const -> Photon
{
  // Sample next direction
  const auto& vin = photon.direction();
  const auto vout = bxdf->sampleDirection(sampler);
  if (vout.inversePdf() == 0.0)
    return Photon{};

  // Evaluate BxDF weight
  const auto& wavelengths = photon_energy->wavelengths();

  const auto weight = bxdf->evaluateWeight(&vin, &vout, wavelengths);

  // Play russian roulette
  const auto roulette_result = this->playRussianRoulette(path_length, weight, sampler);
  if (!roulette_result.result())
    return Photon{};

  const double inverse_probability = 1.0 / roulette_result.probability();
  *wavelength_is_selected = *wavelength_is_selected || bxdf->wavelengthIsSelected();

  const double cos_theta = zisc::dot(intersection.normal(), vout.direction());
  const auto ray_epsilon = (cos_theta > 0.0)
      ? Method::rayCastEpsilon() * intersection.normal()
      : -Method::rayCastEpsilon() * intersection.normal();

  *photon_energy = *photon_energy * weight * inverse_probability;
  return Photon{intersection.point() + ray_epsilon, vout.direction()};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
Ray ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::sampleNextRay(
    const Ray& ray,
    const ShaderPointer& bxdf,
    const IntersectionInfo& intersection,
    Sampler& sampler,
    Spectra* ray_weight,
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

  // Update ray weight
  if (!(*wavelength_is_selected) && bxdf->wavelengthIsSelected()) {
    *ray_weight = *ray_weight * wavelengths.primaryInverseProbability();
    *wavelength_is_selected = true;
  }
  *ray_weight *= weight;

  // Update ray
  const double cos_theta = zisc::dot(intersection.normal(), vout.direction());
  const auto ray_epsilon = (cos_theta > 0.0)
      ? Method::rayCastEpsilon() * intersection.normal()
      : -Method::rayCastEpsilon() * intersection.normal();

  return Ray{intersection.point() + ray_epsilon, vout.direction()};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::tracePhoton(
    RendererSystem& system,
    const Samples& sampled_wavelengths)
{
  // Distribute photons to light sources
  const auto& world = Method::sceneData().world();
  
  const auto& light_source_list = world.lightSourceList();
  for (std::size_t i = 0; i < light_source_list.size(); ++i) {
    const auto& light_source = light_source_list[i];
    const double photons = cast<double>(num_of_photons_) * light_source.weight();
    const std::size_t num_of_photons = cast<std::size_t>(photons);
    tracePhoton(system, i, sampled_wavelengths, light_source.object(),num_of_photons);
  }

  for (auto& result : trace_result_list_)
    result.get();

  photon_map_.construct(system);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::tracePhoton(
    RendererSystem& system,
    const std::size_t light_number,
    const Samples& sampled_wavelengths,
    const Object* light_source,
    const std::size_t num_of_photons)
{
  auto& thread_pool = system.threadPool();
  const std::size_t thread_photons = num_of_photons / thread_pool.numOfThreads();
  const std::size_t rest = num_of_photons % thread_pool.numOfThreads();
  const double scale_factor = 1.0 / cast<double>(num_of_photons - rest);

  std::function<void (const int, const std::size_t)> trace_photon{
  [this, &system, &sampled_wavelengths, light_source, thread_photons, scale_factor]
  (const int thread_id, const std::size_t)
  {
    tracePhoton(system, thread_id, sampled_wavelengths, 
                light_source, thread_photons, scale_factor);
  }};

  constexpr std::size_t start = 0;
  const std::size_t end = thread_pool.numOfThreads();
  trace_result_list_[light_number] = 
      thread_pool.loop(std::move(trace_photon), start, end);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::tracePhoton(
    RendererSystem& system,
    const int thread_id,
    const Samples& sampled_wavelengths,
    const Object* light_source,
    const std::size_t num_of_photons,
    const double scale_factor)
{
  const auto& wavelengths = sampled_wavelengths.wavelengths();

  auto& sampler = system.threadSampler(thread_id);
  auto& memory_pool = system.threadMemoryPool(thread_id);

  for (std::size_t number = 0; number < num_of_photons; ++number) {
    Spectra photon_energy{sampled_wavelengths.wavelengths()};
    auto photon = generatePhoton(light_source, scale_factor, 
                                 sampler, memory_pool, &photon_energy);

    std::size_t path_length = 0;
    bool wavelength_is_selected = false;

    while(true) {
      memory_pool.reset();
      ++path_length;
      const auto& scene = Method::sceneData();
      const auto& world = scene.world();

      // Phton object intersection test
      const auto& bvh = world.bvh();
      const auto intersection = bvh.findClosestIntersection(photon);
      if (!intersection.isIntersected())
        break;

      // Evaluate surface
      const auto& surface = intersection.object()->material().surface();
      const auto& vin = photon.direction();
      const auto bxdf = surface.makeBxdf(&vin, intersection, wavelengths, 
                                         sampler, memory_pool);

      if (hasPhotonMapMaterial(bxdf)) {
        photon_map_.store(thread_id, intersection.point(), photon.direction(), 
                          photon_energy, wavelength_is_selected);
      }

      photon = sampleNextPhoton(path_length, photon, bxdf, intersection,
                                sampler, &photon_energy, &wavelength_is_selected);
      if (!photon.isAlive())
        break;
    }
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::traceRay(
    RendererSystem& system,
    const Samples& sampled_wavelengths)
{
  auto& sampler = system.globalSampler();

  // Set camera
  auto& camera = Method::sceneData().camera();
  camera.sampleLensPoint(sampler);
  camera.jitter(sampler);

  std::function<void (const int, const std::size_t)> trace_path{
  [this, &system, &sampled_wavelengths](const int thread_id, const std::size_t y) 
  {
    traceRay(system, thread_id, y, sampled_wavelengths);
  }};

  const auto& scene = Method::sceneData();
  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  const std::size_t end = scene.camera().heightResolution();
  auto result = thread_pool.loop(std::move(trace_path), start, end);
  result.get();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> 
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::traceRay(
    RendererSystem& system,
    const int thread_id,
    const std::size_t y,
    const Samples& sampled_wavelengths)
{
  const auto& wavelengths = sampled_wavelengths.wavelengths();
  const auto wavelength_weight = makeSampledSpectra(sampled_wavelengths);

  auto& scene = Method::sceneData();
  const auto& world = scene.world();

  auto& sampler = system.threadSampler(thread_id);
  auto& memory_pool = system.threadMemoryPool(thread_id);

  for (std::size_t x = 0; x < scene.camera().widthResolution(); ++x) {
    Spectra contribution{wavelengths};
    bool wavelength_is_selected = false;

    // Generate a camera ray
    Spectra ray_weight{wavelengths};
    auto ray = generateRay(x, y, sampler, memory_pool, &ray_weight);
    ray_weight = ray_weight * wavelength_weight;

    while (true) {
      memory_pool.reset();

      // Ray object intersection test
      const auto& bvh = world.bvh();
      const auto intersection = bvh.findClosestIntersection(ray);
      if (!intersection.isIntersected())
        break;

      // Evaluate material
      const auto& material = intersection.object()->material();

      evaluateImplicitConnection(ray, material, intersection, ray_weight,
                                 sampler, memory_pool, &contribution);

      // Evaluate surface
      const auto& vin = ray.direction();
      const auto& surface = material.surface();
      const auto bxdf = surface.makeBxdf(&vin, intersection, wavelengths, 
                                         sampler, memory_pool);

      if (!hasPhotonMapMaterial(bxdf)) {
        ray = sampleNextRay(ray, bxdf, intersection, sampler,
                            &ray_weight, &wavelength_is_selected);
        if (!ray.isAlive())
          break;
      }
      else {
        // Evaluate explicit connection
        const auto radiance = estimateRadiance(thread_id, vin, intersection, bxdf, 
                                               wavelengths, wavelength_is_selected);
        contribution += ray_weight * radiance;
        break;
      }
    }
    scene.camera().addContribution(x, y, contribution);
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping> inline
void ProbabilisticPpm<kSampleSize, kEnableGlossyMapping>::updateRadius()
{
  ++pass_;
  const double scale_factor = (cast<double>(pass_ - 1) + alpha_) / 
                              cast<double>(pass_);
  square_radius_ = scale_factor * square_radius_;
  inverse_radius_ = zisc::invSqrt(square_radius_);
  inverse_estimation_area_ = (1.0 / zisc::kPi) / square_radius_;
}

} // namespace reflect

#endif // _REFLECT_PROBABILISTIC_PPM_INL_HPP_
