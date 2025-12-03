#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "yuv2jpg.h"
#include "yuvutils.h"
#include "jpg/jpeglib.h"


bool rgb24_to_jpg(const char *filename, uint8_t *rgbData, int width,
                    int height,int quality)
{
    struct jpeg_compress_struct jpeg;  //identify a compress object
    struct jpeg_error_mgr jerr;  //error information

    jpeg.err = jpeg_std_error(&jerr);  
    jpeg_create_compress(&jpeg);  //init compress object

    FILE* pFile = fopen(filename,"wb");  
    if( !pFile )  return 0;  
    jpeg_stdio_dest(&jpeg, pFile);  

    //compress param set,i just did a simple param set
    jpeg.client_data=(void*)&pFile;
    jpeg.image_width = width;  
    jpeg.image_height = height;  
    jpeg.input_components  = 3;  
    jpeg.in_color_space = JCS_RGB;   
    jpeg_set_defaults(&jpeg);   
    //指定亮度及色度质量  
    jpeg.q_scale_factor[0] = jpeg_quality_scaling(100);  
    jpeg.q_scale_factor[1] = jpeg_quality_scaling(100);  
    //图像采样率，默认为2 * 2  
    jpeg.comp_info[0].v_samp_factor = 2;  
    jpeg.comp_info[0].h_samp_factor = 2;  
    //set jpeg compress quality  
    jpeg_set_quality(&jpeg, quality, TRUE);  //100 is the highest

    //start compress
    jpeg_start_compress(&jpeg, TRUE);  

    JSAMPROW row_pointer[1];  

    //from up to down ,set every pixel
    for( unsigned int i=0;i<jpeg.image_height;i++ )  
    {  
        row_pointer[0] = rgbData+i*jpeg.image_width*3;  
        jpeg_write_scanlines( &jpeg,row_pointer,1 );  
    }  
    //stop compress
    jpeg_finish_compress(&jpeg);  

    fclose( pFile );  
    pFile = NULL;  
    jpeg_destroy_compress(&jpeg);  
    return 0;  
}


void yuv420sp_to_jpg(const char *yuvPath, const char *jpgPath, int width, int height) 
{
    FILE *file = fopen(yuvPath, "rb");

    uint8_t *yuv420sp = (uint8_t *)malloc(width * height * 3 / 2);

    fread(yuv420sp, 1, width * height * 3 / 2, file);

    uint8_t *rgb24 = (uint8_t *)malloc(width * height * 3);
     

    //yuv420sp转rgb24
    yuv420sp_to_rgb24(yuv420sp, rgb24, width, height);

    //RGB24转JPG文件
    rgb24_to_jpg(jpgPath, rgb24, width, height, 75);

    //释放内存
    free(yuv420sp);
    free(rgb24);

    //关闭文件句柄
    fclose(file);
}


int32_t yuv420sp_to_jpg2(const char *yuvPath, const char *jpgPath, int width, int height, int quality)
{
    struct jpeg_compress_struct jpeg;  //identify a compress object
    struct jpeg_error_mgr jerr;  //error information
    uint8_t *yuv420sp = (uint8_t *)malloc(width * height * 3 / 2);
    uint8_t *data = (uint8_t *)malloc(width * 3); 
    uint8_t *ybase = NULL, *ubase = NULL;
    
    int idx = 0;
    int i = 0, j = 0;

    memset(data, 0, width * 3);
    jpeg.err = jpeg_std_error(&jerr);  
    jpeg_create_compress(&jpeg);  //init compress object
    
    FILE* yFile = fopen(yuvPath, "rb");
    if( !yFile ) return 0;
    fread(yuv420sp, 1, width * height * 3 / 2, yFile);

    FILE* pFile = fopen(jpgPath, "wb");
    if( !pFile )  return 0;  
    jpeg_stdio_dest(&jpeg, pFile);
    ybase = (uint8_t *) yuv420sp;
    ubase = (uint8_t *) (yuv420sp + width * height);

    //compress param set,i just did a simple param set
    //jpeg.client_data=(void*)&pFile;
    jpeg.image_width = width;  
    jpeg.image_height = height;  
    jpeg.input_components  = 3;  
    jpeg.in_color_space = JCS_YCbCr;   
    jpeg_set_defaults(&jpeg);   
    //指定亮度及色度质量  
    jpeg.q_scale_factor[0] = jpeg_quality_scaling(100);  
    jpeg.q_scale_factor[1] = jpeg_quality_scaling(100);  
    
    jpeg.jpeg_color_space = JCS_YCbCr;

    //图像采样率，默认为2 * 2  
    jpeg.comp_info[0].v_samp_factor = 2;  
    jpeg.comp_info[0].h_samp_factor = 2;  
    //set jpeg compress quality  
    jpeg_set_quality(&jpeg, quality, TRUE);  //100 is the highest

    //start compress
    jpeg_start_compress(&jpeg, TRUE);  

    JSAMPROW row_pointer[1];  

    while(jpeg.next_scanline < jpeg.image_height)
    {
        idx = 0;
        for(i = 0; i < width; i++)
        {
            data[idx++] = ybase[i + j * width];
            data[idx++] = ubase[j/2 * width + (i/2) * 2];
            data[idx++] = ubase[j/2 * width + (i/2) * 2 + 1];
        }
        row_pointer[0] = data;
        jpeg_write_scanlines(&jpeg, row_pointer, 1);
        j++;
    }
    //stop compress
    jpeg_finish_compress(&jpeg);  

    fclose(pFile);  
    pFile = NULL;
    fclose(yFile);
    yFile = NULL;
    jpeg_destroy_compress(&jpeg);  
    return 0; 
}
