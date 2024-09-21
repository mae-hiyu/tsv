/*!
  \file add_object_command.hpp
  \author takemura
  */

#ifndef _REFLECT_ADD_OBJECT_COMMAND_HPP_
#define _REFLECT_ADD_OBJECT_COMMAND_HPP_

// Standard C++ library
#include <functional>
#include <memory>
// ReflectGui
#include "reflect_command.hpp"

// Forward declaration
class QString;

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename Type>
class AddObjectCommand : public ReflectCommand
{
 public:
  //! Create a add object command
  AddObjectCommand(const QString& text,
                   std::unique_ptr<Type>&& object,
                   std::function<void (Type*)> add_function,
                   std::function<Type* ()> take_function);


  //! Execute redo
  void redoCommand() override;

  //! Execute undo
  void undoCommand() override;

 private:
  std::unique_ptr<Type> object_;
  std::function<void (Type*)> add_function_;
  std::function<Type* ()> take_function_;
};

} // namespace reflect

#include "add_object_command-inl.hpp"

#endif // _REFLECT_ADD_OBJECT_COMMAND_HPP_
