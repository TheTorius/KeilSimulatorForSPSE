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

#ifndef LED
#define LED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define const_enum_pin enum

const_enum_pin ledky {
	LED_IN_0 = 0,
	LED_IN_1 = 1,
	LED_IN_2 = 2,
	LED_IN_3 = 3,
	LED_EX_0 = 4,
	LED_EX_1 = 5,
	LED_EX_2 = 6,
	LED_EX_3 = 7
}ledky;

volatile int leds = 0xF0;
static bool LED_Active = false;

void io_set(int led, bool isActive) {
	if(LED_Active) {
		if(led > 3) {
			if(isActive) leds &= ~(1 << led);
			else leds |= (1 << led);
		} else {
			if(isActive) leds |= (1 << led);
			else leds &= ~(1 << led);
		}	
	}
}

void LED_setup() {
	LED_Active = true;
}

#endif
