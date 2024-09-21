/*!
 \file csv-inl.hpp
 \author takemura
 */

#ifndef _ZISC_CSV_INL_HPP_
#define _ZISC_CSV_INL_HPP_

#include "csv.hpp"
// Standard C++ library
#include <cstddef>
#include <istream>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
// Zisc
#include "error.hpp"
#include "string.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace zisc {

// public member function


/*!
 \details
 No detailed.
 */
template <typename ...Types> inline
void Csv<Types...>::append(const std::string& csv)
{
  auto&& record = split(csv);
  data_.push_back(std::move(record));
}

/*!
 \details
 No detailed.
 */
template <typename ...Types>
void Csv<Types...>::append(std::istream& csv)
{
  for (std::string line; std::getline(csv, line);) {
    auto&& record = split(line);
    data_.push_back(std::move(record));
  }
}

/*!
  \details
  No detailed.
  */
template <typename ...Types> inline
void Csv<Types...>::clear()
{
  data_.clear();
}

/*!
 \details
 No detailed.
 */
template <typename ...Types> inline
auto Csv<Types...>::record(const std::size_t row) const -> const RecordType&
{
  auto&& record = 
      std::next(data_.begin(), 
                cast<typename std::list<RecordType>::difference_type>(row));
  return *record;
}

/*!
 \details
 No detailed.
 */
template <typename ...Types> inline
std::size_t Csv<Types...>::rowSize() const
{
  return data_.size();
}

/*!
 \details
 No detailed.
 */
template <typename ...Types> template <std::size_t column> inline
auto Csv<Types...>::get(const std::size_t row) const -> const FieldType<column>&
{
  const auto& record = this->record(row);
  return std::get<column>(record);
}

// private member function

namespace inner {

template <typename RecordType, std::size_t count>
class CsvSplitter
{
  static constexpr std::size_t index = std::tuple_size<RecordType>::value - count;
  using Type = typename std::tuple_element<index, RecordType>::type;

 public:
  template <typename ...Types>
  static RecordType split(std::istringstream& line, const Types& ...values)
  {
    std::string value;
    if (!std::getline(line, value, ','))
      raiseError("## CsvError: Invalid number of fields.");
    return CsvSplitter<RecordType, count-1>::
        split(line, values..., toCxxValue<Type>(zisc::trim(value)));
  }

 private:
  template <typename Type, EnableIfBoolean<Type> = kEnabler>
  static Type toCxxValue(const std::string& value)
  {
    return toBoolean(value);
  }

  template <typename Type, EnableIfInteger<Type> = kEnabler>
  static Type toCxxValue(const std::string& value)
  {
    return toInteger<Type>(value);
  }

  template <typename Type, EnableIfFloat<Type> = kEnabler>
  static Type toCxxValue(const std::string& value)
  {
    return toFloat<Type>(value);
  }

  template <typename Type, EnableIfString<Type> = kEnabler>
  static Type toCxxValue(const std::string& value)
  {
    return value.substr(1, value.size() - 2);
  }

//  static bool isString(const std::string& string)
//  {
//    return (string.front() == '\"') && (string.back() == '\"');
//  }
};

template <typename RecordType>
class CsvSplitter<RecordType, 0>
{
 public:
  template <typename ...Types>
  static RecordType split(std::istringstream& /* line */, const Types& ...values)
  {
    return RecordType{values...};
  }

 private:
};

} // namespace inner

template <typename ...Types>
typename Csv<Types...>::RecordType Csv<Types...>::split(const std::string& csv) const
{
  std::istringstream line{csv};
  auto record = inner::CsvSplitter<RecordType, sizeof...(Types)>::split(line);
  if (!line.eof())
    raiseError("## CsvError: Invalid grammar: \"", line.str(), "\".");
  return record;
}

} // namespace zisc

#endif // _ZISC_CSV_INL_HPP_
