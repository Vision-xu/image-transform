#ifndef YUV2JPG_H
#define YUV2JPG_H
#include <stdbool.h>
#include <stdint.h>

bool rgb24_to_jpg(const char *filename, uint8_t *rgbData, int width, int height,
                    int quality);
void yuv420sp_to_jpg(const char *yuvPath, const char *pngPath, int width, int height);

int32_t yuv420sp_to_jpg2(const char *yuvPath, const char *pngPath, int width, int height, int quality);

#endif
