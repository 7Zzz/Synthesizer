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
	setWHOLEcolor(0, 0, 0);
	DIG_LED_update();
	u8 turn_state = BTN_Read_All(MCP23017_ADDR(15));
	while (turn_state) {
		if (buttons[15].state) {
			turn_state = !turn_state;
			break;
		} else {
			for (int i = 0; i <= NUM_OF_BTNs; i++) {
				if (buttons[i].state == 1) {
					if (leds_on[i] == 1) {
						leds_on[i] = 0;
						setLEDcolor(i, COLOR_ON);
					} else {
						leds_on[i] = 1;
						setLEDcolor(i, COLOR_OFF);
					}
					DIG_LED_update();
				}
			}
		}
//		setWHOLEcolor(r, g, b);
		DIG_LED_update();
	}
}

