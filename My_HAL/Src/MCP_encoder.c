#include "MCP_encoder.h"

void ENC_Init(ENC_TypeDef** encs) {  //?
	for (u8 i = 0; i < NUM_OF_ENCODERS; i++) {
		encs[i]->encNum = i;
		encs[i]->pinAB = i % (NUM_OF_ENCODERS / 2);
		encs[i]->prevState = 0;
		encs[i]->prevTime = 0;
		encs[i]->status = TURN_NO;
	}
	mcpA1 = 0;
	mcpB1 = 0;
	mcpA2 = 0;
	mcpB2 = 0;
}


void ENC_Read_All(ENC_TypeDef** encs, u8 mcp1_addr, u8 mcp2_addr) {
	mcpA1 = MCP23017_ReadPort(PORTA, mcp1_addr);
	mcpB1 = MCP23017_ReadPort(PORTB, mcp1_addr);
	mcpA2 = MCP23017_ReadPort(PORTA, mcp2_addr);
	mcpB2 = MCP23017_ReadPort(PORTB, mcp2_addr);
	for (u8 i = 0; i < NUM_OF_ENCODERS; i++) {
		ENC_StatusTD status = TURN_NO;
		volatile u8 stateA;
		volatile u8 stateB;
		switch (i / 8) {
		case 0:
			stateA = (mcpA1 >> encs[i]->pinAB) & 0x01; // считываем состояние выхода А энкодера
			stateB = (mcpB1 >> encs[i]->pinAB) & 0x01; // считываем состояние выхода B энкодера
			break;
		case 1:
			stateA = (mcpA2 >> encs[i]->pinAB) & 0x01; // считываем состояние выхода А энкодера
			stateB = (mcpB2 >> encs[i]->pinAB) & 0x01; // считываем состояние выхода B энкодера
			break;
		}
		if ( (stateA == 0) && (encs[i]->prevState == 1) && (millis - encs[i]->prevTime > ENC_INTERVAL)) { // если состояние изменилось с положительного к нулю
			encs[i]->prevTime = millis;
			if (stateB == 1) {
				status = TURN_UP;
			} else {
				status = TURN_DN;
			}
		} else if (encs[i]->prevTime > millis) {
			encs[i]->prevTime = 0;
		}
		encs[i]->prevState = stateA;
		encs[i]->status = status;
	}
}
