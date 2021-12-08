/*
 * LCD.c
 *
 * Created: 11/29/2021 8:32:31 PM
 *  Author: Shaimaa K. El-Baklish
 */ 

#include "ATmega32A_Config.h"
#include "Std_Types.h"
#include "LCD.h"
#include "DIO.h"
#if LCD_USE_TIMERS_FOR_DELAY == 1
	#include "GPT.h"
#else
	#include <util/delay.h>
#endif

void LCD_Init(void) {
	/* Initialize GPT Module for Delays */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Init(gaStrGPT_Config);
	#endif
	
	/* Initialize DIO Pins */
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, DIO_OUTPUT);
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, DIO_OUTPUT);
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_OUTPUT);

#if LCD_8BIT_DATA_LENGTH == 1
	/* 8-bit data mode */
	DIO_SetPortDirection(LCD_DATA_PORT, DIO_OUTPUT);
#else
	/* 4-bit data mode */
	DIO_SetHighHalfPortDirection(LCD_DATA_PORT, DIO_OUTPUT);
	LCD_SendInstruction(LCD_RETURN_HOME);
#endif
	/* Send Instruction to set function (data length, number of lines and font) */
	LCD_SendInstruction(LCD_FUNCTION_SET);
	/* Turn on display and clear it */
	LCD_SendInstruction(LCD_DISPLAY_ON);
	LCD_SendInstruction(LCD_CLEAR_DISPLAY);
}

void LCD_SendInstruction(uint8 Instruction) {
	/* Select Instruction Register */
	DIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_INSTRUCTION_REG);
	/* Select Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_RW_PIN, LCD_WRITE_MODE);
	/* Minimum delay for address setup is 60 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* Enable Pulse for Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_HIGH);
	/* Minimum delay for Enable pulse is 450 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#if LCD_8BIT_DATA_LENGTH == 1
	/* 8 bit mode */
	DIO_WritePort(LCD_DATA_PORT, Instruction);
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#else
	/* 4 bit mode */
	/* Write Higher Half of Instruction */
	DIO_WriteHighHalfPort(LCD_DATA_PORT, (Instruction & 0xF0U));
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* bring down the enable pulse */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_LOW);
	/* Minimum delay for data hold is 10 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif

	/* Enable Pulse for Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_HIGH);
	/* Minimum delay for Enable pulse is 450 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* Write Lower Half of Instruction */
	DIO_WriteHighHalfPort(LCD_DATA_PORT, ((Instruction & 0x0FU)<<4));
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#endif
	/* bring down the enable pulse */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_LOW);
	/* Minimum delay for data hold is 10 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
}

void LCD_SelectRowColumn(uint8 Row, uint8 Column) {
	uint8 u8Local_AddressInstruction = 0x00U;
	switch (Row) {
		case 0:
			u8Local_AddressInstruction = (LCD_DDRAM_PREFIX | LCD_1ST_LINE_ADDRESS_PREFIX | Column);
			break;
		case 1:
			u8Local_AddressInstruction = (LCD_DDRAM_PREFIX | LCD_2ND_LINE_ADDRESS_PREFIX | Column);
			break;
		case 2:
			u8Local_AddressInstruction = (LCD_DDRAM_PREFIX | LCD_3RD_LINE_ADDRESS_PREFIX | Column);
			break;
		case 3:
			u8Local_AddressInstruction = (LCD_DDRAM_PREFIX | LCD_4th_LINE_ADDRESS_PREFIX | Column);
			break;
		default: break;
	}
	LCD_SendInstruction(u8Local_AddressInstruction);
}

void LCD_DisplayCharacter(char Data) {
	/* Select Instruction Register */
	DIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_DATA_REG);
	/* Select Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_RW_PIN, LCD_WRITE_MODE);
	/* Minimum delay for address setup is 60 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* Enable Pulse for Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_HIGH);
	/* Minimum delay for Enable pulse is 450 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#if LCD_8BIT_DATA_LENGTH == 1
	/* 8 bit mode */
	DIO_WritePort(LCD_DATA_PORT, Data);
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#else
	/* 4 bit mode */
	/* Write Higher Half of Instruction */
	DIO_WriteHighHalfPort(LCD_DATA_PORT, (Data & 0xF0U));
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* bring down the enable pulse */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_LOW);
	/* Minimum delay for data hold is 10 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif

	/* Enable Pulse for Write Operation */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_HIGH);
	/* Minimum delay for Enable pulse is 450 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
	/* Write Lower Half of Instruction */
	DIO_WriteHighHalfPort(LCD_DATA_PORT, ((Data & 0x0FU)<<4));
	/* Minimum delay for data setup is 195 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
#endif
	/* bring down the enable pulse */
	DIO_WritePin(LCD_CTRL_PORT, LCD_ENABLE_PIN, DIO_LOW);
	/* Minimum delay for data hold is 10 ns */
	#if LCD_USE_TIMERS_FOR_DELAY == 1
		GPT_Delay_us(&gaStrGPT_Config[0], 1);
	#else
		_delay_us(1);
	#endif
}

void LCD_DisplayString(char* Data) {
	while (*Data != '\0') {
		LCD_DisplayCharacter(*Data);
		Data++;
	}
}

void LCD_DisplayInteger(sint16 Data) {
	if (Data < 0) {
		LCD_DisplayCharacter('-');
		Data = -1 * Data;
	}
	uint8 u8Local_Digit = 0U;
	char str_reversed[5] = "";
	char* str_ptr = str_reversed;
	do {
		u8Local_Digit = Data%10;
		*str_ptr = (char)(48 + u8Local_Digit); /* 48 is the ASCII code of '0' */
		Data = Data/10;
		str_ptr++;
	} while (Data > 0);
	do {
		str_ptr--;
		LCD_DisplayCharacter(*str_ptr);
	} while (str_ptr != str_reversed);
}

void LCD_DisplayFloatingPointNumber(float32 Data) {
	/* Will display only 3 Decimal Places */
	uint16 IntegerPart = (uint16)Data;
	LCD_DisplayInteger(IntegerPart);
	LCD_DisplayCharacter('.');
	float32 DecimalPart = (Data - IntegerPart);
	uint8 Digit = 0;
	for (uint8 i = 0; i < 3; i++) {
		Digit = (uint8)(DecimalPart * 10.0);
		LCD_DisplayCharacter((char)(48+Digit));
		DecimalPart = ((DecimalPart*10.0) - Digit);
	}
}

void LCD_CreateSpecialCharacter(char* Pattern, uint8 CGRAM_Location) {
	/* Set CGRAM address. CGRAM stores each character sequence in 8 bytes. */
	LCD_SendInstruction((LCD_CGRAM_PREFIX + (CGRAM_Location*8U)));
	for (uint8 i = 0; i < 8; i++) {
		LCD_DisplayCharacter(Pattern[i]);
	}
}