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

#ifndef KEYPAD
#define KEYPAD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

static bool KBD_Active = false;

void KBD_setup() {
	KBD_Active = true;
}

char KBD_read() {
	if(!KBD_Active) return 0;
	#ifdef KBD
		for (int vk = 0x08; vk <= 0xFE; vk++) { 
			if (GetAsyncKeyState(vk) & 0x8000) { 
				for(int i = 0; i < NUM_ROW * NUM_COL; i++) {
					if(KBD_MAP[i] == vk) return vk;
				}
			}
		}
	#endif	
	return 0;
}

#endif
