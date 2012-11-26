// --------------------------------------------------------------------
// Copyright (c) 2008 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------

#ifndef I2C_H_
#define I2C_H_

//////////////////////////////////////////////////////////////////////
#define A_GND	(1<<0)
#define A_VCC	(1<<1)
#define A_CS	(1<<3)
#define A_SDA	(1<<5)
#define A_SCL	(1<<7)

#define JP1_ADDR ((volatile char *) 0x10000060)
#define SET_DIRECTION(bits) (*(JP1_ADDR+4)=(bits))
#define SET_BIT(bit) ((*JP1_ADDR) |= (bit))
#define CLEAR_BIT(bit) ((*JP1_ADDR) &= ~(bit))
//0xAB
#define OUTMODE	(A_GND|A_VCC|A_CS|A_SDA|A_SCL)
// 0x8B
#define INMODE	(A_GND|A_VCC|A_CS|A_SCL)

#define SDA_DIR_IN(data_base)	SET_DIRECTION(INMODE)
#define SDA_DIR_OUT(data_base) 	SET_DIRECTION(OUTMODE) 
#define SDA_HIGH(data_base)		SET_BIT(A_SDA)
#define SDA_LOW(data_base)		CLEAR_BIT(A_SDA)
#define SDA_READ(data_base)		READ_BIT
#define SCL_HIGH(clk_base)		SET_BIT(A_SCL)
#define SCL_LOW(clk_base)		CLEAR_BIT(A_SCL)

//////////////////////////////////////////////////////////////////////

bool I2C_Write(alt_u32 clk_base, alt_u32 data_base, alt_8 DeviceAddr, alt_u8 ControlAddr, alt_u8 ControlData);
bool I2C_Read(alt_u32 clk_base, alt_u32 data_base, alt_8 DeviceAddr, alt_u8 ControlAddr, alt_u8 *pControlData);
bool I2C_MultipleRead(alt_u32 clk_base, alt_u32 data_base, alt_8 DeviceAddr, alt_u8 szData[], alt_u16 len);

#endif /*I2C_H_*/