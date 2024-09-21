/*!
  \file non_directional_emitter.cpp
  \author takemura
  */

#include "non_directional_emitter.hpp"
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "emitter_model.hpp"
#include "reflect_config.hpp"
#include "RendererBase/color_system.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
NonDirectionalEmitter::NonDirectionalEmitter(const ColorSystem& color_system,
                                             const QSettings& settings,
                                             const QString& prefix) :
    EmitterModel(color_system, settings, prefix)
{
}

/*!
  \details
  No detailed.
  */
EmitterType NonDirectionalEmitter::type() const
{
  return EmitterType::NonDirectional;
}

} // namespace reflect
