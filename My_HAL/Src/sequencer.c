#include "sequencer.h"

void sequencer_func(u8* btn_states) {
	if (btn_states[RECORD_BTN] == PRESSED) { //RECORD_BTN it's record activator this is not necessarily a button
		record_state = !record_state;
		setWHOLEcolor(NOT_SELECTED);
	}
	if (btn_states[REPLAY_BTN] == PRESSED) { //RECORD_BTN it's record activator this is not necessarily a button
		replay_state = !replay_state;
		previous_light = millis;
		current_btn = 0;
		setWHOLEcolor(NOT_SELECTED);
	}

	if (record_state == ON) {
		setWHOLEcolor(RECORD_ON_COLOR);
		for (int i = 0; i < NUM_OF_BTNs; i++)
			if (btn_states[i] == PRESSED
					&& millis - btns[i].previous_pressing > INTERVAL) {
				btns[i].state = UNPRESSED;
				btns[i].previous_pressing = millis;
				btns[i].selected = !btns[i].selected;
			}

		for (int i = 0; i < NUM_OF_BTNs; i++)
			if (btns[i].selected == 1) {
				setLEDcolor(i, RECORD_SELECTED);
			} else {
				setLEDcolor(i, NOT_SELECTED);
			}
	}
	if (replay_state == ON) {
		setWHOLEcolor(NOT_SELECTED);
		if (btns[current_btn].selected == 1) {
			if (millis - previous_light > LED_INTERVAL) {
				previous_light = millis;
				setLEDcolor(current_btn, REPLAY_SELECTED);
			}
		}
		for (int i = (current_btn+1); i < (NUM_OF_BTNs+(current_btn)); i++) {
			if (i > NUM_OF_BTNs)
				i = 0;
			if (btns[i].selected == 1 && i != current_btn) {
				current_btn = i;
				break;
			}
		}
	}
	DIG_LED_update();
}
