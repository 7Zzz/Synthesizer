/*
 * MCP_button.h
 *
 *  Created on: Jul 6, 2018
 *      Author: Roman
 */


#ifndef MCP_BUTTON_H_
#define MCP_BUTTON_H_

#include "global.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "MCP23017.h"

// settings
#define NUM_OF_BTNs          16


// defines
#define PRESSED   1
#define UNPRESSED 0

#define READ      1
#define NOREAD    0

#define INTERVAL  50  // debounce time interval

// button structure type
typedef struct {
	u8 btnNum;
	IO_PortTD port;
	IO_PinTD pin;
    u8 state;
    volatile u32 prevTime;
}BTN_TypeDef;


// variables
BTN_TypeDef buttons[NUM_OF_BTNs];   // all buttons
u8 buttonMsg[3];                    // message to send on state change

// functions
void MCP_Button_Init(BTN_TypeDef* b, u8 num, IO_PortTD port, IO_PinTD pin);
void MCP_Buttons_InitAll(void);     // for one MCP (TODO: for many)
void BTN_Read_All(u8 mcp_addr);

#endif /* BUTTON_H_ */
