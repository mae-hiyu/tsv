/*!
 \file string.cpp
 \author takemura
 */

#include "string.hpp"
// Standard C++ library
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace zisc {

/*!
  \details
  No detailed.
  */
std::string load(const std::string& file_path)
{
  std::ifstream file{file_path, std::ios::in | std::ios::binary};
  std::stringstream text;
  while (!file.eof()) {
    const char character = file.get();
    switch (character) {
     case '\n':
      text << std::endl;
      break;
     case '\r':
      if (file.peek() == '\n')
        file.get();
      text << std::endl;
      break;
     default:
      text << character;
    }
  }
  return text.str();
}

/*!
  \details
  No detailed.
  */
std::string trim(const std::string& string)
{
  if (string.empty())
    return string;

  // Find head white spaces
  std::string::size_type head = 0;
  for (; head < string.size(); ++head) {
    if (string[head] != ' ')
      break;
  }

  // return empty string if all characters are white space
  if (head == string.size())
    return std::string{};

  // Find tail white spaces
  std::string::size_type tail;
  for (tail = string.size() - 1; tail > 0; --tail) {
    if (string[tail] != ' ')
      break;
  }
  ++tail;

  return ((head == 0) && (tail == string.size()))
    ? string
    : string.substr(head, tail - head);
}

} // namespace zisc
