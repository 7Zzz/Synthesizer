#include "DAC.h"

void DACFunc(M_DACTypeDef *M) {

}

void Dac_Init_(M_DACTypeDef *module) {  // conflict_ fix_ (BSP)
	module->iBptr = &(module->iB[0]);
	module->iBcnt = 0;
	module->ld_blk = 0;
	module->snt_smp = 0;
	module->unld_smp = 0;
}
