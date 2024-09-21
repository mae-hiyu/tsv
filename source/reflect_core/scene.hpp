/*!
 \file scene.hpp
 \author takemura
 */


#ifndef _REFLECT_SCENE_HPP_
#define _REFLECT_SCENE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class CameraModel;
class ColorSystem;
class Film;
class RendererManager;
class RendererSystem;
class World;

/*!
 \brief Rendering scene
 \details
 No detailed.
 */
class Scene
{
 public:
  //! Initialize
  Scene(RendererSystem& system,
        const ColorSystem& color_system,
        const QSettings& settings, 
        const RendererManager& manager);


  //! Return the camera
  CameraModel& camera();

  //! Return the camera
  const CameraModel& camera() const;

  //! Returh the film
  const Film& film() const;

  //! Return the world data
  const World& world() const;

 private:
  //! Initialize scene
  void initialize(RendererSystem& system,
                  const ColorSystem& color_system,
                  const QSettings& settings, 
                  const RendererManager& manager);


  UniquePointer<CameraModel> camera_;
  UniquePointer<Film> film_;
  UniquePointer<World> world_;
};

} // namespace reflect


#include "scene-inl.hpp"

#endif // _REFLECT_SCENE_HPP_

