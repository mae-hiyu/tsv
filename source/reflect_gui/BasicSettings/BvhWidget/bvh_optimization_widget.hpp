/*!
  \file bvh_optimization_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_BVH_OPTIMIZATION_WIDGET_HPP_
#define _REFLECT_BVH_OPTIMIZATION_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_bvh_optimization_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class BvhOptimizationWidget : public ReflectWidget
{
 public:
  //! Create a BVH optimization widget
  BvhOptimizationWidget(QWidget* parent);


 private:
  //! Initialize
  void initialize();


  ReflectWidget* current_widget_;
  Ui::BvhOptimizationWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_BVH_OPTIMIZATION_WIDGET_HPP_
