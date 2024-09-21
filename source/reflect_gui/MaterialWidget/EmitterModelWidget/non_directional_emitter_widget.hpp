/*!
  \file non_directional_emitter_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_NON_DIRECTIONAL_EMITTER_WIDGET_HPP_
#define _REFLECT_NON_DIRECTIONAL_EMITTER_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_non_directional_emitter_widget.h"

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
class NonDirectionalEmitterWidget : public ReflectWidget
{
 public:
  //! Create non directional emitter widget
  NonDirectionalEmitterWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* color_palette_;
  Ui::NonDirectionalEmitterWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_NON_DIRECTIONAL_EMITTER_WIDGET_HPP_
