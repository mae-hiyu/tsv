/*!
 \file renderer_base.hpp
 \author takemura
 */

#ifndef _REFLECT_RENDERER_BASE_HPP_
#define _REFLECT_RENDERER_BASE_HPP_

// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <utility>
// Qt
#include <QString>
// Reflect
#include "color_system.hpp"
#include "renderer_manager.hpp"
#include "renderer_system.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QImage;
class QSettings;
class QFile;
class QTextStream;

namespace reflect {

//! \addtogroup RendererBase
//! \{

/*!
  \details
  No detailed.
  */
class RendererBase
{
 public:
  using LogText = std::pair<UniquePointer<QFile>, UniquePointer<QTextStream>>;


  //! Create renderer
  RendererBase(const QSettings& settings);

  //! Release memory
  virtual ~RendererBase();


  //! Return the color system
  const ColorSystem& colorSystem() const;

  //! Return current time string
  static QString getCurrentTime();

  //! Initialize renderer
  virtual void initialize(const QSettings& settings) = 0;

  //! Return the LDR image format
  const QString& ldrImageFormat() const;

  //! Return the renderer manager
  RendererManager& manager();

  //! Return the renderer manager
  const RendererManager& manager() const;

  //! Print the member data
  static std::size_t printMemberData();

  //! Render scene
  virtual void render() = 0;

  //! Return the renderer system
  RendererSystem& system();

 protected:
  //! Get the text style time
  QString getTimeText(const std::int64_t milli_time) const;

  //! Log rendering time
  void logRenderingTime(LogText& log,
                        const std::size_t pass,
                        const std::int64_t pass_time,
                        const std::int64_t total_time) const;

  //! Make log text
  LogText makeLogText(const QString& file_name) const;

 private:
  //! Initialize renderer base
  void initializeBase(const QSettings& settings);

  //! Set LDR image format
  void setLdrImageFormat(const QSettings& settings);


  RendererManager manager_;
  UniquePointer<RendererSystem> system_;
  UniquePointer<ColorSystem> color_system_;
  QString ldr_image_format_;
};

//! Output log
template <typename Type>
RendererBase::LogText& operator<<(RendererBase::LogText& log, const Type& message);

//! \} RendererBase

} // namespace reflect

#include "renderer_base-inl.hpp"

#endif // _REFLECT_RENDERER_BASE_HPP_
