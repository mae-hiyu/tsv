/*!
  \file reflect_layer.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_LAYER_HPP_
#define _REFLECT_REFLECT_LAYER_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_widget_item.hpp"
// UI
#include "ui_layer_widget.h"

// Forward declaration
class QListWidget;
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ReflectLayer : public ReflectListItem
{
 public:
  //! Create a reflect layer
  ReflectLayer();

  //! Activate layer
  void activate() override;

  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Set layer list
  void setLayerList(QListWidget* layer_list);

  //! Set layer number
  void setNumber(const int number);

 private:
  //! Initialize
  void initialize();

  //! Initialize layer frame
  virtual void initializeLayerFrame(QWidget* frame) = 0;

  //! Initialize layer widget
  void initializeWidget();

  //! Read layer data from a setting file
  virtual void readLayerData(const QString& prefix, 
                             const QSettings& settings) = 0;


  QPointer<QWidget> layer_widget_;
  QListWidget* layer_list_;
  Ui::LayerWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_REFLECT_LAYER_HPP_
