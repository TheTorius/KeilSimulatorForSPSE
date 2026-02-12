/**
 * @file <nazev.c>
 * @author <Jmeno Prijmeni>
 */

// Zakomentovat, pokud RTOS nepoužíváme
#define RTOS

#include "stm32f4xx_kit.h"

#define KBD
char KBD_MAP[NUM_ROW * NUM_COL] = {
	'1','2','3',
	'4','5','6',
	'7','8','9',
	'.','2','P'
};

#ifdef RTOS
// Import knihoven, které potřebujete -> button.h, led.h...

#include "led.h"
#include "lcd.h"

int allLeds[8] = {
	LED_IN_0,
	LED_IN_1,
	LED_IN_2,
	LED_IN_3,
	LED_EX_0,
	LED_EX_1,
	LED_EX_2,
	LED_EX_3
};

OS_TID id_task[N];  // Nevytvarejte nove OS_TID jen pridavejte do tohoto

__task Task0(null) {
	for(;;){
		LCD_set(LCD_CLR);
		LCD_set(LCD_LINE2);
		LCD_print("World");
		for(int i = 0; i < 4; i++) {
			io_set(allLeds[i],1);
			io_set(allLeds[i+4],1);
			delay_ms(150);
		}
		
		delay_ms(500);
		LCD_set(LCD_CLR);
		for(int i = 0; i < 4; i++) {
			io_set(allLeds[i],0);
			io_set(allLeds[i+4],0);
			delay_ms(150);
		}
		LCD_set(LCD_LINE1);
		LCD_print("Hello");
		delay_ms(500);
	}
}

__task setup(null) {
	// TODO: setup
	
	LED_setup();
	LCD_setup();
	
	id_task[0] = os_tsk_create(Task0, 0);
	
	wait; // NEMAZAT
}

int main() {
	os_sys_init(setup);
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Bez RTOS /////////////////////////////////////////////////

#ifndef RTOS

// import knihoven (napr. button.h, lcd.h...)

void func() {
	
}

__BOARD_SETUP setup() {
	// TODO: setup
}

int main() {
	
}
#endif
