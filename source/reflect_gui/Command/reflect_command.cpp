/*!
  \file reflect_command.cpp
  \author takemura
  */

// Standard C++ library
#include <list>
#include <memory>
// Qt
#include <QString>
#include <QUndoCommand>
// Zisc
#include "zisc/utility.hpp"
// ReflectGui
#include "reflect_command.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ReflectCommand::ReflectCommand(const QString& text) :
    QUndoCommand(text, nullptr)
{
}

/*!
  \details
  No detailed.
  */
void ReflectCommand::addChild(ReflectCommand* child)
{
  child_commands_.emplace_back(child);
}

/*!
  \details
  No detailed.
  */
void ReflectCommand::redo()
{
  auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());
  window->disableCommandLogging();

  redoCommand();
  for (auto& child : child_commands_)
    child->redoCommand();

  window->enableCommandLogging();
}

/*!
  \details
  No detailed.
  */
void ReflectCommand::undo()
{
  auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());
  window->disableCommandLogging();

  undoCommand();
  for (auto& child : child_commands_)
    child->undoCommand();

  window->enableCommandLogging();
}

} // namespace reflect
