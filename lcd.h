#ifndef LCD
#define LCD

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <limits.h>

#define LCD_LINE1 0
#define LCD_LINE2 1
#define LCD_CLR   2
#define ROW_WIDTH 8

static bool LCD_Active = false;
static bool LCD_Row = true;
volatile char LCD_Row1[ROW_WIDTH+1] = {};
volatile char LCD_Row2[ROW_WIDTH+1] = {};
static bool LCD_Continue = false;
static int  LCD_Row1N = 0;
static int  LCD_Row2N = 0;

static HANDLE hLCDMutex = NULL;

void LCD_setup();
void LCD_set(int setup);
void LCD_print(char* pole);
void LCD_refresh();

////////////////////////////////////////////
////////////////////////////////////////////

void LCD_setup() {
	LCD_Active = true;
	
	if (hLCDMutex == NULL) {
		hLCDMutex = CreateMutex(NULL, FALSE, NULL);
	}
}

void LCD_set(int setup) {
	WaitForSingleObject(hLCDMutex, INFINITE);
	switch (setup) {
	case LCD_LINE1:
		LCD_Row = true;
		LCD_Continue = false;
		LCD_Row1N = 0;
		LCD_Row2N = 0;
		break;
	case LCD_LINE2:
		LCD_Row = false;
		LCD_Continue = false;
		LCD_Row1N = 0;
		LCD_Row2N = 0;
		break;
	case LCD_CLR:
		memset(LCD_Row1, ' ', ROW_WIDTH);
		memset(LCD_Row2, ' ', ROW_WIDTH);
		LCD_Row1[ROW_WIDTH] = '\0';
		LCD_Row2[ROW_WIDTH] = '\0';
		LCD_Row1N = 0;
		LCD_Row2N = 0;
		LCD_refresh();
		break;
	default:
		break;
	}
	ReleaseMutex(hLCDMutex);
}

void LCD_print(char* pole) {
	if(!LCD_Active) return;
	WaitForSingleObject(hLCDMutex, INFINITE);
	
	if(!LCD_Continue) {
		LCD_Row1N = 0;
		LCD_Row2N = 0;
	}
	
	int n = 0;
	
	for(int i = (!LCD_Continue) ? 0 : ((LCD_Row) ? LCD_Row1N : LCD_Row2N); i < ROW_WIDTH; i++) {
		if(pole[n] == '\0') break;
		else  {
			(LCD_Row) ? (LCD_Row1[i] = pole[n]) : (LCD_Row2[i] = pole[n]);
			(LCD_Row) ? LCD_Row1N++ : LCD_Row2N++;
		}
		n++;
	}
	
	system("cls");
	printf("##########\n#%8s#\n#%8s#\n##########",LCD_Row1,LCD_Row2);
	
	LCD_Continue = true;
	ReleaseMutex(hLCDMutex);
}

void LCD_refresh() {
	WaitForSingleObject(hLCDMutex, INFINITE);
	system("cls");
	printf("##########\n#%8s#\n#%8s#\n##########",LCD_Row1,LCD_Row2);
	ReleaseMutex(hLCDMutex);
}

#endif
