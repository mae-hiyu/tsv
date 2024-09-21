/*!
  \file binary_file.hpp
  \author takemura
  */

#ifndef _ZISC_BINARY_FILE_HPP_
#define _ZISC_BINARY_FILE_HPP_

// 標準C++ライブラリ
#include <fstream>
#include <string>
// Ziscライブラリ
#include "non_copyable.hpp"
#include "utility.hpp"

namespace zisc {

/*!
  \brief バイナリファイルのタイプを表します
  \details
  No detailed.
  */
enum class BinaryFileType
{
  kRead,
  kWrite,
  kReadWrite
};

/*!
  \brief バイナリファイルを扱います
  \details
  No detailed.
  */
template <BinaryFileType file_type>
class BinaryFile : public NonCopyable
{
 public:
  //! ファイルを閉じます
  void close();

  //! ファイルを開きます
  bool open(const std::string& file_name);

  //! バイナリファイルから値を読み込みます
  template <typename Type>
  Type read(const std::streamsize size = cast<std::streamsize>(sizeof(Type)));

  //! バイナリファイルに書き込みます
  template <typename Type, typename ...Types>
  void write(const Type& buffer, const Types& ...buffers);

  //! バイナリファイルに書き込みます
  template <typename Type>
  void write(const Type& buffer);

 private:
  std::fstream binary_file_;
};

// 使いやすい別名をつけます
using ReadBinary = BinaryFile<BinaryFileType::kRead>;
using WriteBinary = BinaryFile<BinaryFileType::kWrite>;
using ReadWriteBinary = BinaryFile<BinaryFileType::kReadWrite>;

} // namespace zisc

#include "binary_file-inl.hpp"

#endif // _ZISC_BINARY_FILE_HPP_
