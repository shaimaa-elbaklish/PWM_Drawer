/*
 * ATmega32A_Config.h
 *
 * Created: 11/29/2021 4:15:27 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef ATMEGA32A_CONFIG_H_
#define ATMEGA32A_CONFIG_H_

#include "Std_Types.h"

/************************************************************************/
/*			CPU Frequency (Hardware oscillator, e.g. crystal)           */
/************************************************************************/
#define F_CPU								(16000000UL)

/************************************************************************/
/*				Digital Input Output Module -  SFR Addresses            */
/************************************************************************/
#define PORTA_OUT_REG						((volatile uint8*)0x3BU)
#define PORTA_DIR_REG						((volatile uint8*)0x3AU)
#define PORTA_INP_REG						((volatile uint8*)0x39U)

#define PORTB_OUT_REG						((volatile uint8*)0x38U)
#define PORTB_DIR_REG						((volatile uint8*)0x37U)
#define PORTB_INP_REG						((volatile uint8*)0x36U)

#define PORTC_OUT_REG						((volatile uint8*)0x35U)
#define PORTC_DIR_REG						((volatile uint8*)0x34U)
#define PORTC_INP_REG						((volatile uint8*)0x33U)

#define PORTD_OUT_REG						((volatile uint8*)0x32U)
#define PORTD_DIR_REG						((volatile uint8*)0x31U)
#define PORTD_INP_REG						((volatile uint8*)0x30U)

/************************************************************************/
/*				Global Interrupts Module - SFR Addresses                */
/************************************************************************/
#define STATUS_REG							((volatile uint8*)0x5FU)

/************************************************************************/
/*						Shared Timers SFR Addresses                     */
/************************************************************************/
#define TIMERS_INT_MASK_REG					((volatile uint8*)0x59U)
#define TIMERS_INT_FLAG_REG					((volatile uint8*)0x58U)

/************************************************************************/
/*						Timer 0 SFR Addresses                           */
/************************************************************************/
#define TIMER0_CTRL_REG						((volatile uint8*)0x53U)
#define TIMER0_CNTR_REG						((volatile uint8*)0x52U)
#define TIMER0_CMP_REG						((volatile uint8*)0x5CU)

/************************************************************************/
/*						Timer 1 SFR Addresses                           */
/************************************************************************/
#define TIMER1_CTRL_REG_A					((volatile uint8*)0x4FU)
#define TIMER1_CTRL_REG_B					((volatile uint8*)0x4EU)
#define TIMER1_CNTR_REG_H					((volatile uint8*)0x4DU)
#define TIMER1_CNTR_REG_L					((volatile uint8*)0x4CU)
#define TIMER1_CMP_A_REG_H					((volatile uint8*)0x4BU)
#define TIMER1_CMP_A_REG_L					((volatile uint8*)0x4AU)
#define TIMER1_CMP_B_REG_H					((volatile uint8*)0x49U)
#define TIMER1_CMP_B_REG_L					((volatile uint8*)0x48U)
#define TIMER1_INP_CAPT_REG_H				((volatile uint8*)0x47U)
#define TIMER1_INP_CAPT_REG_L				((volatile uint8*)0x46U)

/************************************************************************/
/*						Timer 2 SFR Addresses                           */
/************************************************************************/
#define TIMER2_CTRL_REG						((volatile uint8*)0x45U)
#define TIMER2_CNTR_REG						((volatile uint8*)0x44U)
#define TIMER2_CMP_REG						((volatile uint8*)0x43U)


#endif /* ATMEGA32A_CONFIG_H_ */