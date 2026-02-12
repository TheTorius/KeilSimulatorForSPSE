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

#ifndef STM32F4XX_KIT_H
#define STM32F4XX_KIT_H

#ifndef USER_BUTTON
#define USER_BUTTON 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define __task DWORD WINAPI
#define null LPVOID lpParam

__task raylibMain(null);

#define OS_TID HANDLE
#define os_sys_init(setup) HANDLE mainTsks[2]; mainTsks[0] = os_tsk_create(setup,0); mainTsks[1] = os_tsk_create(raylibMain,0); WaitForMultipleObjects(2, mainTsks, TRUE, INFINITE);
#define N 32
#define wait Sleep(INFINITE);

#define NUM_ROW 4
#define NUM_COL 3

void delay_ms(int ms) {
	Sleep(ms);
}

HANDLE os_tsk_create(LPTHREAD_START_ROUTINE taskFunction, int priority) {
	HANDLE hThread = CreateThread(NULL, 0, taskFunction, NULL, 0, NULL);
	
	if (hThread == NULL) {
		printf("CHYBA: Nepodarilo se vytvorit vlakno!\n");
	}
	
	return hThread;
}

void os_tsk_delete(HANDLE task_id) {
	TerminateThread(task_id, 0);
	CloseHandle(task_id); 
}

void os_tsk_delete_self() {
	ExitThread(0);
}

#endif
