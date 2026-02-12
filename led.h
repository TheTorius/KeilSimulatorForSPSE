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
