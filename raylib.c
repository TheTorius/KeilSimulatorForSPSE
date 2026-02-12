/*!
* Project Name: Keil STM32F407VG Simulator - SPSE HAVIROV
* Author: Bc. Lukáš Horák <horak.lucas@seznam.cz>
* License: MIT
* Copyright (c) 2025 Lukáš Horák
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/


#include <raylib.h>
#include <string.h>

#define NUM_FRAMES_PER_LINE     5
#define NUM_LINES               5

extern int leds;

#define ROW_WIDTH 8

extern volatile char LCD_Row1[ROW_WIDTH + 1]; 
extern volatile char LCD_Row2[ROW_WIDTH + 1];

int raylibMain(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

	SetTraceLogLevel(LOG_ERROR);
    InitWindow(screenWidth, screenHeight, "Keil STM32F407VG Simulator - SPSE HAVIROV");

	Texture2D ARM = LoadTexture(".\\stm32.png");
	ARM.width = 300;
	ARM.height = 450;
	
    SetTargetFPS(240);

    while (!WindowShouldClose())    
    {
		
        BeginDrawing();

            ClearBackground(BLACK);
		
			DrawTexture(ARM,0,0,WHITE);
			
			if(leds & 1) {DrawRectangle(122,285,20,20,ORANGE);}
			if(leds & 2) {DrawRectangle(142,265,20,20,GREEN);}
			if(leds & 4) {DrawRectangle(162,285,20,20,RED);}
			if(leds & 8) {DrawRectangle(142,305,20,20,BLUE);}
			if(leds & 16) {DrawRectangle(330,305,20,20,RED);}
			if(leds & 32) {DrawRectangle(360,305,20,20,RED);}
			if(leds & 64) {DrawRectangle(390,305,20,20,RED);}
			if(leds & 128) {DrawRectangle(420,305,20,20,RED);}

			DrawText((const char*)LCD_Row1,350,150,25,WHITE);
			DrawLine(350,174,450,174,WHITE);
			DrawText((const char*)LCD_Row2,350,175,25,WHITE);
			

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------


    CloseAudioDevice();

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
