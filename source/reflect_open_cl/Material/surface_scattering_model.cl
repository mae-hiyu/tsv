/*!
 \file surface_scattering_model.cl
 \author takemura
 */

#include "surface_scattering_model.h"

#include "reflect_config.h"
#include "sampled_direction.h"
#include "sampled_wavelengths.h"
#include "sampler.h"
#include "spectral_distribution.h"
#include "weight.h"

/*! Calculate Lambert reflection direction */
float3 calculateLambertReflectionDirection(const float3* normal,
                                           SamplerState* sampler);

/*! Evaluate Lambert BRDF weight */
IntensitySamples evaluateLambertBrdfRadiance(
    const SurfaceScatteringModel* surface,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths);

/*! Evaluate Lambert BRDF weight */
IntensitySamples evaluateLambertBrdfWeight(
    const SurfaceScatteringModel* surface,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths);

/*!
 \details
 No detailed.
 */
float3 calculateLambertReflectionDirection(const float3* normal,
                                           SamplerState* sampler)
{
  return sampleCosineWeightedDirection(normal, sampler);
}

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateBxdfRadiance(
    const SurfaceScatteringModel* surface_model,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths,
    const float3* vin,
    const float3* normal,
    const float3* vout)
{
  IntensitySamples radiance;
  switch (surface_model->type_) {
   case kSmoothDiffuse:
    radiance = evaluateLambertBrdfRadiance(surface_model,
                                           weight_list,
                                           weight_color_index_array,
                                           weight_spectra_array,
                                           wavelengths);
    break;
   default:
    break;
  }
  return radiance;
}

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateBxdfWeight(
    const SurfaceScatteringModel* surface_model,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths,
    const float3* vin,
    const float3* normal,
    float3* vout,
    SamplerState* sampler)
{
  IntensitySamples weight;
  switch (surface_model->type_) {
   case kSmoothDiffuse:
    *vout = calculateLambertReflectionDirection(normal, sampler);
    weight = evaluateLambertBrdfWeight(surface_model,
                                       weight_list,
                                       weight_color_index_array,
                                       weight_spectra_array,
                                       wavelengths);
    break;
   default:
    break;
  }
  return weight;
}

const constant float kLambertCoefficient = 1.0f / kPi;

/*! Evaluate Lambert BRDF weight */
IntensitySamples evaluateLambertBrdfRadiance(
    const SurfaceScatteringModel* surface,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths)
{
  const global Weight* weight = &weight_list[surface->parameter_[0]];
  return kLambertCoefficient *
         evaluateSpectraWeight(weight, 
                               weight_color_index_array, 
                               weight_spectra_array,
                               wavelengths);
}

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateLambertBrdfWeight(
    const SurfaceScatteringModel* surface,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths)
{
  const global Weight* weight = &weight_list[surface->parameter_[0]];
  return evaluateSpectraWeight(weight, 
                               weight_color_index_array, 
                               weight_spectra_array,
                               wavelengths);
}

/*!
 \details
 No detailed.
 */
uchar getSurfaceModelType(const uchar surface_type)
{
  switch (surface_type) {
   case kSmoothDiffuse:
    return kDiffuseSurfaceModel;
    break;
   default:
    break;
  }
  return 0;
}
