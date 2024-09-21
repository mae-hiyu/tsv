/*!
  \file binary_file-inl.hpp
  \author takemura
  */

#ifndef _ZISC_BINARY_FILE_INL_HPP_H_
#define _ZISC_BINARY_FILE_INL_HPP_H_

#include "binary_file.hpp"
// 標準C++ライブラリ
#include <cstddef>
#include <fstream>
#include <ios>
#include <string>
#include <utility>
// Ziscライブラリ
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <BinaryFileType file_type> inline
void BinaryFile<file_type>::close()
{
  binary_file_.close();
}
    
/*!
  \details
  No detailed.

  \param[in] file_name ファイル名
  \return ファイルのオープンに成功した場合はtrue，そうでない場合はfalse
  */
template <BinaryFileType file_type> inline
bool BinaryFile<file_type>::open(const std::string& file_name)
{
  constexpr auto mode = std::ios_base::binary |
      ((file_type == BinaryFileType::kReadWrite)
          ? (std::ios_base::in | std::ios_base::out | std::ios_base::trunc)
          : (file_type == BinaryFileType::kRead)
              ? std::ios_base::in
              : (std::ios_base::out | std::ios_base::trunc));
  binary_file_.open(file_name, mode);
  return !binary_file_.fail();
}

namespace inner {

/*!
  \brief バイナリファイルから値を読み込みます
  \details
  No detailed.

  \param[in] size バッファサイズ
  \param[out] binary_file バイナリファイル
  \return 読み込んだ値
  */
template <typename Type> inline
Type read(const std::streamsize size, std::fstream* binary_file)
{
  Type buffer;
  binary_file->read(reinterpret_cast<char*>(&buffer), size);
  return buffer;
}

/*!
  \brief バイナリファイルから文字列を読み込みます
  \details
  No detailed.

  \param[in] size 文字列サイズ
  \param[out] binary_file バイナリファイル
  \return 読み込んだ文字列
  */
template <> inline
std::string read(const std::streamsize size, std::fstream* binary_file)
{
  std::string buffer;
  buffer.resize(cast<std::size_t>(size));
  binary_file->read(&buffer[0], size);
  return std::move(buffer);
}

/*!
  \brief バイナリファイルに値を書き込みます
  \details
  No detailed.

  \param[in] buffer 書き込む値
  \param[out] binary_file バイナリファイル
  */
template <typename Type> inline
void write(const Type& buffer, std::fstream* binary_file)
{
  binary_file->write(reinterpret_cast<const char*>(&buffer), sizeof(Type));
}

/*!
  \brief バイナリファイルに文字列を書き込みます
  \details
  No detailed.

  \param[in] buffer 書き込む値
  \param[out] binary_file バイナリファイル
  */
inline
void write(const std::string& buffer, std::fstream* binary_file)
{
  (*binary_file) << buffer;
}

/*!
  \brief バイナリファイルに文字列を書き込みます
  \details
  No detailed.

  \param[in] buffer 書き込む値
  \param[out] binary_file バイナリファイル
  */
inline
void write(const char* const& buffer, std::fstream* binary_file)
{
  (*binary_file) << buffer;
}

/*!
  \brief バイナリファイルに文字列を書き込みます
  \details
  No detailed.

  \param[in] buffer 書き込む値
  \param[out] binary_file バイナリファイル
  */
template <std::size_t N> inline
void write(const char (&buffer)[N], std::fstream* binary_file)
{
  (*binary_file) << buffer;
}

} // namespace inner

/*!
 \details
 No detailed.

 \param[in] size バッファサイズ
 \return 読み込んだ値
 */
template <BinaryFileType file_type> template <typename Type> inline
Type BinaryFile<file_type>::read(const std::streamsize size)
{
  static_assert(file_type != BinaryFileType::kWrite,"## write only file can't read.");
  return inner::read<Type>(size, &binary_file_);
}

/*!
  \details
  No detailed.

  \param[in] buffer 書き込む値
  \param[in] buffers 書き込む値
  */
template <BinaryFileType file_type> template <typename Type, typename ...Types> inline
void BinaryFile<file_type>::write(const Type& buffer, const Types& ...buffers)
{
  static_assert(file_type != BinaryFileType::kRead, "## read only file can't write.");
  write(buffer);
  write(buffers...);
}

/*!
  \details
  No detailed.

  \param[in] buffer 書き込む値
  */
template <BinaryFileType file_type> template <typename Type> inline
void BinaryFile<file_type>::write(const Type& buffer)
{
  static_assert(file_type != BinaryFileType::kRead, "## read only file can't write.");
  inner::write(buffer, &binary_file_);
}

} // namespace zisc

#endif // _ZISC_BINARY_FILE_INL_HPP_H_
