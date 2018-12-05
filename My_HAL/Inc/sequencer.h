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
//TODO include of hcv color func

#define SELECTION_OFF   0,   0, 255
#define SELECTION_ON    0, 255,   0
#define METRONOME_ON  255,   0,   0

//define IT IS CONST, THEY MUST BE UPPER CASE not st_metronome, but ST_METRONOME, del it if you read it
#define ST_METRONOME 0

u8 st_mode_selection;
u8 state;

void tumbler(u8);
void mode_selection(void);
void metornome(void);
void led(void);

#endif /* SEQUENCER_H_ */
