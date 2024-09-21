//
//  manipulatePNG.h
//  ImageComparator_MT2
//
//  Created by 渡部 心 on 12/10/25.
//  Copyright (c) 2012年 Shin Watanabe. All rights reserved.
//

#ifndef __ImageComparator_MT2__manipulatePNG__
#define __ImageComparator_MT2__manipulatePNG__

#include <libpng16/png.h>

void checkIfPNG(const char *file_name, FILE **fp);
void readPNGInfo(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);
void readPNG(FILE *fp, png_structp png_ptr, png_infop info_ptr, png_bytepp *image, png_uint_32 *width, png_uint_32 *height);
void ReadPNGFile(const char* filename, unsigned char*** data, int* width, int* height);

//RGBの順番で渡す。
int writePNG(const char *file_name, png_bytepp image, int width, int height);
int writePNGwithDate(const char *name, png_bytepp image, int width, int height);

#endif /* defined(__ImageComparator_MT2__manipulatePNG__) */
