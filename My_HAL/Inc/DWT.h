/*
 * DWT.h
 *
 *  Created on: Oct 20, 2018
 *      Author: Roman
 */

#ifndef DWT_H_
#define DWT_H_

#include "core_cm3.h"    // link the appropriate core

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

#define _DWT_INIT_  { SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; \
	                  DWT_CYCCNT = 0;                            }
#define _DWT_START_   DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;
#define _DWT_STOP_    DWT_CONTROL &= ~DWT_CTRL_CYCCNTENA_Msk;
#define _DWT_GET_     DWT_CYCCNT

#endif /* DWT_H_ */
