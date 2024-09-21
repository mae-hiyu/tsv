/*!
 \file non_copyable.hpp
 \author takemura
 */

#ifndef _ZISC_NON_COPYABLE_HPP_
#define _ZISC_NON_COPYABLE_HPP_

namespace zisc {

/*!
 \brief A class that is super class of NonCopyable is Prohibited copy operation
 \details
 No detailed.
 */
class NonCopyable
{
 protected:
  NonCopyable() {}

 private:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};

} // namespace misc

#endif // _ZISC_NON_COPYABLE_HPP_
