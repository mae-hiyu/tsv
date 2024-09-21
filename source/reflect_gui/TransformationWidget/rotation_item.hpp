/*!
  \file rotation_item.hpp
  \author takemura
  */

#ifndef _REFLECT_ROTATION_ITEM_HPP_
#define _REFLECT_ROTATION_ITEM_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_layer.hpp"
// UI
#include "ui_rotation_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class RotationItem : public ReflectLayer
{
 public:
  //! Create a rotation item
  RotationItem();

 private:
  //! Initialize
  void initialize();

  //! Initialize layer frame
  void initializeLayerFrame(QWidget* frame) override;

  //! Read layer data from a setting file
  void readLayerData(const QString& prefix,
                     const QSettings& settings) override;


  QPointer<QWidget> item_widget_;
  Ui::RotationWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_ROTATION_ITEM_HPP_
