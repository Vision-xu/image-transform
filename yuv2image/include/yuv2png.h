#ifndef YUV2PNG_H
#define YUV2PNG_H

bool rgb24_to_png(const char *filename, uint8_t *rgbData, int width, int height,
                    int quality);
void yuv420sp_to_png(const char *yuvPath, const char *pngPath, int width, int height);

#endif
