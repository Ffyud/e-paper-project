/*****************************************************************************
* | File      	:   EPD_2in15b_test.c
* | Author      :   Waveshare team
* | Function    :   2inch15 e-paper (B) test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2024-08-07
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to dealv
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included inv
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_2in15b.h"
#include <time.h> 

int EPD_2in15b_test(void)
{
    printf("EPD_2IN15B_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN15B_Init();
    EPD_2IN15B_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE *BlackImage, *RedImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_2IN15B_WIDTH % 8 == 0)? (EPD_2IN15B_WIDTH / 8 ): (EPD_2IN15B_WIDTH / 8 + 1)) * EPD_2IN15B_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    if((RedImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
	Paint_Clear(WHITE);
	Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
	Paint_Clear(WHITE);

#if 0   // show bmp
    printf("show bmp------------------------\r\n");
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/2.15__b.bmp", 0, 0);
    Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 0, WHITE);
    Paint_SelectImage(RedImage);
    GUI_ReadBmp("./pic/2.15__r.bmp", 0, 0);
    EPD_2IN15B_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
#endif

#if 1   // show image for array    
    Debug("show image for array\r\n");
    EPD_2IN15B_Display(gImage_2in15b_B, gImage_2in15b_R);
    DEV_Delay_ms(2000);
#endif

#if 1   // Drawing on the image
    printf("Drawing\r\n");

    //1.Draw black image
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_CN(130, 20, "΢ѩ����", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    //2.Draw red image
    Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(210, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_CN(130, 0,"���abc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);

    EPD_2IN15B_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);

#endif

    printf("Clear...\r\n");
    EPD_2IN15B_Clear();

    printf("Goto Sleep...\r\n");
    EPD_2IN15B_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return 0;
}
