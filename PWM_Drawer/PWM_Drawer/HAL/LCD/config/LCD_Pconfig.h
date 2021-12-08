/*
 * LCD_Pconfig.h
 *
 * Created: 11/29/2021 8:32:50 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef LCD_PCONFIG_H_
#define LCD_PCONFIG_H_

/************************************************************************/
/*							LCD Characteristics                         */
/************************************************************************/
#define LCD_NUM_LINES					(4U)
#define LCD_MAX_LINE_WIDTH				(20U)

/************************************************************************/
/*							LCD Configurations                          */
/************************************************************************/
#define LCD_8BIT_DATA_LENGTH			(0U)	/* 1 for 8 bit mode and 0 for 4 bit mode */
#define LCD_MAX_LINES					(1U)	/* 1 for 2/4 lines and 0 for 1/2 line(s) */
#define LCD_FONT_SIZE					(0U)	/* 1 for big font (5x10) and 0 for small font (5x8) */

#define LCD_CURSOR_MODE					(1U)	/* 1 for ON and 0 for OFF */
#define LCD_CURSOR_BLINK_MODE			(1U)	/* 1 for Blinking Cursor and 0 to turn off blinking */

#define LCD_USE_TIMERS_FOR_DELAY		(0U)	/* 1 to use GPT Module for delays and 0 to use delay.h */

/************************************************************************/
/*							LCD Connections                             */
/************************************************************************/
#define LCD_CTRL_PORT					(DIO_PORT_B)
#define LCD_RS_PIN						(DIO_PIN_1)
#define LCD_RW_PIN						(DIO_PIN_2)
#define LCD_ENABLE_PIN					(DIO_PIN_0)

#define LCD_DATA_PORT					(DIO_PORT_A)
#define LCD_DATA_D4_PIN					(DIO_PIN_4)
#define LCD_DATA_D5_PIN					(DIO_PIN_5)
#define LCD_DATA_D6_PIN					(DIO_PIN_6)
#define LCD_DATA_D7_PIN					(DIO_PIN_7)

/************************************************************************/
/*				Some Compiler Checks on Configurations                  */
/************************************************************************/
#if LCD_MAX_LINES == 1 && LCD_FONT_SIZE == 1
	#pragma GCC error "You can NOT use big font (5x10) in the 2-line mode!!"
#endif


#endif /* LCD_PCONFIG_H_ */