/*!
  \file approximate_agglomerative_clustering_bvh_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_HPP_
#define _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_approximate_agglomerative_clustering_bvh_widget.h"

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
class ApproximateAgglomerativeClusteringBvhWidget : public ReflectWidget
{
 public:
  //! Create a approximate agglomerative clustering bvh widget
  ApproximateAgglomerativeClusteringBvhWidget(QWidget* parent);


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
  Ui::ApproximateAgglomerativeClusteringBvhWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_HPP_
