///*
// * button.c
// *
// *  Created on: Jul 6, 2018
// *      Author: Roman
// */
#include "MCP_button.h"
//#include "reg.h"  // for test ?

void MCP_Button_Init(BTN_TypeDef* b, u8 num, IO_PortTD port, IO_PinTD pin) {
	b->btnNum = num;
	b->port = port;
	b->pin = pin;
	b->state = UNPRESSED;
	b->prevTime = 0;
}

void MCP_Buttons_InitAll(void) {
	for (u8 i = 0; i < NUM_OF_BTNs; i++) {
		MCP_Button_Init(&buttons[i], i, i / 8, i % 8); // auto-assign num, port and pin
	}
	buttonMsg[0] = 'b';
	buttonMsg[1] = 0;
	buttonMsg[2] = UNPRESSED;
}

int* BTN_Read_All(u8 mcp_addr) {
	int btn_pressed[NUM_OF_BTNs];

	u8 mcpA = MCP23017_ReadPort(mcp_addr, PORTA);
	u8 mcpB = MCP23017_ReadPort(mcp_addr, PORTB);
	u8 read = 0;
	for (u8 i = 0; i < NUM_OF_BTNs; i++) {
		switch (i / 8) {
		case 0:
			read = (mcpA >> buttons[i].pin) & 0x01; //вроде дает двоичный код c 1-8 кнопку который надо передать расширителю портов
			break;
		case 1:
			read = (mcpB >> buttons[i].pin) & 0x01; //вроде дает двоичный код c 8-16 кнопку который надо передать расширителю портов
			break;
		}
		if (millis - buttons[i].prevTime > INTERVAL) {
			if (read && buttons[i].state == UNPRESSED) {
				buttons[i].state = PRESSED;
				buttons[i].prevTime = millis;
				buttonMsg[1] = i;              // fill msg - button number
				buttonMsg[2] = PRESSED; 	   // button state
				//for(u8 k = 0; k<3; k++)
				//Reg_Send(&buttonMsg[k]);     // action  ?
				if (btn_pressed[i] == 0)
					btn_pressed[i] = 1;
				else
					btn_pressed[i] = 0;

			} else if (!read && buttons[i].state == PRESSED) {
				buttons[i].state = UNPRESSED;
				buttons[i].prevTime = millis;
				buttonMsg[1] = i;                  // fill msg - button number
				buttonMsg[2] = UNPRESSED;          // button state
				//for (u8 k = 0; k < 3; k++)
				//Reg_Send(&buttonMsg[k]);     // action   ?
			}
		}
		if (buttons[i].prevTime > millis)
			buttons[i].prevTime = 0;
	} return btn_pressed;
}

// TODO:
//u8 BTN_ReadPush(BTN_TypeDef b) {
//
//	return 0;
//}

