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
#include <stdlib.h>     //for abs func

#define SELECTED         0  , 255, 255
#define RECORD_ON_COLOR  255,   0,   0
#define RECORD_OFF_COLOR 0  ,   0,   0

#define RECORD_ON        1
#define RECORD_OFF       0

#define RECORD_BTN  15

u8 state;

void tumbler(u8);
void mode_selection(void);
void sequencer_func(void);
void light(void);

extern volatile uint32_t millis; // am I right?

#endif /* SEQUENCER_H_ */
