/*
 * GLCD.h
 *
 * Created: 12/7/2021 3:03:10 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef GLCD_H_
#define GLCD_H_

#include "ATmega32A_Config.h"
#include "DIO.h"

#include "GLCD_Pconfig.h"
#include "GLCD_Char_Patterns.h"

/************************************************************************/
/*				Data Types for Graphical LCD Module                     */
/************************************************************************/
typedef enum {
	GLCD_DISPLAY_OFF				= (0x3EU),
	GLCD_DISPLAY_ON					= (0x3FU),
	GLCD_SET_Y_ADDRESS_PREFIX		= (0x40U),
	GLCD_SET_X_ADDRESS_PREFIX		= (0xB8U),
	GLCD_SET_Z_ADDRESS_PREFIX		= (0xC0U)
}GLCD_CommandType;

typedef enum {
	GLCD_INSTRUCTION_REG,
	GLCD_DATA_REG
}GLCD_RegisterSelectType;

typedef enum {
	GLCD_NO_PAGES,
	GLCD_PAGE_0,
	GLCD_PAGE_1,
	GLCD_BOTH_PAGES
}GLCD_PageSelectType;

typedef enum {
	GLCD_WRITE_MODE,
	GLCD_READ_MODE
}GLCD_ReadWriteType;

/************************************************************************/
/*			Function Prototypes for Graphical LCD Module                */
/************************************************************************/
void GLCD_Init(void);
void GLCD_SelectPage(GLCD_PageSelectType Page);
void GLCD_SendInstruction(GLCD_CommandType Instruction);
void GLCD_SendData(uint8 Data);
void GLCD_Reset(void);
void GLCD_DisplayCharacter(char Data);
void GLCD_DisplayString(char* Data_Ptr);
void GLCD_DisplayInteger(sint32 Data);
void GLCD_DisplayFloatingPoint(float32 Data);
void GLCD_ClearDisplay(void);
void GLCD_GoToLine(uint8 Line);
void GLCD_DisplaySpecialPattern(uint64 Pattern);

/************************************************************************/
/*			Global Variables for Graphical LCD Module                   */
/************************************************************************/



#endif /* GLCD_H_ */