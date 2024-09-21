/*!
  \file      tsv-probabilistic_ppm.hpp
  \author    takemura
  #2016/01/11
  */

#pragma once

// Standard C++ library
#include <cstddef>
#include <functional>
#include <future>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "rendering_method.hpp"
#include "DataStructure/knn_photon_list.hpp"
#include "DataStructure/photon_map.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class ColorSystem;
class IntersectionInfo;
class Material;
class Object;
class Ray;
class RendererSystem;
class Scene;
template <std::size_t> class SampledSpectra;
template <std::size_t> class SampledWavelengths;
template <std::size_t> class ShaderModel;
template <typename> class UniquePointer;
template <std::size_t> class WavelengthSamples;

//! \addtogroup RenderingMethod
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize, bool kEnableGlossyMapping>
class TSVProbabilisticPpm : public RenderingMethod<kSampleSize>
{
 public:
  using Method = RenderingMethod<kSampleSize>;
  using Map = PhotonMap<kSampleSize>;
  using Photon = Ray;
  using Spectra = typename Method::Spectra;
  using Samples = typename Method::Samples;
  using SamplesXYZ = typename Method::SamplesXYZ;
  using Shader = ShaderModel<kSampleSize>;
  using ShaderPointer = UniquePointer<Shader>;
  using Wavelengths = WavelengthSamples<kSampleSize>;


  //! Creaet a TSVProbabilisticPPM instance
   TSVProbabilisticPpm(RendererSystem& system, 
                    const ColorSystem& color_system,
                    const QSettings& settings, 
                    Scene* scene);


   //! Render scene using probabilistic ppm method
   void render(RendererSystem& system) override;

 private:
  //! Estimate radiance
  Spectra estimateRadiance(const int thread_id,
                           const Vector3& vin,
                           const IntersectionInfo& intersection,
                           const ShaderPointer& bxdf,
                           const Wavelengths& wavelengths,
                           const bool wavelength_is_selected);

  //! Evaluate implicit connection
  void evaluateImplicitConnection(const Ray& ray,
                                  const Material& material,
                                  const IntersectionInfo& intersection,
                                  const Spectra& ray_weight,
                                  Sampler& sampler,
                                  MemoryPool& memory_pool,
                                  Spectra* contribution) const;

  //! Generate a photon
  Photon generatePhoton(const Object* light_source,
                        const double scale_factor,
                        Sampler& sampler,
                        MemoryPool& memory_pool,
                        Spectra* photon_energy) const;

  //! Generate a camera ray
  Ray generateRay(const std::size_t x,
                  const std::size_t y,
                  Sampler& sampler,
                  MemoryPool& memory_pool,
                  Spectra* ray_weight) const;

  //! Check if the materal has photon map
  bool hasPhotonMapMaterial(const ShaderPointer& bxdf) const;

  //! Initialize
  void initialize(RendererSystem& system, const QSettings& settings);

  //! Initialize filter kernel
  void initializeFilterKernel(const QSettings& settings, const QString& key);

  //! Sample next photon
  Photon sampleNextPhoton(const std::size_t path_length,
                          const Photon& photon,
                          const ShaderPointer& bxdf,
                          const IntersectionInfo& intersection,
                          Sampler& sampler,
                          Spectra* photon_energy,
                          bool* wavelength_is_selected) const;

  //! Sample next photon
  Ray sampleNextRay(const Ray& ray,
                    const ShaderPointer& bxdf,
                    const IntersectionInfo& intersection,
                    Sampler& sampler,
                    Spectra* photon_energy,
                    bool* wavelength_is_selected) const;

  //! Distribute photons to light sources
  void tracePhoton(RendererSystem& system, const Samples& sampled_wavelengthsXYZ);

  //! Parallelize photon tracing
  void tracePhoton(RendererSystem& system,
                   const std::size_t light_number,
                   const Samples& sampled_wavelengthsXYZ,
                   const Object* light_source,
                   const std::size_t num_of_photons);

  //! Trace photons of a light source
  void tracePhoton(RendererSystem& system,
                   const int thread_id,
                   const Samples& sampled_wavelengthsXYZ,
                   const Object* light_source,
                   const std::size_t num_of_photons,
                   const double scale_factor);

  //! Parallelize ray tracing
  void traceRay(RendererSystem& system, const Samples& sampled_wavelengthsXYZ);

  //! Trace ray
  void traceRay(RendererSystem& system, 
                const int thread_id,
                const std::size_t y,
                const Samples& sampled_wavelengthsXYZ);

  //! Update radius
  void updateRadius();


  static constexpr std::size_t kMaxReflectionCountPrediction = 15;

  
  Map photon_map_;
  std::function<double (const double)> kernel_;
  std::vector<typename Map::PhotonList> thread_photon_list_;
  std::vector<std::future<void>> trace_result_list_;
  std::size_t pass_;
  std::size_t num_of_photons_;
  double square_radius_;
  double inverse_radius_;
  double inverse_estimation_area_;
  double alpha_;
};

//! \} RenderingMethod

} // namespace reflect

#include "tsv-probabilistic_ppm-inl.hpp"
