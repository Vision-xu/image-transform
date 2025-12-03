#include <sys/types.h>
#include <stdint.h>
#include "yuvutils.h"


void yuv420sp_to_rgb24(uint8_t *yuv420sp, uint8_t *rgb24, int width, int height)
{
    int index =0;
    uint8_t *ybase = yuv420sp;
    uint8_t *ubase = &yuv420sp[width * height];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            uint8_t Y = ybase[y + x * width];
            uint8_t U = ubase[x / 2 * width + (y / 2) * 2];
            uint8_t V = ubase[x / 2 * width + (y / 2) * 2 + 1];
            
            rgb24[index++] = Y + 1.402 * (V - 128); //R  
            rgb24[index++] = Y - 0.34413 * (U - 128) - 0.71414 * (V - 128); //G
            rgb24[index++] = Y + 1.772 * (U - 128); //B
            
            /*
            rgb24[index++] = Y + 1.779 * (U - 128); //B
            rgb24[index++] = Y - 0.3455 * (U - 128) - 0.7169 * (V - 128); //G 
            rgb24[index++] = Y + 1.4075 * (V - 128); //R  
            */
        }
    }

}
