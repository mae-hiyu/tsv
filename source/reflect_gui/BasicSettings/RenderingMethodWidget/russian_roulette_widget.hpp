/*!
  \file russian_roulette_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_RUSSIAN_ROULETTE_WIDGET_HPP_
#define _REFLECT_RUSSIAN_ROULETTE_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_russian_roulette_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class RussianRouletteWidget : public ReflectWidget
{
 public:
  //! Create russian roulette widget
  RussianRouletteWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

 private:
  //! Initialize
  void initialize();


  Ui::RussianRouletteWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_RUSSIAN_ROULETTE_WIDGET_HPP_
