/*!
  \file renderer_base-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERER_BASE_INL_HPP_
#define _REFLECT_RENDERER_BASE_INL_HPP_

#include "renderer_base.hpp"
// Qt
#include <QFile>
#include <QString>
#include <QTextStream>
// Zisc
#include "zisc/thread_pool.hpp"
// Reflect
#include "color_system.hpp"
#include "reflect_config.hpp"
#include "renderer_manager.hpp"
#include "renderer_system.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
const ColorSystem& RendererBase::colorSystem() const
{
  return *color_system_;
}

/*!
  \details
  No detailed.
  */
inline
const QString& RendererBase::ldrImageFormat() const
{
  return ldr_image_format_;
}

/*!
  \details
  No detailed.
  */
inline
RendererManager& RendererBase::manager()
{
  return manager_;
}

/*!
  \details
  No detailed.
  */
inline
const RendererManager& RendererBase::manager() const
{
  return manager_;
}

/*!
  \details
  No detailed.
  */
inline
RendererSystem& RendererBase::system()
{
  return *system_;
}

/*!
  \details
  No detailed.
  */
inline
void RendererBase::logRenderingTime(LogText& log,
                                    const std::size_t pass,
                                    const std::int64_t pass_time,
                                    const std::int64_t total_time) const
{
  const auto pass_time_text = getTimeText(pass_time);
  const auto total_time_text = getTimeText(total_time);

  const QString log_text{"%1,    %2,    %3,    %4,    %5"};
  log << (((log_text.arg(pass))
                    .arg(pass_time))
                    .arg(total_time))
                    .arg(pass_time_text, total_time_text) << endl;
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
RendererBase::LogText& operator<<(RendererBase::LogText& log, const Type& message)
{
  *log.second << message;
  return log;
}

} // namespace reflect

#endif // _REFLECT_RENDERER_BASE_INL_HPP_
