/*!
  \file reflect_command.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_COMMAND_HPP_
#define _REFLECT_REFLECT_COMMAND_HPP_

// Standard C++ library
#include <list>
#include <memory>
// Qt
#include <QList>
#include <QUndoCommand>

// Forward declaration
class QString;

namespace reflect {

/*!
  \brief The base class of the Command class
  \details
  No detailed.
  */
class ReflectCommand : public QUndoCommand
{
 public:
  //! Create command
  ReflectCommand(const QString& text);


  //! Add a child command
  void addChild(ReflectCommand* child);

  //! Execute redo
  void redo() override;

  //! Execute undo 
  void undo() override;

 protected:
  //! Execute redo
  virtual void redoCommand() = 0;

  //! Execute undo 
  virtual void undoCommand() = 0;

 private:
  std::list<std::unique_ptr<ReflectCommand>> child_commands_;
};

} // namespace reflect

#endif // _REFLECT_REFLECT_COMMAND_HPP_
