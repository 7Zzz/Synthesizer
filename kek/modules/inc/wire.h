#ifndef WIRE_H_
#define WIRE_H_

#include "global.h"

typedef struct {
	float *addrSrc;
	float *addrDst;
} M_WireTypeDef;

void WireFunc (M_WireTypeDef *module);  // load block from source addr to dest addr
void Wire_Init(M_WireTypeDef *module);  // 0 addresses by default and if(addr == 0) {no load is performed}

#endif /* WIRE_H_ */
