/*
 * LFO.c
 *
 *  Created on: 14 июл. 2018 г.
 *      Author: Дом
 */

#include "LFO.h"

void LFO_Init(M_LFO_TypeDef *M) {
	M->freq = 0;
	M->amp = 50;
	M->counter = 0;
	M->wasNoteOn = 0;
	M->prevMillis = 0;
}
void LFO_Update(M_LFO_TypeDef *M, float f, float a) {
	M->freq = f;
	M->amp = a;
}
u16 LFO_Func(M_LFO_TypeDef *M, u16 param, u8 isNoteOn) {
	M->counter = millis - M->prevMillis;
	if (isNoteOn) {
		if (!M->wasNoteOn) {
			M->counter = 0;
			M->wasNoteOn = 1;
			M->prevMillis = millis;
		}
		param = myAbs(
				param
						+ M->amp
								* arm_sin_f32(
										(float) M->counter * 3.1416 * M->freq
												/ (float) MAX ));
		if(param<15)
			param = 15;
	} else
		M->wasNoteOn = 0;
	return param;
}
float myAbs(float in) {
	if (in >= 0)
		return in;
	else
		return -in;
}
