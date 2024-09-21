/*!
  \file renderer_manager.cpp
  \author takemura
  */

#include "renderer_manager.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RendererManager::RendererManager() :
    is_rendering_mode_{true}
{
}

/*!
  \details
  No detailed.
  */
void RendererManager::finishRendering()
{
  is_rendering_mode_ = false;
}

} // namespace reflect
