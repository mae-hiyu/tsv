/*!
 \file world.hpp
 \author takemura
 */

#ifndef _REFLECT_WORLD_HPP_
#define _REFLECT_WORLD_HPP_

// Standard C++ library
#include <cstddef>
#include <future>
#include <list>
#include <tuple>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "Data/light_source_reference.hpp"
#include "Data/object.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Material/SurfaceModel/surface_model.hpp"
#include "Material/Texture/texture.hpp"
#include "Sampling/light_source_sampler.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class Bvh;
class ColorSystem;
class RendererManager;
class RendererSystem;

/*!
 \brief Rendering world
 \details
 No detailed.
 */
class World
{
 public:
  //! Initialize
  World(RendererSystem& system,
        const ColorSystem& color_system,
        const QSettings& settings, 
        const RendererManager& manager);


  //! Return the bvh
  const Bvh& bvh() const;

  //! Make emitter model list
  std::vector<const EmitterModel*> emitterList() const;

  //! Return the light source list
  const std::vector<LightSourceReference>& lightSourceList() const;

  //! Return the world light source sampler
  const LightSourceSampler& lightSourceSampler() const;

  //! Make surface list
  std::vector<const SurfaceModel*> surfaceList() const;

  //! Make texture list
  std::vector<const Texture*> textureList() const;

  //! Return the world object list
  const std::vector<Object>& objectList() const;

  //! Select a light source randomly
//  const LightSourceReference& selectLightSource(Sampler& sampler) const;

 private:
  //! Initialize world
  void initialize(RendererSystem& system,
                  const ColorSystem& color_system,
                  const QSettings& settings, 
                  const RendererManager& manager);

  //! Initialize emitter list
  void initializeEmitter(RendererSystem& system, 
                         const ColorSystem& color_system,
                         const QSettings& settings);

  //! Initialize Object
  void initializeObject(RendererSystem& system, const QSettings& settings);

  //! Initialize the world information of light sources
  void initializeWorldLightSource();

  //! Initialize surface scattering list
  void initializeSurface(RendererSystem& system,
                         const std::vector<const Texture*>& texture_list, 
                         const QSettings& settings);

  //! Initialize texture list
  void initializeTexture(RendererSystem& system, 
                         const ColorSystem& color_system,
                         const QSettings& settings);

  //! Make objects
  std::list<std::future<std::vector<Object>>> makeObjects(
      RendererSystem& system,
      const QSettings& settings, 
      const QString& prefix,
      const Matrix4x4& transformation);


  UniquePointer<Bvh> bvh_;
  UniquePointer<LightSourceSampler> light_source_sampler_;
  std::vector<UniquePointer<EmitterModel>> emitter_list_;
  std::vector<UniquePointer<SurfaceModel>> surface_list_;
  std::vector<UniquePointer<Texture>> texture_list_;
  std::vector<Object> object_list_;
  std::vector<LightSourceReference> light_source_list_;
};

} // namespace reflect

#include "world-inl.hpp"

#endif // _REFLECT_WORLD_HPP_
