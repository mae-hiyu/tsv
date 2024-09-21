/*!
  \file renderer_manager.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERER_MANAGER_HPP_
#define _REFLECT_RENDERER_MANAGER_HPP_

// Qt
#include <QObject>
#include <QString>

// Forward declaration
class QImage;

namespace reflect {

//! \addtogroup RendererBase
//! \{

/*!
  \details
  No detailed.
  */
class RendererManager : public QObject
{
  Q_OBJECT

 public slots:
  //! Finish rendering
  void finishRendering();

 public:
  //! Create a renderer manager
  RendererManager();


  //! Check if the renderer is rendering mode.
  bool isRenderingMode() const;

  //! Return the rendering directory
  const QString& renderingDirectory() const;

  //! Set the rendering directory
  void setRenderingDirectory(const QString& rendering_dir);

 signals:
  //! Output text
  void outputText(const QString& text) const;

  //! Output image
  void outputImage(const QImage& image) const;

  //! This function is called, when rendering is finished
  void finishedRendering() const;

 private:
  bool is_rendering_mode_;
  QString rendering_dir_;
};

//! \} RendererBase

} // namespace reflect

#include "renderer_manager-inl.hpp"

#endif // _REFLECT_RENDERER_MANAGER_HPP_
