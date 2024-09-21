/*!
 \file path_tracing.cl
 \author takemura
 */

#include "bvh_node.h"
#include "camera.h"
#include "emitter_model.h"
#include "intersection_point.h"
#include "light_source_reference.h"
#include "object.h"
#include "ray.h"
#include "reflect_config.h"
#include "rendering_method.h"
#include "russian_roulette.h"
#include "sampled_spectra.h"
#include "sampled_wavelengths.h"
#include "sampler.h"
#include "spectral_distribution.h"
#include "surface_scattering_model.h"
#include "weight.h"

/*! Evaluate next event */
IntensitySamples estimateNextEvent(
    const SurfaceScatteringModel* surface_model,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const global EmitterModel* emitter_list,
    const global Object* object_list,
    const global LightSourceReference* light_source_list,
    const global BvhNode* bvh,
    const Ray* ray, 
    const IntersectionPoint* intersection, 
    const local SampledWavelengths* wavelengths,
    SamplerState* sampler);

/*!
 \details
 No detailed.
 */
kernel void initializePathTracing(global SamplerState* sampler_list,
                                  global SampledWavelengths* sampled_wavelengths,
                                  global uint* number)
{
  SamplerState sampler = sampler_list[0];
  *sampled_wavelengths = sampleWavelengths(&sampler);
  *number = 0;
  sampler_list[0] = sampler;
}

/*!
 \brief Render image uinsg PathTracing method
 \details
 The algorithm named "RegenerationPTsk" is used.
 Please see the paper 
 "Progressive Light Transport Simulation on the GPU Survey and Improvements.pdf" 
 for more details.
 */
kernel void render(const global Weight* weight_list,
                   const global uint* weight_color_index_array,
                   const global half* weight_float_array,
                   const global SpectralDistribution* weight_spectra_array,
                   const global SurfaceScatteringModel* surface_scattering_list,
                   const global SpectralDistribution* surface_spectra_array,
                   const global EmitterModel* emitter_list,
                   const global Object* object_list,
                   const global LightSourceReference* light_source_list,
                   const global BvhNode* bvh,
                   const global SampledWavelengths* sampled_wavelengths,
                   global SamplerState* sampler_list,
                   global SpectralDistribution* spectra_buffer,
                   global uint* number)
{
  local SampledWavelengths wavelengths;
  copySampledWavelengths(sampled_wavelengths, &wavelengths);

  const size_t sampler_index = get_global_id(0) + 1;
  SamplerState sampler = sampler_list[sampler_index];

  IntensitySamples contribution;
  Ray ray;
  size_t path = 0;
  uint pixel_index = 0;
  uint previous_object_index;
  uchar previous_surface_type;
  bool is_idle_thread = true;
  while (true) {
    if (is_idle_thread) {
      /* Generate ray */
      if (!getPixelIndex(number, &pixel_index))
        break;
      contribution = (IntensitySamples)0.0f;
      ray = generateRay(pixel_index, &sampler);
      ray.weight_ *= wavelengths.inverse_probabilities_;
      path = 0;
      previous_object_index = kNonObjectIndex;
      previous_surface_type = kSpecularSurfaceModel;
    }

    ++path;
      
    /* Find closest intersected object */
    const IntersectionPoint intersection = 
        findClosestIntersection(&ray, bvh, object_list, previous_object_index);
    is_idle_thread = intersection.object_index_ == kNonObjectIndex;

    if (!is_idle_thread) {
      /* A case of light source, evaluate the light radiance */
      const ushort emitter_index = intersection.emitter_index_;
      if (emitter_index != kNonEmitterIndex &&
          !intersection.is_reverse_face_ &&
          previous_surface_type == kSpecularSurfaceModel) {
        const global EmitterModel* emitter = &emitter_list[emitter_index];
        IntensitySamples radiance = evaluateEmitterRadiance(emitter,
                                                            &ray.direction_,
                                                            &intersection.normal_,
                                                            &wavelengths);
        contribution = fma(radiance, ray.weight_, contribution);
      }
    
      const ushort surface_index = intersection.surface_scattering_index_;
      const SurfaceScatteringModel surface = surface_scattering_list[surface_index];
      const uchar surface_type = getSurfaceModelType(surface.type_);
  
      /* Evaluate next event */
      if (emitter_index == kNonEmitterIndex && 
          surface_type != kSpecularSurfaceModel) {
        const IntensitySamples radiance = estimateNextEvent(&surface,
                                                            surface_spectra_array,
                                                            weight_list,
                                                            weight_color_index_array,
                                                            weight_float_array,
                                                            weight_spectra_array,
                                                            emitter_list,
                                                            object_list,
                                                            light_source_list,
                                                            bvh,
                                                            &ray, 
                                                            &intersection, 
                                                            &wavelengths,
                                                            &sampler);
        contribution = fma(radiance, ray.weight_, contribution);
      }
  
      /* Evaluate BxDF weight */
      float3 vout;
      IntensitySamples bxdf_weight = evaluateBxdfWeight(&surface,
                                                        surface_spectra_array,
                                                        weight_list,
                                                        weight_color_index_array,
                                                        weight_float_array,
                                                        weight_spectra_array,
                                                        &wavelengths,
                                                        &ray.direction_,
                                                        &intersection.normal_,
                                                        &vout,
                                                        &sampler);
  
      /* Evaluate russian roulette */
      const RouletteResult result = playRussianRoulette(path, &bxdf_weight, &sampler);
      is_idle_thread = !result.result_;

      /* Update variables */
      ray.weight_ *= bxdf_weight * (1.0f / result.probability_);
      ray.origin_ = intersection.point_;
      ray.direction_ = vout;
      previous_object_index = intersection.object_index_;
      previous_surface_type = surface_type;
    }

    if (is_idle_thread)
      addRadiance(pixel_index, &contribution, &wavelengths, spectra_buffer);
  }

  sampler_list[sampler_index] = sampler;
}

