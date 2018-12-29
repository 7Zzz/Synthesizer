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

#define RECORD_SELECTED 200,150,0
#define REPLAY_SELECTED 0,150,200
#define NOT_SELECTED 0,0,0

#define REPLAY_ON_COLOR 100,100,100
#define RECORD_ON_COLOR 50,50,50

#define ON  1
#define OFF 0
#define RECORD_BTN 0
#define REPLAY_BTN 1

#define LED_INTERVAL 400

u8 record_state;
u8 replay_state;
u8 selected_start;
u8 current_btn;
unsigned long previous_light;

typedef struct
{
	u8 state;
	u8 previous_pressing;
	u8 selected;
	u8 replaying;
} btn;

btn btns[NUM_OF_BTNs];

extern volatile uint32_t millis;

void sequencer_func(u8* i);

#endif /* SEQUENCER_H_ */
