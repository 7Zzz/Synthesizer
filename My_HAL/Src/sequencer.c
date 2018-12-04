#include "sequencer.h"


int array[16] = {0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0};
void mode_selection(void)
{
	//TODO selection of mode, buttons combination maybe
	if (st_mode_selection == 1)
	{
		switch (state)
		{
			case st_metronome:
				mentronome();
				break;
		}
	}
}

void light(void)
{
	HsvColor Hsv;
	for(int i = 0; i<16; i++)
	{
		if(array[i] == 1)
		{
			Hsv.h = 170;
			Hsv.s = 255;
			Hsv.v = 125;
			setLEDcolor(i, HsvToRgb(Hsv).r, HsvToRgb(Hsv).g, HsvToRgb(Hsv).b);
			DIG_LED_update();
			HAL_Delay(5);
		}
	}
}


void metronome(void) {
	// get color from each button and save it
	// if any of buttons was pressed save current tick for it and turn it's led on
	// if any of pressed buttons was pressed again, calculate tick between pressing and save it and turn it's led off
	// return initial led for each item
}

