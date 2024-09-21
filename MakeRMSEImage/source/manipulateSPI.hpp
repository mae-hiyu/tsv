//
//  manipulateSPI.h
//  GIRenderer
//
//  Created by 渡部 心 on 12/10/14.
//
//

#ifndef __GIRenderer__manipulateSPI__
#define __GIRenderer__manipulateSPI__

#include <cstdio>
#include <cstdlib>

struct SPIHeader {
    unsigned char filetype[3];
    int width, height, numWL;
    float minWL, maxWL;
    SPIHeader() {};
    SPIHeader(int w, int h, int numWL_, float minWL_, float maxWL_) {
        filetype[0] = 'S';
        filetype[1] = 'P';
        filetype[2] = 'I';
        width = w;
        height = h;
        numWL = numWL_;
        minWL = minWL_;
        maxWL = maxWL_;
    }
};

bool thisIsSPI(const char *file_name);
void readSPIInfo(const char *file_name, SPIHeader* headerInfo);
void readSPI(const char *file_name, float**** data, int* width, int* height, int* numWL, float* minWL, float* maxWL);

int writeSPI(const char *file_name, float*** image, int width, int height, int numWL, float minWL, float maxWL);

#endif /* defined(__GIRenderer__manipulateSPI__) */
