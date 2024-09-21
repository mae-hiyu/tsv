/*!
 \file world.cpp
 \author takemura
 */

#include "world.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <functional>
#include <future>
#include <list>
#include <memory>
#include <stack>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/stopwatch.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "Data/light_source_reference.hpp"
#include "Data/object.hpp"
#include "DataStructure/bvh.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "Material/material.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Material/SurfaceModel/surface_model.hpp"
#include "Material/Texture/texture.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_manager.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Sampling/light_source_sampler.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
World::World(RendererSystem& system,
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
std::vector<const EmitterModel*> World::emitterList() const
{
  std::vector<const EmitterModel*> emitter_list;
  emitter_list.reserve(emitter_list_.size());
  for (const auto& emitter_model : emitter_list_)
    emitter_list.emplace_back(emitter_model.get());
  return emitter_list;
}

/*!
  \details
  No detailed.
  */
std::vector<const SurfaceModel*> World::surfaceList() const
{
  std::vector<const SurfaceModel*> surface_list;
  surface_list.reserve(surface_list_.size());
  for (const auto& surface_model : surface_list_)
    surface_list.emplace_back(surface_model.get());
  return surface_list;
}

/*!
  \details
  No detailed.
  */
std::vector<const Texture*> World::textureList() const
{
  std::vector<const Texture*> texture_list;
  texture_list.reserve(texture_list_.size());
  for (const auto& texture : texture_list_)
    texture_list.emplace_back(texture.get());
  return texture_list;
}

/*!
 \details
 No detailed.
 */
//const LightSourceReference& World::selectLightSource(Sampler& sampler) const
//{
//  const double threshold = sampler.sample(0.0, 1.0);
//  double sum = 0.0;
//  for (const auto& light_source : light_source_list_) {
//    sum += light_source.weight();
//    if (threshold < sum)
//      return light_source;
//  }
//  zisc::raiseError("WorldError: Light source selection failed.");
//  return light_source_list_[0];
//}

/*!
  \details
  No detailed.
  */
void World::initialize(RendererSystem& system,
                       const ColorSystem& color_system,
                       const QSettings& settings, 
                       const RendererManager& manager)
{
  zisc::Stopwatch timer;
 
  // Initialize texture
  timer.start();
  initializeTexture(system, color_system, settings);
  auto time = timer.elapsedTime();
  auto message = QStringLiteral("Texture initialization time: %1 ms").arg(time);
  emit manager.outputText(message);

  const auto texture_list = textureList();

  // Initialize surface scattering
  timer.start();
  initializeSurface(system, texture_list, settings);
  time = timer.elapsedTime();
  message = QStringLiteral("SurfaceModel  initialization time: %1 ms").arg(time);
  emit manager.outputText(message);

  // Initialize emitter
  timer.start();
  initializeEmitter(system, color_system, settings);
  time = timer.elapsedTime();
  message = QStringLiteral("EmitterModel initialization time: %1 ms").arg(time);
  emit manager.outputText(message);

  // Initialize objects
  timer.start();
  initializeObject(system, settings);
  time = timer.elapsedTime();
  message = QStringLiteral("Object initialization time: %1 ms").arg(time);
  emit manager.outputText(message);
  message = QStringLiteral("Num of objects: %1").arg(object_list_.size());
  emit manager.outputText(message);

  // Initialize a BVH
  timer.start();
  bvh_ = makeBvh(settings);
  bvh_->construct(system, object_list_);
  time = timer.elapsedTime();
  message = QStringLiteral("BVH construction time: %1 ms").arg(time);
  emit manager.outputText(message);

  initializeWorldLightSource();
  light_source_sampler_ = new LightSourceSampler{light_source_list_};
}

/*!
  \details
  No detailed.
  */
void World::initializeEmitter(RendererSystem& system, 
                              const ColorSystem& color_system,
                              const QSettings& settings)
{
  const QString prefix{keyword::emitter_model};
  const auto count = value<std::size_t>(settings, prefix + "/" + keyword::count);
  emitter_list_.resize(count + 1);

  auto make_default_emitter = [this, &color_system, &settings, &prefix]()
  {
    const auto p = QString{keyword::default_setting} + "/" + prefix;
    emitter_list_[0] = makeEmitter(color_system, settings, p);
  };

  std::function<void (const std::size_t)> make_emitter{
  [this, &color_system, &settings, &prefix](const std::size_t index)
  {
    const auto item_id = (prefix + "/" + keyword::item).arg(index);
    emitter_list_[index + 1] = makeEmitter(color_system, settings, item_id);
  }};

  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  auto result = thread_pool.loop(std::move(make_emitter), start, count);
  make_default_emitter();
  result.get();
}

/*!
  \details
  No detailed.
  */
void World::initializeObject(RendererSystem& system, const QSettings& settings)
{
  const QString prefix{keyword::object};
  auto results = makeObjects(system, settings, prefix, Matrix4x4{1.0, 0.0, 0.0, 0.0,
                                                                 0.0, 1.0, 0.0, 0.0,
                                                                 0.0, 0.0, 1.0, 0.0,
                                                                 0.0, 0.0, 0.0, 1.0});

  std::list<std::vector<Object>> object_list;
  for (auto& result : results)
    object_list.emplace_back(result.get());

  std::size_t num_of_objects = 0;
  for (const auto& objects : object_list)
    num_of_objects += objects.size();

  object_list_.reserve(results.size());
  for (auto& objects : object_list) {
    for (auto& object : objects) {
      object_list_.emplace_back(std::move(object));
    }
  }
}

/*!
  \details
  No detailed.
  */
void World::initializeWorldLightSource()
{
  double total_world_flux = 0.0;
  std::list<const Object*> light_source_list;
  for (const auto& object : object_list_) {
    if (object.material().isLightSource()) {
      total_world_flux += object.geometry().surfaceArea() *
                          object.material().emitter().radiantEmittance();
      light_source_list.emplace_back(&object);
    }
  }

  light_source_list_.reserve(light_source_list.size());
  for (const auto* light_source : light_source_list)
    light_source_list_.emplace_back(total_world_flux, light_source);
}

/*!
  \details
  No detailed.
  */
void World::initializeSurface(RendererSystem& system,
                              const std::vector<const Texture*>& texture_list,
                              const QSettings& settings)
{
  const QString prefix{keyword::surface_model};
  const auto count = value<std::size_t>(settings, prefix + "/" + keyword::count);
  surface_list_.resize(count + 1);

  auto make_default_surface = [this, &settings, &texture_list, &prefix]()
  {
    const auto p = QString{keyword::default_setting} + "/" + prefix;
    surface_list_[0] = makeSurface(settings, p, texture_list);
  };

  std::function<void (const std::size_t)> make_surface{
  [this, &settings, &prefix, &texture_list](const std::size_t index)
  {
    const auto item_id = (prefix + "/" + keyword::item).arg(index);
    surface_list_[index + 1] = makeSurface(settings, item_id, texture_list);
  }};

  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  auto result = thread_pool.loop(std::move(make_surface), start, count);
  make_default_surface();
  result.get();
}

/*!
  \details
  No detailed.
  */
void World::initializeTexture(RendererSystem& system, 
                              const ColorSystem& color_system,
                              const QSettings& settings)
{
  const QString prefix{keyword::texture};
  const auto count = value<std::size_t>(settings, prefix + "/" + keyword::count);
  texture_list_.resize(count + 1);

  auto make_default_texture = [this, &color_system, &settings]()
  {
    const auto prefix = QString{keyword::default_setting} + "/" + keyword::texture;
    texture_list_[0] = makeTexture(color_system, settings, prefix);
  };

  std::function<void (const std::size_t)> make_texture{
  [this, &color_system, &settings, &prefix](const std::size_t index)
  {
    const auto item_id = (prefix + "/" + keyword::item).arg(index);
    texture_list_[index + 1] = makeTexture(color_system, settings, item_id);
  }};

  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  auto result = thread_pool.loop(std::move(make_texture), start, count);
  make_default_texture();
  result.get();
}

/*!
  \details
  No detailed.
  */
std::list<std::future<std::vector<Object>>> World::makeObjects(
    RendererSystem& system,
    const QSettings& settings, 
    const QString& prefix,
    const Matrix4x4& transformation)
{
  std::list<std::future<std::vector<Object>>> results;

  auto make_object = [this, &settings](const QString& prefix, 
                                       const Matrix4x4& transformation)
  {
    // Make geometries
    auto geometry_list = makeGeometry(settings, prefix);
    const auto matrix = transformation * makeTransformationMatrix(settings, prefix);
    for (auto& geometry : geometry_list)
      geometry->transform(matrix);

    // Make a material
    // Set BSDF
    const auto bsdf_index = value<int>(settings, 
                                       prefix + "/" + keyword::surface_index);
    const auto* bsdf = (0 <= bsdf_index && 
                        bsdf_index < cast<int>(surface_list_.size()))
        ? surface_list_[bsdf_index].get()
        : surface_list_[0].get();
    // Set Light
    EmitterModel* light = nullptr;
    const bool is_light_source = value<bool>(settings, 
                                             prefix + "/" + keyword::is_light_source);
    if (is_light_source) {
      const auto light_index = value<int>(settings, 
                                          prefix + "/" + keyword::emitter_index);
      light = (0 <= light_index && light_index < cast<int>(emitter_list_.size()))
          ? emitter_list_[light_index].get()
          : emitter_list_[0].get();
    }
    const Material material{bsdf, light};

    // Make objects
    std::vector<Object> object_list;
    object_list.reserve(geometry_list.size());
    for (auto& geometry : geometry_list)
      object_list.emplace_back(material, std::move(geometry));
    return object_list;
  };
  auto& thread_pool = system.threadPool();

  const auto count = value<int>(settings, prefix + "/" + keyword::count);
  for (int index = 0; index < count; ++index) {
    const auto item_id = (prefix + "/" + keyword::item).arg(index);
    const auto type = value<QString>(settings, item_id + "/" + keyword::type);
    const auto type_hash = zisc::toHash32(type.toStdString().c_str());
    if (type_hash == zisc::toHash32(keyword::camera_object))
      continue;
    if (!value<bool>(settings, item_id + "/" + keyword::visibility))
      continue;
    if (type_hash == zisc::toHash32(keyword::single_object)) {
      std::function<std::vector<Object> ()> _make_object{
          std::bind(make_object, item_id, transformation)};
      results.emplace_back(thread_pool.enqueue(std::move(_make_object)));
    }
    else if (type_hash == zisc::toHash32(keyword::group_object)) {
      const auto group_transformation = makeTransformationMatrix(settings, item_id);
      auto group_results = 
          makeObjects(system, settings, item_id, transformation * group_transformation);
      for (auto& result : group_results)
        results.emplace_back(std::move(result));
    }
    else {
      zisc::raiseError("ObjectError: Unsupported type is specified.");
    }
  }
  return results;
}

} // namespace reflect
