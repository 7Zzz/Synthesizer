#include "sequencer.h"

void sequencer_func(u8* btn_states) {
	if (btn_states[RECORD_BTN] == PRESSED) //RECORD_BTN it's record activator this is not necessarily a button
		record_state = !record_state;
	if (btn_states[REPLAY_BTN] == PRESSED){ //RECORD_BTN it's record activator this is not necessarily a button
		replay_state = !replay_state;
		replay_start = millis;
	}

	if (record_state == ON) {

		for (int i = 0; i < NUM_OF_BTNs; i++)
			if (btn_states[i] == PRESSED
					&& millis - btns[i].previous_pressing > INTERVAL) {
				btns[i].state = UNPRESSED;
				btns[i].previous_pressing = millis;
			}

		for (int i = 0; i < NUM_OF_BTNs; i++)
			if (btns[i].state == 1) {
				setLEDcolor(i, SELECTED);
				btns[i].selected_start = millis;
			} else {
				setLEDcolor(i, NOT_SELECTED);
			}
	}
	if(replay_state == ON)
	{
		for (int i = 0; i < NUM_OF_BTNs; i++) {
			if (millis - replay_start > btns[i].selected_start) {
				setLEDcolor(i, SELECTED);
			}
		}
	}
	DIG_LED_update();
}

