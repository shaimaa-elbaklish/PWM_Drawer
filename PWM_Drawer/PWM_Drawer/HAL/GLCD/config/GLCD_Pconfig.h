/*
 * GLCD_Pconfig.h
 *
 * Created: 12/7/2021 3:03:02 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef GLCD_PCONFIG_H_
#define GLCD_PCONFIG_H_

/************************************************************************/
/*					Graphical LCD Characteristics                       */
/************************************************************************/
#define GLCD_MAX_LINES							(8U)
#define GLCD_MAX_LINE_PIXEL_WIDTH				(128U)
#define GLCD_MAX_PAGE_PIXEL_WIDTH				(64U)

/************************************************************************/
/*					Graphical LCD Configurations                        */
/************************************************************************/
#define GLCD_USE_TIMERS_FOR_DELAY				(0U)	/* 1 to use GPT for delay, 0 to use delay.h */

/************************************************************************/
/*					Graphical LCD Connections                           */
/************************************************************************/
#define GLCD_CTRL_PORT							(DIO_PORT_B)
#define GLCD_ENABLE_PIN							(DIO_PIN_0)
#define GLCD_RW_PIN								(DIO_PIN_1)
#define GLCD_RS_PIN								(DIO_PIN_2)
#define GLCD_PAGE_SELECT_PIN_1					(DIO_PIN_4)
#define GLCD_PAGE_SELECT_PIN_2					(DIO_PIN_5)
#define GLCD_RESET_PIN							(DIO_PIN_6)


#define GLCD_DATA_PORT							(DIO_PORT_A)
#define GLCD_DATA_D0_PIN						(DIO_PIN_0)
#define GLCD_DATA_D1_PIN						(DIO_PIN_1)
#define GLCD_DATA_D2_PIN						(DIO_PIN_2)
#define GLCD_DATA_D3_PIN						(DIO_PIN_3)
#define GLCD_DATA_D4_PIN						(DIO_PIN_4)
#define GLCD_DATA_D5_PIN						(DIO_PIN_5)
#define GLCD_DATA_D6_PIN						(DIO_PIN_6)
#define GLCD_DATA_D7_PIN						(DIO_PIN_7)



#endif /* GLCD_PCONFIG_H_ */