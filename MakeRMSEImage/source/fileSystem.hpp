//
//  fileSystem.h
//  ImageComparator
//
//  Created by 渡部 心 on 12/01/25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ImageComparator_fileSystem_h
#define ImageComparator_fileSystem_h

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
using namespace std;
namespace fs = boost::filesystem;

namespace FileSystem {
    //指定したディレクトリ内のファイル・ディレクトリを列挙する。空文字列を渡すとカレントディレクトリ。
    void enumerateFileNames(const string &where = string(""));
    //指定したディレクトリ内のファイル・ディレクトリ名を取得する。空文字列を渡すとカレントディレクトリ。
    void getFileNames(string** files, int* n, const string &where = string(""), const string &ext = string(""));
    //指定したディレクトリ内のファイル・ディレクトリが存在するかを確かめる。空文字列を渡すとカレントディレクトリ。
    bool fileExists(const string &file, const string &where = string(""));
}

#endif
