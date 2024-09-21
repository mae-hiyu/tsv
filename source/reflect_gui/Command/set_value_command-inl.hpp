/*!
  \file set_value_command-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SET_VALUE_COMMAND_INL_HPP_
#define _REFLECT_SET_VALUE_COMMAND_INL_HPP_

#include "set_value_command.hpp"
// Standard C++ library
#include <functional>
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
SetValueCommand<Type>::SetValueCommand(
    const QString& text,
    const Type& new_value,
    const Type& old_value,
    std::function<void (const Type& value)> setter) :
        ReflectCommand(text),
        new_value_{new_value},
        old_value_{old_value},
        setter_{std::move(setter)}
{
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void SetValueCommand<Type>::redoCommand()
{
  setter_(new_value_);
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void SetValueCommand<Type>::undoCommand()
{
  setter_(old_value_);
}

} // namespace reflect

#endif // _REFLECT_SET_VALUE_COMMAND_INL_HPP_
