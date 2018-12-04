#include "wire.h"

void WireFunc(M_WireTypeDef *M) {
	for (int i = 0; i < AUDIO_BLOCKSIZE; i++)
		M->addrDst[i] += M->addrSrc[i]; // ”казательЌа—труктуру->»м€Ёлемента  -  операци€ косвенного выбора элемента структурного объекта, адресуемого указателем
}

void Wire_Init(M_WireTypeDef *M) {  // assign default addresses
	M->addrDst = 0;
	M->addrSrc = 0;
}
