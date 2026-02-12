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
