#ifndef YUVUTILS_H
#define YUVUTILS_H
#include <stdint.h>

void yuv420sp_to_rgb24(uint8_t *yuv420sp, uint8_t *rgb24, int width, int height);
#endif
