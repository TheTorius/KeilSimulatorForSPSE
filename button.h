#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

static bool BTN_Active = false;

void BTN_setup() {
	BTN_Active = true;
}

int io_read(int a) {
	if(!BTN_Active) return 0;
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		return 1;
	}
	return 0;
}

#endif
