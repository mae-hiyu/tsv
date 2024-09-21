/*!
  \file material_widget.cpp
  \author takemura
  */

#include "material_widget.hpp"
// Qt
#include <QSettings>
#include <QString>

namespace reflect {

/*!
  \details
  No detailed.
  */
template <>
void SurfaceModelWidget::setDefaultConfiguration(const QString& group,
                                                 QSettings* settings)
{
  settings->beginGroup(group);

  QString key;

  key = keyword::name;
  settings->setValue(key, QStringLiteral("Default surface scattering"));

  key = keyword::type;
  settings->setValue(key, QString{keyword::smooth_diffuse_surface});

  key = QString{keyword::reflectance} + "/" + keyword::texture_index;
  settings->setValue(key, 0);

  settings->endGroup();
}

/*!
  \details
  No detailed.
  */
template <>
void EmitterModelWidget::setDefaultConfiguration(const QString& group,
                                                 QSettings* settings)
{
  settings->beginGroup(group);

  QString key;

  key = keyword::name;
  settings->setValue(key, QStringLiteral("Default emitter"));

  key = keyword::type;
  settings->setValue(key, QString{keyword::non_directional_emitter});

  key = QString{keyword::property} + "/" + keyword::type;
  settings->setValue(key, QString{keyword::spectra});

  key = QString{keyword::property} + "/" + keyword::spectra_file;
  settings->setValue(key, QStringLiteral(":/property/cie_si_d65.csv"));

  key = keyword::radiant_emittance;
  settings->setValue(key, 10.0);

  settings->endGroup();
}

/*!
  \details
  No detailed.
  */
template <>
void TextureWidget::setDefaultConfiguration(const QString& group,
                                            QSettings* settings)
{
  settings->beginGroup(group);

  QString key;

  key = keyword::name;
  settings->setValue(key, QStringLiteral("Default texture"));

  key = keyword::type;
  settings->setValue(key, QString{keyword::unicolor_texture});

  key = QString{keyword::color} + "/" + keyword::type;
  settings->setValue(key, QString{keyword::spectra});

  key = QString{keyword::color} + "/" + keyword::spectra_file;
  settings->setValue(key, QStringLiteral(":/property/default_reflectance.csv"));

  settings->endGroup();
}

} // namespace reflect
