/*!
  \file probabilistic_ppm_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_PROBABILISTIC_PPM_HPP_
#define _REFLECT_PROBABILISTIC_PPM_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_probabilistic_ppm.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ProbabilisticPpmWidget : public ReflectWidget
{
 public:
  //! Create probabilistic ppm widget
  ProbabilisticPpmWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  Ui::ProbabilisticPpmWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_PROBABILISTIC_PPM_HPP_
