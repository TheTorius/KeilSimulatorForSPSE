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
