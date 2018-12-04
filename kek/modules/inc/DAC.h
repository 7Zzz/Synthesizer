#include "global.h"

#ifndef DAC_H_
#define DAC_H_

#define IB_SIZE 10  // in blocks
#define HALF    (IB_SIZE * AUDIO_BLOCKSIZE / 2 )  // in smp

typedef struct {
	float  iB[IB_SIZE][AUDIO_BLOCKSIZE];                // input/outbut buffer
	float*  iBptr;             // input/outbut buffer load addr
	u16 iBcnt;             // input buffer counter (in samples)
	u16 unld_smp;          // index of sample to unload
	u16 ld_blk;            // index of block to load
	u16 snt_smp;           // sent samples counter
} M_DACTypeDef;

void DACFunc  (M_DACTypeDef *module);
void Dac_Init_(M_DACTypeDef *module);  // conflict_ fix_ (BSP)

#endif /* DAC_H_ */
