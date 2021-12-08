/*
 * LCD.h
 *
 * Created: 11/29/2021 8:32:38 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Pconfig.h"

#define LCD_DDRAM_PREFIX				(0x80U)
#define LCD_CGRAM_PREFIX				(0x40U)
#define LCD_1ST_LINE_ADDRESS_PREFIX		(0x00U)
#define LCD_2ND_LINE_ADDRESS_PREFIX		(0x40U)
#define LCD_3RD_LINE_ADDRESS_PREFIX		(0x14U)
#define LCD_4th_LINE_ADDRESS_PREFIX		(0x54U)

/************************************************************************/
/*				Data Types for LCD Module                               */
/************************************************************************/
typedef enum {
	LCD_CLEAR_DISPLAY			= (0x01U),
	LCD_RETURN_HOME				= (0x02U),
	LCD_DISPLAY_OFF				= (0x08U),
	LCD_DISPLAY_ON				= ((0x0CU) | (LCD_CURSOR_MODE<<1) | (LCD_CURSOR_BLINK_MODE)),
	LCD_DISPLAY_SHIFT_RIGHT		= (0x1CU),
	LCD_DISPLAY_SHIFT_LEFT		= (0x18U),
	LCD_CURSOR_SHIFT_RIGHT		= (0x14U),
	LCD_CURSOR_SHIFT_LEFT		= (0x10U),
	LCD_FUNCTION_SET			= ((0x20U) | (LCD_8BIT_DATA_LENGTH<<4) | (LCD_MAX_LINES<<3) | (LCD_FONT_SIZE<<2))
}LCD_CommandType;

typedef enum {
	LCD_INSTRUCTION_REG,
	LCD_DATA_REG
}LCD_RegisterSelectType;

typedef enum {
	LCD_WRITE_MODE,
	LCD_READ_MODE
}LCD_ReadWriteType;

/************************************************************************/
/*				Function Prototypes for LCD Module                      */
/************************************************************************/
void LCD_Init(void);
void LCD_SendInstruction(uint8 Instruction);
void LCD_SelectRowColumn(uint8 Row, uint8 Column);
void LCD_DisplayCharacter(char Data);
void LCD_DisplayString(char* Data);
void LCD_DisplayInteger(sint16 Data);
void LCD_DisplayFloatingPointNumber(float32 Data);
void LCD_CreateSpecialCharacter(char* Pattern, uint8 CGRAM_Location);


/************************************************************************/
/*				External Variables for LCD Module                       */
/************************************************************************/


#endif /* LCD_H_ */