/*!
  \file light_source_reference.cpp
  \author takemura
  */

#include "light_source_reference.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "object.hpp"
#include "Geometry/geometry.hpp"
#include "Material/material.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Utility/size.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
LightSourceReference::LightSourceReference(const double total_flux,
                                           const Object* light_source) :
    light_source_{light_source}
{
  initialize(total_flux);
}

/*!
  \details
  No detailed.
  */
void LightSourceReference::initialize(const double total_flux)
{
  const double flux = light_source_->geometry().surfaceArea() *
                      light_source_->material().emitter().radiantEmittance();
  weight_ = flux / total_flux;
  inverse_weight_ = 1.0 / weight_;
}

/*!
  \details
  No detailed.
  */
std::size_t LightSourceReference::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(weight_);
  size += PRINT_VARIABLE_DATA(inverse_weight_);
  size += PRINT_VARIABLE_DATA(light_source_);
  return size;
}

} // namespace reflect
