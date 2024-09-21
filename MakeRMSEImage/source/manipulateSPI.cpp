//
//  manipulateSPI.cpp
//  GIRenderer
//
//  Created by 渡部 心 on 12/10/14.
//
//

#include "manipulateSPI.hpp"
#include <stdio.h>
#include <time.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

bool thisIsSPI(const char *file_name) {
    FILE* fp;
    if ((fp = fopen(file_name, "rb")) == NULL) {
        printf("file does not exist.\n");
        return false;
    }
    
    unsigned char filetype[3];
    SPIHeader header;
    fread(filetype, sizeof(unsigned char), 3, fp);
    fclose(fp);
    if (filetype[0] != 'S' || filetype[1] != 'P' || filetype[2] != 'I') {
        return false;
    }
    
    return true;
}

void readSPIInfo(const char *file_name, SPIHeader* headerInfo) {
    if (thisIsSPI(file_name)) {
        FILE* fp = fopen(file_name, "rb");
        fread(headerInfo, sizeof(SPIHeader), 1, fp);
        fclose(fp);
    }
    else {
        *headerInfo = SPIHeader();
    }
}

void readSPI(const char *file_name, float**** data, int* width, int* height, int* numWL, float* minWL, float* maxWL) {
    if (!thisIsSPI(file_name)) {
        *width = *height = 0.0f;
        *numWL = 0;
        *minWL = *maxWL = 0.0f;
        return;
    }
    FILE* fp = fopen(file_name, "rb");
    SPIHeader header;
    readSPIInfo(file_name, &header);
    *width = header.width;
    *height = header.height;
    *numWL = header.numWL;
    *minWL = header.minWL;
    *maxWL = header.maxWL;
    
    fseek(fp, sizeof(SPIHeader), SEEK_SET);
    
    *data = (float***)malloc(*height * sizeof(float**));
    for (int i = 0; i < *height; ++i) {
        (*data)[i] = (float**)malloc(*width * sizeof(float*));
        for (int j = 0; j < *width; ++j) {
            (*data)[i][j] = (float*)malloc(*numWL * sizeof(float));
            fread((*data)[i][j], sizeof(float), *numWL, fp);
        }
    }
    fclose(fp);
}

int writeSPI(const char *file_name, float*** image, int width, int height, int numWL, float minWL, float maxWL) {
    FILE *fp;
    
    //--------------------------------------------------
    //ディレクトリーの存在確認。無ければ作成。
    namespace fs = boost::filesystem;
    int index = 0;
    while (true) {
        if (file_name[index] == '\0') {
            while (true) {
                if (index == 0 || file_name[--index] == '/') {
                    break;
                }
            }
            break;
        }
        ++index;
    }
    char* nestDir = (char*)malloc((index + 1) * sizeof(char));
    memcpy((void*)nestDir, (void*)file_name, index);
    nestDir[index] = '\0';
    fs::path p(nestDir);
    boost::system::error_code ercode;
    if (fs::exists(p, ercode) == false) {
        fs::create_directories(p, ercode);
    }
    free(nestDir);
    //--------------------------------------------------
    
	if ((fp = fopen(file_name, "wb")) == NULL) {
        return 1;
    }
    SPIHeader head(width, height, numWL, minWL, maxWL);
    fwrite(&head, sizeof(head), 1, fp);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fwrite(image[i][j], sizeof(float), numWL, fp);
        }
    }
    
	fclose(fp);
	return 0;
}
