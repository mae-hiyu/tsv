/*!
  \file reflect_multilayer.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_MULTILAYER_HPP_
#define _REFLECT_REFLECT_MULTILAYER_HPP_

// ReflectGui
#include "reflect_widget.hpp"

// Forward declaration
class QListWidget;
class QPushButton;
class QWidget;

namespace reflect {

// Forward declaration
class ReflectLayer;

/*!
  \details
  No detailed.
  */
class ReflectMultilayer : public ReflectWidget
{
 public:
  //! Create a multilayer widget
  ReflectMultilayer(QWidget* parent);


  //! Activate
  void activate() override;

  //! Add a layer
  void addLayer(ReflectLayer* layer);

  //! Set add layer button
  template <typename LayerClass>
  void setAddLayerButton(QPushButton* button);

  //! Set delete layer button
  void setDeleteLayerButton(QPushButton* button);

  //! Set layer list widget
  void setLayerList(QListWidget* layer_list);

  //! Set move down button
  void setMoveDownButton(QPushButton* button);

  //! Set move up button
  void setMoveUpButton(QPushButton* button);

 private:
  //! Initialize
  void initialize();

  //! Update layer number
  void updateLayerNumber();


  QListWidget* layer_list_;
};

} // namespace reflect

#include "reflect_multilayer-inl.hpp"

#endif // _REFLECT_REFLECT_MULTILAYER_HPP_
