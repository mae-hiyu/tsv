/*!
  \file rgb_palette_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_PALETTE_WIDGET_HPP_
#define _REFLECT_RGB_PALETTE_WIDGET_HPP_

// Qt
#include <QColor>
// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_rgb_palette_widget.h"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

/*!
  \details
  No detailed.
  */
class RgbPaletteWidget : public ReflectWidget
{
 public:
  //! Create a rgb color palette widget
  RgbPaletteWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Set color to label
  void setColor(const QColor& color);


  QColor color_;
  Ui::RgbPaletteWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_RGB_PALETTE_WIDGET_HPP_
