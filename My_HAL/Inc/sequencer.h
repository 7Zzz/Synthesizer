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

#define SELECTION_ON    0, 255,   0
#define METRONOME_ON  255,   0,   0
#define st_metronome 0

u8 st_mode_selection;
u8 state;

void mode_selection(void);
void metornome(void);

#endif /* SEQUENCER_H_ */
