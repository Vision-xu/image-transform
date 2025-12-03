#include <stdio.h>
#include <stdint.h>
#include "yuv2jpg.h"
#include "yuv2png.h"

int32_t main(int32_t argc, char *argv[])
{
    char yuvfilename[256] = {0};
    char jpgfilename[256] = {0};
    //char pngfilename[256] = {0};
    snprintf(yuvfilename, sizeof(yuvfilename), "/tmp/pipeline_2_vse_ochn0_1088x1280_stride_1088_frameid_692_ts_320732704159395.yuv");
    //snprintf(pngfilename, sizeof(pngfilename), "pipeline_2_vse_ochn0_1088x1280_stride_1088_frameid_692_ts_320732704159395.png");
    snprintf(jpgfilename, sizeof(jpgfilename), "pipeline_2_vse_ochn0_1088x1280_stride_1088_frameid_692_ts_320732704159395.jpg");

    //yuv420sp_to_png(yuvfilename, pngfilename, 1088, 1280);

    //yuv420sp_to_jpg(yuvfilename, jpgfilename, 1088, 1280);
    yuv420sp_to_jpg2(yuvfilename, jpgfilename, 1088, 1280, 100);
}
