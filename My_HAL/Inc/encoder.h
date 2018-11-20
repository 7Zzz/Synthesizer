//#ifndef ENCODER_H_
//#define ENCODER_H_
//
//#include "global.h"
//#include "MCP23017.h"
//
//// settings
//#define ENC_NUM              1
//#define ENC_MCP_PINA         PIN6
//#define ENC_MCP_PINA_PORT    PORTA
//#define ENC_MCP_PINB         PIN7
//#define ENC_MCP_PINB_PORT    PORTA
//
//#define INTERVAL  50
//
//
//
//// defines
//
//
//
//
//
//// types
//typedef enum statuses {
//	TURN_NO = 0, TURN_DN, TURN_UP
//}ENC_StatusTD;
//
//typedef struct {
//	IO_PortTD port; //?
//    u16 pinA;
//    u16 pinB;
//    u8 prevState;
//    u32 prevTime;
//    ENC_StatusTD status;
//}ENC_TypeDef;
//
//
//
//
//
//void ENC_Init(ENC_TypeDef* enc, IO_PortTD mcp_port, IO_PinTD mcp_pinA, IO_PinTD mcp_pinB);
//ENC_StatusTD ENC_Read(ENC_TypeDef* enc);
//
//#endif /* ENCODER_H_ */
