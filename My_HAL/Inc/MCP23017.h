///*
//  MCP23017.h
// *
// *  Created on: Jul 8, 2018
// *      Author: Roman
// */
#include "i2c.h"
#include "global.h"

#ifndef MCP23017_H_
#define MCP23017_H_

// settings
#define MCP_I2C_HANDLER  hi2c2
#define MCP_TIMEOUT      1

// internal address configuration select
#define MCP23017_IOCON_SAME_BANK        // addresses for each port are sequential
//#define MCP23017_IOCON_DIFFERENT_BANKS  // addresses for each port are split in 2 banks

// init configuration select
//#define MCP23017_DEFAULT_OUT_CONFIG
#define MCP23017_DEFAULT_IN_CONFIG


// defines
#ifdef MCP23017_IOCON_SAME_BANK
#define MCP23017_MEM_ADDR_SIZE  I2C_MEMADD_SIZE_8BIT

#define MCP23017_ADDR(x)           (0x20 | x)     // TODO: hw_addr to struct
                //#define MCP23017_ADDR_0           (0x20 | MCP23017_HW_ADDR_0)
                //#define MCP23017_ADDR_1           (0x20 | MCP23017_HW_ADDR_1)
                //#define MCP23017_ADDR_2           (0x20 | MCP23017_HW_ADDR_2)
                //#define MCP23017_ADDR_3           (0x20 | MCP23017_HW_ADDR_3)
                //#define MCP23017_ADDR_4           (0x20 | MCP23017_HW_ADDR_4)

#define MCP_WRITE               0
#define MCP_READ                1
                //#define MCP23017_OPCODE_W       ( (MCP23017_ADDR << 1) | MCP_WRITE )
                //#define MCP23017_OPCODE_R       ( (MCP23017_ADDR << 1) | MCP_READ )


// registers
#define MCP23017_IODIRA         0x00
#define MCP23017_IPOLA          0x02
#define MCP23017_GPINTENA       0x04
#define MCP23017_DEFVALA        0x06
#define MCP23017_INTCONA        0x08
#define MCP23017_IOCONA         0x0A
#define MCP23017_GPPUA          0x0C
#define MCP23017_INTFA          0x0E
#define MCP23017_INTCAPA        0x10
#define MCP23017_GPIOA          0x12
#define MCP23017_OLATA          0x14

#define MCP23017_IODIRB         0x01
#define MCP23017_IPOLB          0x03
#define MCP23017_GPINTENB       0x05
#define MCP23017_DEFVALB        0x07
#define MCP23017_INTCONB        0x09
#define MCP23017_IOCONB         0x0B
#define MCP23017_GPPUB          0x0D
#define MCP23017_INTFB          0x0F
#define MCP23017_INTCAPB        0x11
#define MCP23017_GPIOB          0x13
#define MCP23017_OLATB          0x15

#define MCP23017_INT_ERR        255 //?
#endif

#ifdef MCP23017_IOCON_DIFFERENT_BANKS
#define MCP23017_IODIRA         0x00
#define MCP23017_IPOLA          0x01
#define MCP23017_GPINTENA       0x02
#define MCP23017_DEFVALA        0x03
#define MCP23017_INTCONA        0x04
#define MCP23017_IOCONA         0x05
#define MCP23017_GPPUA          0x06
#define MCP23017_INTFA          0x07
#define MCP23017_INTCAPA        0x08
#define MCP23017_GPIOA          0x09
#define MCP23017_OLATA          0x0A

#define MCP23017_IODIRB         0x10
#define MCP23017_IPOLB          0x11
#define MCP23017_GPINTENB       0x12
#define MCP23017_DEFVALB        0x13
#define MCP23017_INTCONB        0x14
#define MCP23017_IOCONB         0x15
#define MCP23017_GPPUB          0x16
#define MCP23017_INTFB          0x17
#define MCP23017_INTCAPB        0x18
#define MCP23017_GPIOB          0x19
#define MCP23017_OLATB          0x1A

#define MCP23017_INT_ERR        255 //?
#endif


// pins
typedef enum IO_Pins { PIN1 = 0,  PIN2,  PIN3,  PIN4,
                       PIN5,      PIN6,  PIN7,  PIN8,
                        }IO_PinTD;

// ports
typedef enum IO_Ports { PORTA = 0,  PORTB }IO_PortTD;

// direction
#define MCP_OUT    0
#define MCP_IN     1

// pull-up
#define MCP_UP     1
#define MCP_NOUP   0

// polarity
#define ACT_LO 1
#define ACT_HI 0

// macro



// vars
u8 MCP_Astate;  //   TODO: to struct
u8 MCP_Bstate;  // Port A and Port B states (for 1 MCP)


// funcs
void MCP23017_Init(void);
u8 MCP23017_ReadPort(u8 mcp_addr, IO_PortTD port);
                //void MCP_SpinA(u8* state, IO_PinTD pin);
                //void MCP_RpinA(u8* state, IO_PinTD pin);
                //void MCP_TpinA(u8* state, IO_PinTD pin);
                //void MCP_SpinB(u8* state, IO_PinTD pin);
                //void MCP_RpinB(u8* state, IO_PinTD pin);
                //void MCP_TpinB(u8* state, IO_PinTD pin);

                //void MCP_LED_Animation(u16 delay);

#endif /* MCP23017_H_ */
