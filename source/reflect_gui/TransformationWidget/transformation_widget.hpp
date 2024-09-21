/*!
  \file transformation_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_TRANSFORMATION_WIDGET_HPP_
#define _REFLECT_TRANSFORMATION_WIDGET_HPP_

// ReflectGui
#include "reflect_multilayer.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_transformation_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class TransformationWidget : public ReflectMultilayer
{
 public:
  //! Create a transformation widget
  TransformationWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Enable or disable scaling
  void setScalingEnabled(const bool enabled);

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  Ui::TransformationWidget ui_;
};

//! Make a transformation item
ReflectLayer* makeTransformationItem(const QString& prefix, 
                                     const QSettings& settings);

} // namespace reflect

#endif // _REFLECT_TRANSFORMATION_WIDGET_HPP_
