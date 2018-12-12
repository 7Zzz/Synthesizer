#include "sequencer.h"

void save(u8 index, u8 value) {
	u8 pressing_index = btns[index].counter_pressing;
	if (btns[index].state == UNPRESSED && value == PRESSED) {
		btns[index].state = 1; // saving button state into structure btns
		time_periods[index][pressing_index] = millis; //save period into array
	} else if (btns[index].state == PRESSED && value == PRESSED)
		return;

	else if (btns[index].state == PRESSED && value == UNPRESSED) {
		time_periods[index][pressing_index] = abs(
				millis - time_periods[index][pressing_index]);
		btns[index].counter_pressing += 1; // adding one to pressing counter
	} else
		btns[index].state = 0; // saving button state into structure btns

}

void sequencer_func(u8* btn_states) {
	state = RECORD_OFF;
	if (RECORD_BTN == PRESSED) // RECORD_BTN it's record activator this is not necessarily a button
		state = RECORD_ON;

	if (state == RECORD_ON) {
		setWHOLEcolor(RECORD_OFF_COLOR); // turning led off
		DIG_LED_update();
		for (int i = 0; i < NUM_OF_BTNs; i++)
			btns[i].state = btn_states[i];
		for (int i = 0; i < NUM_OF_BTNs; i++)
			save(i, btns[i].state); // updating state and starting timer(so and stopping it)
		light();

}

void light(void) {
	HsvColor Hsv;
	for (int i = 0; i < NUM_OF_BTNs; i++) {
		if (btns[i].state == 1) {
			Hsv.h = 170;
			Hsv.s = 255;
			Hsv.v = 125;
			setLEDcolor(i, HsvToRgb(Hsv).r, HsvToRgb(Hsv).g, HsvToRgb(Hsv).b);
			DIG_LED_update();
			HAL_Delay(5);
		}
	}
}
