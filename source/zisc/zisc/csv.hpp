/*
 \file csv.hpp
 \author takemura
 */

#ifndef _ZISC_CSV_HPP_
#define _ZISC_CSV_HPP_

// Standard C++ library
#include <cstddef>
#include <istream>
#include <list>
#include <string>
#include <tuple>
// Zisc
#include "non_copyable.hpp"

namespace zisc {

/*!
 \brief Manipulate CSV file
 \details
 No detailed.
 */
template <typename ...Types>
class Csv : public NonCopyable
{
 public:
  using RecordType = std::tuple<Types...>;

  template <std::size_t index>
  using FieldType = typename std::tuple_element<index, RecordType>::type;


  //! Add values
  void append(const std::string& csv);

  //! Add values
  void append(std::istream& csv);

  //! Clear all csv data
  void clear();

  //! Get column size
  static constexpr std::size_t columnSize() 
  {
    return sizeof...(Types);
  }

  //! Get record 
  const RecordType& record(const std::size_t row) const;

  //! Get row size
  std::size_t rowSize() const;

  //! Get value
  template <std::size_t column>
  const FieldType<column>& get(const std::size_t row) const;

 private:
  //! CSVを要素ごとに分割します
  RecordType split(const std::string& csv) const;


  std::list<RecordType> data_;
};

} // namespace zisc

#include "csv-inl.hpp"

#endif // _ZISC_CSV_HPP_
