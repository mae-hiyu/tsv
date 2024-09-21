//
//  manipulatePNG.cpp
//  ImageComparator_MT2
//
//  Created by 渡部 心 on 12/10/25.
//  Copyright (c) 2012年 Shin Watanabe. All rights reserved.
//

#include "manipulatePNG.hpp"
#include <stdio.h>
#include <time.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

const size_t PNG_BYTES_TO_CHECK = 4;

void checkIfPNG(const char *file_name, FILE **fp)
{
	unsigned char sig[PNG_BYTES_TO_CHECK];
	
	if ((*fp = fopen(file_name, "rb")) != NULL) {
        if (fread(sig, 1, PNG_BYTES_TO_CHECK, *fp) != PNG_BYTES_TO_CHECK) {
            fclose(*fp);
            *fp = NULL;
        }
        if (png_sig_cmp(sig, 0, PNG_BYTES_TO_CHECK)) {
            fclose(*fp);
            *fp = NULL;
        }
    }
}

void readPNGInfo(FILE *fp, png_structp *png_ptr, png_infop *info_ptr)
{
	*png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (*png_ptr == NULL) {
        fclose(fp);
        exit(EXIT_FAILURE);
	}
	*info_ptr = png_create_info_struct(*png_ptr);
	if (*info_ptr == NULL) {
        png_destroy_read_struct(png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
	}
	if (setjmp(png_jmpbuf(*png_ptr))) {
        png_destroy_read_struct(png_ptr, info_ptr, (png_infopp)NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
	}
	png_init_io(*png_ptr, fp);
	png_set_sig_bytes(*png_ptr, PNG_BYTES_TO_CHECK);
	png_read_info(*png_ptr, *info_ptr);
}

void readPNG(FILE *fp, png_structp png_ptr, png_infop info_ptr, png_bytepp *image, png_uint_32 *width, png_uint_32 *height)
{
	png_uint_32     i, j;
	
	*width = png_get_image_width(png_ptr, info_ptr);
	*height = png_get_image_height(png_ptr, info_ptr);
    if (*image == NULL) {
     	if ((*image = (png_bytepp)malloc(*height * sizeof(png_bytep))) == NULL) {
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < *height; i++) {
            (*image)[i] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
            if ((*image)[i] == NULL) {
                for (j = 0; j < i; j++) free((*image)[j]);
                free(*image);
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
	png_read_image(png_ptr, *image);
}

void ReadPNGFile(const char* filename, unsigned char*** data, int* width, int* height) {
    FILE* fp;
    png_structp png_ptr;
    png_infop png_info_ptr;
    png_bytepp imagedata = *data;
    png_uint_32 _width;
    png_uint_32 _height;
    //    png_byte depth;
    //    png_byte channels;
    
    checkIfPNG(filename, &fp);
    if (fp != NULL) {
        readPNGInfo(fp, &png_ptr, &png_info_ptr);
        readPNG(fp, png_ptr, png_info_ptr, &imagedata, &_width, &_height);
        *width = int(_width);
        *height = int(_height);
        //        depth = png_get_bit_depth(png_ptr, png_info_ptr);
        //        channels = png_get_channels(png_ptr, png_info_ptr);
        //        printf("size : %dx%d, bitdepth : %dx%d\n", width, height, depth, channels);
        
        //        double gamma;
        //        if (png_get_gAMA(png_ptr, png_info_ptr , &gamma)) {
        //            printf("gamma : %.3f\n", gamma);
        //        }
        
        //        png_textp text_ptr;
        //        int num_text;
        //        if (png_get_text(png_ptr, png_info_ptr, &text_ptr, &num_text)) {
        //            for (int i = 0; i < num_text; ++i) {
        //                printf("%s", text_ptr[i].text);
        //            }
        //            printf("\n");
        //        }
        
        *data = (unsigned char**)imagedata;
        
        png_destroy_read_struct(&png_ptr, &png_info_ptr, (png_infopp)NULL);
        fclose(fp);
    }
    else {
        *data = NULL;
    }
}

int writePNG(const char *file_name, png_bytepp image, int width, int height)
{
	FILE *fp;
	png_structp	png_ptr;
	png_infop info_ptr;
    
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
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);
	png_set_filter(png_ptr, 0, PNG_ALL_FILTERS);
	png_set_compression_level(png_ptr, 6);
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    //	png_set_gAMA(png_ptr, info_ptr, 1.0);
    
	{
		time_t		gmt;		// G.M.T.
		png_time	mod_time;
        //		png_text	text_ptr[5];
        
		time(&gmt);
		png_convert_from_time_t(&mod_time, gmt);
		png_set_tIME(png_ptr, info_ptr, &mod_time);
		
        //		text_ptr[0].key = "Title";
        //		text_ptr[0].text = "Test";
        //		text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
        //		text_ptr[1].key = "Author";
        //		text_ptr[1].text = "Yuzo KATO";
        //		text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
        //		text_ptr[2].key = "Description";
        //		text_ptr[2].text = "Test Pattern";
        //		text_ptr[2].compression = PNG_TEXT_COMPRESSION_NONE;
        //		text_ptr[3].key = "Creation Time";
        //		text_ptr[3].text = png_convert_to_rfc1123(png_ptr, &mod_time);
        //		text_ptr[3].compression = PNG_TEXT_COMPRESSION_NONE;
        //		text_ptr[4].key = "Software";
        //		text_ptr[4].text = "test.exe";
        //		text_ptr[4].compression = PNG_TEXT_COMPRESSION_NONE;
        //		png_set_text(png_ptr, info_ptr, text_ptr, 5);
	}
	
	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, image);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return 0;
}

int writePNGwithDate(const char *name, const int index, png_bytepp image, int width, int height) {
    struct tm* t_st;
    time_t timer;
    time(&timer);
    t_st = localtime(&timer);
    char strTime[300];
    sprintf(strTime, "%s_%d__%4d%02d%02d_%02d%02d%02d.png",
            name, index,
            t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday,
            t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

    return writePNG(strTime, image, width, height);
}
