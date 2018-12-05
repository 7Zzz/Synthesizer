#include "sequencer.h"

// { state, interval }
int array[NUM_OF_BTNs][NUM_OF_BTNs] =
{
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 },
{ 0, 0 } };

void save(u8 index, u8 value)
{
	if (array[index][0] == UNPRESSED && value == PRESSED)
	{
		array[index][0] = 1; // save state
		array[index][1] = millis; //save period into array, but we haven't got array now :(
	}
	else if (array[index][0] == PRESSED && value == PRESSED)
		return;

	else if (array[index][0] == PRESSED && value == UNPRESSED)
		array[index][1] = abs(millis - array[index][1]);

	else
		array[index][0] = 0; // save state

}

void sequencer_func(void)
{
	state = RECORD_OFF;
	if (RECORD_BTN == PRESSED) // RECORD_BTN it's record activator this is not necessarily a button
		state = RECORD_ON;

	if (state == RECORD_ON)
	{
		setWHOLEcolor(RECORD_OFF_COLOR); // turning led off
		DIG_LED_update();

		int *buttons = BTN_Read_All(MCP23017_ADDR(3)); // reading all buttons

		for (int i = 0; i < NUM_OF_BTNs; i++)
			save(i, buttons[i]); // updating state and starting timer(so and stopping it)
	}
	else
	{
		light();
	}

}

void light(void)
{
	HsvColor Hsv;
	for (int i = 0; i < NUM_OF_BTNs; i++)
	{
		if (array[i][0] == 1)
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
