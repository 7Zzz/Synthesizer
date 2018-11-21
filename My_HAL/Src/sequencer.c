/*
 * sequencer.c
 *
 *  Created on: 20 ????. 2018 ?.
 *      Author: ??????
 */

#include "sequencer.h"

int leds_on[NUM_OF_BTNs];

void memorize_buttons(void) {  // metronome
	//function to memorize the pressed buttons and highlight them
	//u8 r, g, b = LEDbuffer[0]; // сделать возврат цвета после выполнения функции
	setWHOLEcolor(COLOR_OFF); // обнулить все цвета на клавиатуре, на цвет не выбрано
	DIG_LED_update();
	buttons = BTN_Read_All(MCP23017_ADDR(3));
	u8 turn_state = buttons[15].state;
	while (turn_state) {
		buttons = BTN_Read_All(MCP23017_ADDR(3));
		turn_state = buttons[15].state;
		if (buttons[15].state) {
			turn_state = !turn_state;
			break;
		} else {
			for (int i = 0; i <= NUM_OF_BTNs; i++) {
				if (buttons[i].state == 1) {
					if (leds_on[i] == 0) {
						leds_on[i] = 1;
						setLEDcolor(i, COLOR_ON);
					} else {
						leds_on[i] = 0;
						setLEDcolor(i, COLOR_OFF);
					}
					DIG_LED_update();
				}
			}
		}
//		setWHOLEcolor(r, g, b); // вернуть значения до начала функции
		DIG_LED_update();
	}
}

