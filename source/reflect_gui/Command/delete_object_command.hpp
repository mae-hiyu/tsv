/*!
  \file delete_object_command.hpp
  \author takemura
  */

#ifndef _REFLECT_DELETE_OBJECT_COMMAND_HPP_
#define _REFLECT_DELETE_OBJECT_COMMAND_HPP_

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
class DeleteObjectCommand : public ReflectCommand
{
 public:
  //! Create a delete object command
  DeleteObjectCommand(const QString& text,
                      std::function<Type* ()> take_function,
                      std::function<void (Type*)> add_function);


  //! Execute redo
  void redoCommand() override;

  //! Execute undo
  void undoCommand() override;

 private:
  std::unique_ptr<Type> object_;
  std::function<Type* ()> take_function_;
  std::function<void (Type*)> add_function_;
};

} // namespace reflect

#include "delete_object_command-inl.hpp"

#endif // _REFLECT_DELETE_OBJECT_COMMAND_HPP_
