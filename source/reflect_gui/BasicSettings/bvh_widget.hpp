/*!
  \file bvh_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_BVH_WIDGET_HPP_
#define _REFLECT_BVH_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_bvh_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class BvhWidget : public ReflectWidget
{
 public:
  //! Create bvh widget
  BvhWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Make a bvh widget
  ReflectWidget* makeBvhWidget(const QString& type);


  ReflectWidget* current_widget_;
  Ui::BvhWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_BVH_WIDGET_HPP_
