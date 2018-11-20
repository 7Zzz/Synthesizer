#ifndef MCP_ENCODER_H_
#define MCP_ENCODER_H_

#include "global.h"
#include "MCP23017.h"


#define ENC_INTERVAL 40

// defines
#define NUM_OF_ENCODERS 16

// types
typedef enum statuses {
	TURN_NO = 0, TURN_DN, TURN_UP
} ENC_StatusTD;

typedef struct {
	u8 encNum;
	IO_PinTD pinAB;
	ENC_StatusTD status;
	u8 prevState;
	u32 prevTime;
} ENC_TypeDef;

// vars
ENC_TypeDef encoders[NUM_OF_ENCODERS];
u8 mcpA1;
u8 mcpB1;
u8 mcpA2;
u8 mcpB2;

void ENC_Init(ENC_TypeDef** encs);
void ENC_Read_All(ENC_TypeDef** encs, u8 mcp1_addr, u8 mcp2_addr);


#endif /* ENCODER_H_ */
