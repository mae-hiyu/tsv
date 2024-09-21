/*!
 \file scene.cpp
 \author takemura
 */

#include "scene.hpp"
// Standard C++ library
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "world.hpp"
#include "CameraModel/camera_model.hpp"
#include "CameraModel/film.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_manager.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
Scene::Scene(RendererSystem& system,
             const ColorSystem& color_system,
             const QSettings& settings, 
             const RendererManager& manager)
{
  initialize(system, color_system, settings, manager);
}

/*!
  \details
  No detailed.
  */
void Scene::initialize(RendererSystem& system,
                       const ColorSystem& color_system,
                       const QSettings& settings, 
                       const RendererManager& manager)
{
  auto& thread_pool = system.threadPool();

  // Initialize a camera
  std::function<void ()> initialize_camera{[this, &settings, &color_system]()
  {
    const auto item_id = (QString{keyword::object} + "/" + keyword::item).arg(0);
    film_ = new Film{color_system, settings, item_id};
    camera_ = makeCameraModel(color_system, settings, item_id);
    camera_->setFilm(film_.get());

    const auto transformation = makeTransformationMatrix(settings, item_id);
    camera_->transform(transformation);
  }};
  auto camera_result = thread_pool.enqueue(std::move(initialize_camera));

  world_ = new World(system, color_system, settings, manager);
  
  camera_result.get();
}

} // namespace reflect
