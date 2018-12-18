/*
 * sequencer.h
 *
 *  Created on: 20 ????. 2018 ?.
 *      Author: ??????
 */

#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include "MCP_button.h"
#include "dig_LED.h"
#include <stdlib.h>

#define SELECTED              0  , 255, 255
#define RECORD_ON_COLOR       255,   0,   0
#define RECORD_OFF_COLOR      0  ,   0,   0

#define RECORD_ON             1
#define RECORD_OFF            0

#define RECORD_BTN            1

#define MAX_VALUE_OF_PRESSING 5

u8 state;
unsigned long time_periods[NUM_OF_BTNs][MAX_VALUE_OF_PRESSING]; // playing interval of buttons(in millis)
uint32_t the_begining_millis;
uint32_t first_pause = 1000;

typedef struct
{
	u8 state;
	u8 counter_pressing;
	uint32_t tap_millis;
} btn;

btn btns[NUM_OF_BTNs];

extern volatile uint32_t millis;

void save(u8 index, u8 value);
void sequencer_func(u8* i);
void light(void);

#endif /* SEQUENCER_H_ */
