/*!
  \file reflect_multilayer-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_MULTILAYER_INL_HPP_
#define _REFLECT_REFLECT_MULTILAYER_INL_HPP_

#include "reflect_multilayer.hpp"
// Standard C++ library
#include <memory>
#include <type_traits>
#include <utility>
// Qt
#include <QPushButton>
#include <QString>
// Zisc
#include "zisc/utility.hpp"
// ReflectGui
#include "reflect_layer.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/add_object_command.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <typename LayerClass> inline
void ReflectMultilayer::setAddLayerButton(QPushButton* button)
{
  static_assert(std::is_base_of<ReflectLayer, LayerClass>::value,
                "## LayerClass must be the super class of ReflectLayer.");

  auto add_layer = [this]()
  {
    auto* window = ReflectWidget::mainWindow();
    window->disableCommandLogging();

    auto layer = std::unique_ptr<LayerClass>{new LayerClass{}};
    layer->setLayerList(layer_list_);

    const auto text = QStringLiteral("Add %1 layer.").arg(layer->name());
    auto add_function = [this](LayerClass* layer)
    {
      layer_list_->insertItem(0, layer);
      layer->activate();
      layer_list_->setCurrentItem(nullptr);
      updateLayerNumber();
    };
    auto take_function = [this]()
    {
      auto* layer = cast<LayerClass*>(layer_list_->takeItem(0));
      layer_list_->setCurrentItem(nullptr);
      updateLayerNumber();
      return layer;
    };

    auto* command = new AddObjectCommand<LayerClass>{text, std::move(layer),
                                                     add_function, take_function};
    window->appendCommand(command);

    window->enableCommandLogging();
  };

  connection_list_ << connectButton(button, add_layer);
}

} // namespace reflect

#endif // _REFLECT_REFLECT_MULTILAYER_INL_HPP_
