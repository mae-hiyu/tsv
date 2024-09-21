/*!
  \file scaling_item.hpp
  \author takemura
  */

#ifndef _REFLECT_SCALING_ITEM_HPP_
#define _REFLECT_SCALING_ITEM_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_layer.hpp"
// UI
#include "ui_scaling_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ScalingItem : public ReflectLayer
{
 public:
  //! Create a scaling item
  ScalingItem();

 private:
  //! Initialize
  void initialize();

  //! Initialize layer frame
  void initializeLayerFrame(QWidget* frame);

  //! Read layer data from a setting file
  void readLayerData(const QString& prefix,
                     const QSettings& settings) override;


  QPointer<QWidget> item_widget_;
  Ui::ScalingWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SCALING_ITEM_HPP_
