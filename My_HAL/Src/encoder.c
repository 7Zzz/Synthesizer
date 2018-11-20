//#include "encoder.h"
//
//void ENC_Init(ENC_TypeDef* enc, IO_PortTD mcp_port, IO_PinTD mcp_pinA,
//		IO_PinTD mcp_pinB) {
//	enc->pinA = mcp_pinA;
//	enc->pinB = mcp_pinB;
//	enc->port = mcp_port;
//	enc->prevState = 0;
//	enc->prevTime = 0;
//
//}
//
//ENC_StatusTD ENC_Read(ENC_TypeDef* enc) {
//	ENC_StatusTD status = TURN_NO;
//	volatile u8 tmp1 = MCP23017_ReadPort(PORTA);
//	volatile uint8_t stateA = (tmp1 >> enc->pinA) & 0x01; // считываем состо€ние выхода ј энкодера
//	volatile uint8_t stateB = (tmp1 >> enc->pinB) & 0x01; // считываем состо€ние выхода B энкодера
//	u8 tmp = (stateA == 0)  && (enc->prevState == 1);
//	if (tmp && (millis - enc->prevTime > 40)) { // если состо€ние изменилось с положительного к нулю
//		enc->prevTime = millis;
//		if (stateB == 1) {
//			status = TURN_UP;
//		} else {
//			status = TURN_DN;
//		}
//	} else if (enc->prevTime > millis) {
//		enc->prevTime = 0;
//	}
//	enc->prevState = stateA;
//	return status;
//}