/*!
 \details
 No detailed.
 */
IntensitySamples estimateNextEvent(
    const SurfaceScatteringModel* surface_model,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const global EmitterModel* emitter_list,
    const global Object* object_list,
    const global LightSourceReference* light_source_list,
    const global BvhNode* bvh,
    const Ray* ray, 
    const IntersectionPoint* intersection, 
    const local SampledWavelengths* wavelengths,
    SamplerState* sampler)
{
  /* Select light source */
  float inverse_light_probability = 0.0f;
  const uint object_index = selectLightSource(light_source_list, 
                                              &inverse_light_probability,
                                              sampler);
  const Object light_source = object_list[object_index];

  /* Sample a point on the light source */
  float inverse_point_probability = 0.0f;
  const float3 point = sampleObjectPointImportance(&light_source, 
                                                   intersection, 
                                                   &inverse_point_probability,
                                                   sampler);

  /* Make next ray */
  const float3 diff = point - intersection->point_;
  const float3 next_direction = normalize(diff);
  const Ray next_ray = {ray->weight_, intersection->point_, next_direction};

  /* Evaluate visibility */
  const IntersectionPoint next_intersection =
      findClosestIntersection(&next_ray, 
                              bvh, 
                              object_list, 
                              intersection->object_index_);
  if (next_intersection.object_index_ != object_index ||
      next_intersection.is_reverse_face_)
    return (IntensitySamples)(0.0f);

  /* Evaluate the light radiance */
  const global EmitterModel* emitter = &emitter_list[light_source.emitter_index_];
  const IntensitySamples radiance = evaluateEmitterRadiance(
      emitter,
      &next_ray.direction_,
      &next_intersection.normal_,
      wavelengths);

  /* Evaluate the reflectance */
  const IntensitySamples f = evaluateBxdfRadiance(surface_model,
                                                  surface_spectra_array,
                                                  weight_list,
                                                  weight_color_index_array,
                                                  weight_float_array,
                                                  weight_spectra_array,
                                                  wavelengths,
                                                  &ray->direction_,
                                                  &intersection->normal_,
                                                  &next_ray.direction_);

  /* Calculate geometry factor */
  const float square_distance = dot(diff, diff);
  const float cos_theta_o = dot(intersection->normal_, next_direction);
  const float cos_theta_i = -dot(next_intersection.normal_, next_direction);
  const float geometry_factor = cos_theta_i * cos_theta_o / square_distance;

  /* Calculate the contribution */
  const float inverse_pdf = inverse_light_probability * inverse_point_probability;
  return radiance * f * (geometry_factor * inverse_pdf);
}
