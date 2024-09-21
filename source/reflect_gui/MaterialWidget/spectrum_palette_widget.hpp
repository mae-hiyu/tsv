/*!
  \file spectrum_palette_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRUM_PALETTE_WIDGET_HPP_
#define _REFLECT_SPECTRUM_PALETTE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_spectrum_palette_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class SpectrumPaletteWidget : public ReflectWidget
{
 public:
  //! Create a spectrum palette widget
  SpectrumPaletteWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Set button text
  void setText(const QString& text);

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

 private:
  //! Initialize
  void initialize();


  Ui::SpectrumPaletteWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SPECTRUM_PALETTE_WIDGET_HPP_
