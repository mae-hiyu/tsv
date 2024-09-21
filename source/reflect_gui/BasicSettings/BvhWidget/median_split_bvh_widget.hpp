/*!
  \file median_split_bvh_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_MEDIAN_SPLIT_BVH_WIDGET_HPP_
#define _REFLECT_MEDIAN_SPLIT_BVH_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_median_split_bvh_widget.h"

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
class MedianSplitBvhWidget : public ReflectWidget
{
 public:
  //! Create a median split bvh widget
  MedianSplitBvhWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* bvh_optimization_widget_;
  Ui::MedianSplitBvhWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_MEDIAN_SPLIT_BVH_WIDGET_HPP_
