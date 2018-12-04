/*
 * LFOfld.c
 *
 *  Created on: 14 èşë. 2018 ã.
 *      Author: Äîì
 */

#include "LFOfld.h"

void LFOfld_Init(M_LFOfld_TypeDef *M) {
	M->freq = 0;
	M->amp = 3;
	M->counter = 0;
	M->wasNoteOn = 0;
	M->prevMillis = 0;
}
void LFOfld_Update(M_LFOfld_TypeDef *M, float f, float a) {
	M->freq = f;
	M->amp = a;
}
float LFOfld_Func(M_LFOfld_TypeDef *M, float param, u8 isNoteOn) {
	M->counter = millis - M->prevMillis;
	if (isNoteOn) {
		if (!M->wasNoteOn) {
			M->counter = 0;
			M->wasNoteOn = 1;
			M->prevMillis = millis;
		}

		param = myAbss(
				param
						+ M->amp
								* arm_sin_f32(
										(float) M->counter * 3.1416*M->freq
												/ (float) MAXs));
	} else
		M->wasNoteOn = 0;
	return param;
}
float myAbss(float in) {
	if (in >= 0)
		return in;
	else
		return -in;
}
