/*!
 \file material.hpp
 \author takemura
 */

#ifndef _REFLECT_MATERIAL_HPP_
#define _REFLECT_MATERIAL_HPP_

namespace reflect {

// Forward declaration
class EmitterModel;
class SurfaceModel;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class Material
{
 public:
  //! Create a material
  Material(const SurfaceModel* surface, const EmitterModel* emitter);


  //! Return the emitter model
  const EmitterModel& emitter() const;

  //! Return the surface scattering model
  const SurfaceModel& surface() const;

  //! Check if this material is light source
  bool isLightSource() const;

 private:
  const SurfaceModel* surface_;
  const EmitterModel* emitter_;
};

//! \} Material

} // namespace reflect

#include "material-inl.hpp"

#endif // _REFLECT_MATERIAL_HPP_
