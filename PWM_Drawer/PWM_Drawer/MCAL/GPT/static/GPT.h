/*
 * GPT.h
 *
 * Created: 11/30/2021 4:45:37 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef GPT_H_
#define GPT_H_

#include "ATmega32A_Config.h"
#include "GPT_Pconfig.h"

/************************************************************************/
/*					Bit Definitions for GPT Module                      */
/************************************************************************/
#define TIMER0_CTC_CTRL_BIT					(3U)  /* in TCCR1 */
#define TIMER0_OVF_INT_BIT					(0U)
#define TIMER0_CMP_INT_BIT					(1U)

#define TIMER1_CTC_CTRL_BIT					(3U)  /* in TCCR1B */
#define TIMER1_OVF_INT_BIT					(2U)
#define TIMER1_CMP_B_INT_BIT				(3U)
#define TIMER1_CMP_A_INT_BIT				(4U)

#define TIMER2_CTC_CTRL_BIT					(3U)  /* in TCCR2 */
#define TIMER2_OVF_INT_BIT					(6U)
#define TIMER2_CMP_INT_BIT					(7U)

/************************************************************************/
/*						Data Types for GPT Module                       */
/************************************************************************/
typedef enum {
	GPT_TIMER_0,
	GPT_TIMER_1,
	GPT_TIMER_2
}GPT_TimerType;

typedef enum {
	GPT_NORMAL_MODE,
	GPT_CTC_MODE
}GPT_OperationType;

typedef enum {
	GPT_TIMER_STOP,
	GPT_PRESCALE_1,
	GPT_PRESCALE_8,
	GPT_PRESCALE_32,
	GPT_PRESCALE_64,
	GPT_PRESCALE_128,
	GPT_PRESCALE_256,
	GPT_PRESCALE_1024,
	GPT_EXT_CLK_FALLING_EDGE,
	GPT_EXT_CLK_RISING_EDGE
}GPT_ClockType;

typedef enum {
	GPT_INTERRUPT_DISABLED,
	GPT_INTERRUPT_ENABLED
}GPT_InterruptStateType;

typedef struct {
	GPT_TimerType Tmr_Channel;
	GPT_OperationType Op_Mode;
	GPT_ClockType Clk_Prescale;
	GPT_InterruptStateType Int_State;
}GPT_ConfigurationType;

typedef enum {
	GPT_TIMER_RUNNING,
	GPT_TIMER_FINISHED,
}GPT_StatusType;

typedef void (*Callback_Ptr)(void*);

/************************************************************************/
/*				Function Prototypes for GPT Module                      */
/************************************************************************/
void GPT_Init(const GPT_ConfigurationType* Config_Arr_Ptr);
void GPT_Delay_us(const GPT_ConfigurationType* Config_Ptr, uint16 Delay_Time_us);
void GPT_Delay_ms(const GPT_ConfigurationType* Config_Ptr, uint16 Delay_Time_ms);
GPT_StatusType GPT_GetTimerStatus(const GPT_ConfigurationType* Config_Ptr);

/************************************************************************/
/*				External Variables for GPT Module                       */
/************************************************************************/
extern const GPT_ConfigurationType gaStrGPT_Config[NUM_TIMERS_OPERATING];

#endif /* GPT_H_ */