/*!
  \file scene-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SCENE_INL_HPP_
#define _REFLECT_SCENE_INL_HPP_

#include "scene.hpp"
// Standard C++ library
#include <vector>
// Reflect
#include "world.hpp"
#include "CameraModel/camera_model.hpp"
#include "CameraModel/film.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
CameraModel& Scene::camera()
{
  return *camera_;
}

/*!
  \details
  No detailed.
  */
inline
const CameraModel& Scene::camera() const
{
  return *camera_;
}

/*!
  \details
  No detailed.
  */
inline
const Film& Scene::film() const
{
  return *film_;
}

/*!
  \details
  No detailed.
  */
inline
const World& Scene::world() const
{
  return *world_;
}

} // namespace reflect

#endif // _REFLECT_SCENE_INL_HPP_
