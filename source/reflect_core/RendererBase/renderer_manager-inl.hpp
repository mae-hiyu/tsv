/*!
  \file renderer_manager-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERER_MANAGER_INL_HPP_
#define _REFLECT_RENDERER_MANAGER_INL_HPP_

#include "renderer_manager.hpp"
// Qt
#include <QString>

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
bool RendererManager::isRenderingMode() const
{
  return is_rendering_mode_;
}

/*!
  \details
  No detailed.
  */
inline
const QString& RendererManager::renderingDirectory() const
{
  return rendering_dir_;
}

/*!
  \details
  No detailed.
  */
inline
void RendererManager::setRenderingDirectory(const QString& rendering_dir)
{
  rendering_dir_ = rendering_dir;
}

} // namespace reflect

#endif // _REFLECT_RENDERER_MANAGER_INL_HPP_
