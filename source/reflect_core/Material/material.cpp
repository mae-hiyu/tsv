/*!
 \file material.cpp
 \author takemura
 */

#include "material.hpp"

namespace reflect {

// Forward declaration
class EmitterModel;
class SurfaceModel;

/*!
  \details
  No detailed.
  */
Material::Material(const SurfaceModel* surface, const EmitterModel* emitter) :
    surface_{surface},
    emitter_{emitter}
{
}

} // namespace reflect
