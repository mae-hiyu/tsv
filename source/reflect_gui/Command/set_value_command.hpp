/*!
  \file set_value_command.hpp
  \author takemura
  */

#ifndef _REFLECT_SET_VALUE_COMMAND_HPP_
#define _REFLECT_SET_VALUE_COMMAND_HPP_

// Standard C++ library
#include <functional>
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
class SetValueCommand : public ReflectCommand
{
 public:
  //! Create a value command
  SetValueCommand(const QString& text, 
               const Type& new_value,
               const Type& old_value,
               std::function<void (const Type& value)> setter);

  
  //! Execute redo
  void redoCommand() override;

  //! Execute undo
  void undoCommand() override;

 private:
  Type new_value_,
       old_value_;
  std::function<void (const Type& value)> setter_;
};

} // namespace reflect

#include "set_value_command-inl.hpp"

#endif // _REFLECT_SET_VALUE_COMMAND_HPP_
