/*!
  \file color_palette_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_PALETTE_WIDGET_HPP_
#define _REFLECT_COLOR_PALETTE_WIDGET_HPP_

// Standard C++ library
#include <vector>
#include <utility>
// Qt
#include <QString>
// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_color_palette_widget.h"

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
class ColorPaletteWidget : public ReflectWidget
{
 public:
  //! Create a color palette widget
  ColorPaletteWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Return the current widget index
  std::size_t getCurrentIndex(const QString& type) const;

  //! Initialize
  void initialize();

  //! Set current widget index
  void setCurrentIndex(const std::size_t index);


  ReflectWidget* current_palette_;
  std::vector<std::pair<QString, ReflectWidget*>> palette_list_;
  Ui::ColorPaletteWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_COLOR_PALETTE_WIDGET_HPP_
