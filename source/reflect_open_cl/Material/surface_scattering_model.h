/*!
 \file surface_scattering_model.h
 \author takemura
 */

#ifndef _REFLECT_SURFACE_SCATTERING_MODEL_H_
#define _REFLECT_SURFACE_SCATTERING_MODEL_H_

#include "sampled_wavelengths.h"
#include "sampler.h"
#include "spectral_distribution.h"
#include "weight.h"

/*!
 \details
 No detailed.
 */
typedef struct _SurfaceScatteringModel
{
  ushort parameter_[3];
  uchar type_;
} SurfaceScatteringModel;

/*! \brief Evaluate BxDF weight */
IntensitySamples evaluateBxdfRadiance(
    const SurfaceScatteringModel* surface,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths,
    const float3* vin,
    const float3* normal,
    const float3* vout);

/*! \brief Evaluate BxDF weight */
IntensitySamples evaluateBxdfWeight(
    const SurfaceScatteringModel* surface,
    const global SpectralDistribution* surface_spectra_array,
    const global Weight* weight_list,
    const global uint* weight_color_index_array,
    const global half* weight_float_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths,
    const float3* vin,
    const float3* normal,
    float3* vout,
    SamplerState* sampler);

/*! \brief Return the surface model type */
uchar getSurfaceModelType(const uchar surface_type);

#endif /* _REFLECT_SURFACE_SCATTERING_MODEL_H_ */
