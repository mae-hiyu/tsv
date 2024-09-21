/*!
  \file emitter_model.cpp
  \author takemura
  */

#include "emitter_model.hpp"
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "non_directional_emitter.hpp"
#include "Color/spectral_distribution.hpp"
#include "RendererBase/color_system.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
EmitterModel::EmitterModel(const ColorSystem& color_system,
                           const QSettings& settings, 
                           const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
void EmitterModel::scale(const double scale)
{
  power_distribution_ *= scale;
}

/*!
  \details
  No detailed.
  */
void EmitterModel::initialize(const ColorSystem& color_system,
                              const QSettings& settings, 
                              const QString& prefix)
{
  auto key = prefix + "/" + keyword::radiant_emittance;
  radiant_emittance_ = value<double>(settings, key);

  key = prefix + "/" + keyword::property;
  power_distribution_ = makeEmissiveDistribution(color_system, settings, key);
  scale(radiant_emittance_);
}

/*!
  \details
  No detailed.
  */
UniquePointer<EmitterModel> makeEmitter(const ColorSystem& color_system,
                                        const QSettings& settings,
                                        const QString& prefix)
{
  EmitterModel* emitter = nullptr;

  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::non_directional_emitter):
    emitter = new NonDirectionalEmitter{color_system, settings, prefix};
    break;
   default:
    zisc::raiseError("EmitterError: Unsupported type is specified.");
    break;
  }

  return UniquePointer<EmitterModel>{emitter};
}

} // namespace reflect
