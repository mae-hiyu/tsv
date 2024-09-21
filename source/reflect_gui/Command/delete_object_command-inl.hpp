/*!
  \file delete_object_command-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_DELETE_OBJECT_COMMAND_INL_HPP_
#define _REFLECT_DELETE_OBJECT_COMMAND_INL_HPP_

#include "delete_object_command.hpp"
// Standard C++ library
#include <functional>
#include <memory>
#include <utility>
// ReflectGui
#include "reflect_command.hpp"

// Forward declaration
class QString;

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename Type> inline
DeleteObjectCommand<Type>::DeleteObjectCommand(
    const QString& text,
    std::function<Type* ()> take_function,
    std::function<void (Type*)> add_function) :
        ReflectCommand(text),
        take_function_{std::move(take_function)},
        add_function_{std::move(add_function)}
{
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void DeleteObjectCommand<Type>::redoCommand()
{
  object_.reset(take_function_());
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void DeleteObjectCommand<Type>::undoCommand()
{
  add_function_(object_.release());
}

} // namespace reflect

#endif // _REFLECT_DELETE_OBJECT_COMMAND_INL_HPP_
