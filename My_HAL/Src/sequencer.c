#include "sequencer.h"

void mode_selection(void) {

	//TODO selection of mode, buttons combination maybe

	if (st_mode_selection == 1) {
		switch (state) {

		case "st_metronome":
			mentronome();
			break;

		}

	}
}

void metronome(void) {
	// get color from each button and save it
	// if any of buttons was pressed save current tick for it and turn it's led on
	// if any of pressed buttons was pressed again, calculate tick between pressing and save it and turn it's led off
	// return initial led for each item
}

