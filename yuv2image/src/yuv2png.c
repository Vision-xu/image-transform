#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "yuv2png.h"
#include "yuvutils.h"
#include "png/png.h"


bool rgb24_to_png(const char *filename, uint8_t *rgbData, int width,
                    int height,int quality)
{
    FILE *fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    fp = fopen(filename, "wb");
    if (fp) {
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        info_ptr = png_create_info_struct(png_ptr);
        if (png_ptr == NULL || info_ptr == NULL) {
            fclose(fp);
            return false;
        }
        png_init_io(png_ptr, fp);
        png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
       
        png_write_info(png_ptr, info_ptr);
        png_set_packing(png_ptr);
        uint8_t *data = (uint8_t *) malloc(width * 3);
        memset(data, 0, width * 3);
        uint32_t rgb_index = 0;
        for (uint32_t i = 0; i < height; ++i) {
            for (uint32_t j = 0; j < width; ++j) {
                data[j * 3 + 0] = rgbData[rgb_index++];
                data[j * 3 + 1] = rgbData[rgb_index++];
                data[j * 3 + 2] = rgbData[rgb_index++];
            }
            png_write_row(png_ptr, data);
        }

        free(data);
        png_write_end(png_ptr, info_ptr);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return true;
    }
    return false;
}


void yuv420sp_to_png(const char *yuvPath, const char *pngPath, int width, int height) 
{
    FILE *file = fopen(yuvPath, "rb");

    uint8_t *yuv420sp = (uint8_t *)malloc(width * height * 3 / 2);

    fread(yuv420sp, 1, width * height * 3 / 2, file);

    uint8_t *rgb24 = (uint8_t *)malloc(width * height * 3);
     

    //yuv420sp转rgb24
    yuv420sp_to_rgb24(yuv420sp, rgb24, width, height);

    //RGB24转PNG文件
    rgb24_to_png(pngPath, rgb24, width, height, 100);

    //释放内存
    free(yuv420sp);
    free(rgb24);

    //关闭文件句柄
    fclose(file);
}
