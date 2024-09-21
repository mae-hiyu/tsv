/*!
  \file surface_model-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SURFACE_MODEL_INL_HPP_
#define _REFLECT_SURFACE_MODEL_INL_HPP_

#include "surface_model.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "multilayer_thin_film_surface.hpp"
#include "rough_conductor_surface.hpp"
#include "rough_dielectric_surface.hpp"
#include "smooth_conductor_surface.hpp"
#include "smooth_dielectric_surface.hpp"
#include "smooth_diffuse_surface.hpp"
#include "Material/shader_model.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

// Forward declaration
class IntersectionInfo;
class Sampler;
template <std::size_t> class WavelengthSamples;

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SurfaceModel::makeBxdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  ShaderPointer<kSampleSize> shader;

  const auto surface_type = type();
  switch (surface_type) {
   case SurfaceType::SmoothDiffuse:
    shader = makeLambertBrdf(this, vin, intersection, 
                             wavelengths, sampler, memory_pool);
    break;
   case SurfaceType::SmoothDielectric:
    shader = makeSpecularBsdf(this, vin, intersection,
                              wavelengths, sampler, memory_pool);
    break;
   case SurfaceType::SmoothConductor:
    shader = makeSpecularBrdf(this, vin, intersection,
                              wavelengths, sampler, memory_pool);
    break;
   case SurfaceType::MultilayerThinFilms:
    shader = makeThinFilmSpecularBrdf(this, vin, intersection,
                                      wavelengths, sampler, memory_pool);
    break;
   case SurfaceType::RoughDielectric:
    shader = makeGgxDielectricBsdf(this, vin, intersection,
                                  wavelengths, sampler, memory_pool);
    break;
   case SurfaceType::RoughConductor:
    shader = makeGgxConductorBrdf(this, vin, intersection,
                                  wavelengths, sampler, memory_pool);
    break;
   default:
    zisc::raiseError("SurfaceModelError: (type=", cast<int>(surface_type),
                     ") makeBxdf method is not implemented.");
    break;
  }

  return shader;
}

} // namespace reflect

#endif // _REFLECT_SURFACE_MODEL_INL_HPP_
