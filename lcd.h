#ifndef LCD
#define LCD

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
