//
//  fileSystem.cpp
//  ImageComparator
//
//  Created by 渡部 心 on 12/01/25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "fileSystem.hpp"
#include <boost/foreach.hpp>

namespace FileSystem {
    void enumerateFileNames(const string &where) {
        const fs::path path(where.empty() ? fs::current_path() : where.c_str());
        BOOST_FOREACH(const fs::path& p, std::make_pair(fs::directory_iterator(path), fs::directory_iterator())) {
            if (fs::is_directory(p)) {
                printf("D ");
            }
            else {
                printf("F ");
            }
            printf("%s\n", p.filename().string().c_str());
        }
    }
    
    void getFileNames(string** files, int* n, const string &where, const string &ext) {
        fs::path p(where.empty() ? fs::current_path() : where.c_str());
        fs::directory_iterator end;
        //----------------------------------------------------------------
        //ファイル数カウント。
        *n = 0;
        for (fs::directory_iterator it(p); it != end; ++it) {
            fs::path& filepath = (fs::path&)(*it);
            if (filepath.extension().string() == ext || ext.empty()) {
                ++(*n);
            }
        }
        //----------------------------------------------------------------
        
        //----------------------------------------------------------------
        //ファイル名の取得。
        if (*n > 0) {
            *files = (string*)malloc(*n * sizeof(string));
            int index = 0;
            for (fs::directory_iterator it(p); it != end; ++it) {
                fs::path& filepath = (fs::path&)(*it);
                if (filepath.extension().string() == ext || ext.empty()) {
                    new (&((*files)[index])) string(filepath.filename().string());
                    ++index;
                }
            }
        }
        //----------------------------------------------------------------
    }
    
    bool fileExists(const string &file, const string &where) {
        string fullpath = where;
        if (fullpath[fullpath.length() - 1] == '/') {
            fullpath.erase(--fullpath.end());
        }
        fullpath += file;
        fs::path p(fullpath.c_str());
        boost::system::error_code ercode;
        return fs::exists(p, ercode);
    }
}
