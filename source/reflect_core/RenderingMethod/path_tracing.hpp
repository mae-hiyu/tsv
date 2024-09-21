/*!
 \file path_tracing.hpp
 \author takemura
 */

#ifndef _REFLECT_PATH_TRACING_HPP_
#define _REFLECT_PATH_TRACING_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
// Reflect
#include "reflect_config.hpp"
#include "rendering_method.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class ColorSystem;
class IntersectionInfo;
class Material;
class Ray;
class RendererSystem;
class Sampler;
class Scene;
template <std::size_t> class ShaderModel;
template <typename> class UniquePointer;

//! \addtogroup RenderingMethod
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class PathTracing : public RenderingMethod<kSampleSize>
{
 public:
  using Method = RenderingMethod<kSampleSize>;
  using Spectra = typename Method::Spectra;
  using Samples = typename Method::Samples;
  using Shader = ShaderModel<kSampleSize>;
  using ShaderPointer = UniquePointer<Shader>;
    
  

  //! Create a PathTracing instance
  PathTracing(RendererSystem& system,
              const ColorSystem& color_system,
              const QSettings& settings, 
              Scene* scene);


  //! Render scene using path tracing method
  void render(RendererSystem& system) override;

 private:
  //! Evaluate the explicit connection
  void evaluateExplicitConnection(const double mis_weight,
                                  const Ray& ray,
                                  const ShaderPointer& bxdf,
                                  const IntersectionInfo& intersection_info,
                                  const Spectra& ray_weight,
                                  Sampler& sampler,
                                  MemoryPool& memory_pool,
                                  Spectra* contribution) const;

  //! Evaluate the implicit connection
  void evaluateImplicitConnection(const double mis_weight,
                                  const Ray& ray,
                                  const Material& material,
                                  const IntersectionInfo& intersection_info,
                                  const Spectra& ray_weight,
                                  Sampler& sampler,
                                  MemoryPool& memory_pool,
                                  Spectra* contribution) const;

  //! Generate a camera ray
  Ray generateRay(const std::size_t x,
                  const std::size_t y,
                  Sampler& sampler,
                  MemoryPool& memory_pool,
                  Spectra* ray_weight) const;

  //! Initialize
  void initialize(const QSettings& settings);

  //! Sample next ray
  Ray sampleNextRay(const std::size_t path_length,
                    const Ray& ray,
                    const ShaderPointer& bxdf,
                    const IntersectionInfo& intersection_info,
                    Sampler& sampler,
                    Spectra* ray_weight,
                    Spectra* next_ray_weight,
                    bool* wavelength_is_selected) const;

  //! Parallelize path tracing
  void traceCameraPath(RendererSystem& system);

  //! Trace path
  void traceCameraPath(RendererSystem& system,
                       const int thread_id,
                       const std::size_t y,
                       const Samples& sampled_wavelengths);
};

//! \} RenderingMethod

} // namespace reflect

#include "path_tracing-inl.hpp"

#endif // _REFLECT_PATH_TRACING_HPP_
