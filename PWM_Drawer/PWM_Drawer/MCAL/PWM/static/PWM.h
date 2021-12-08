/*
 * PWM.h
 *
 * Created: 12/4/2021 11:29:54 AM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "ATmega32A_Config.h"
#include "PWM_Pconfig.h"

#define PWM_TIMER_0_FAST_BIT			(3U)
#define PWM_TIMER_0_INVERTING_BIT		(4U)

#define PWM_TIMER_1_FAST_BIT			(3U)
#define PWM_TIMER_1_A_INVERTING_BIT		(6U)
#define PWM_TIMER_1_B_INVERTING_BIT		(4U)

#define PWM_TIMER_2_FAST_BIT			(3U)
#define PWM_TIMER_2_INVERTING_BIT		(4U)

/************************************************************************/
/*					Data Types for PWM Module                           */
/************************************************************************/
typedef enum {
	PWM_TIMER_0_CHANNEL,
	PWM_TIMER_1_CHANNEL_A,
	PWM_TIMER_1_CHANNEL_B,
	PWM_TIMER_2_CHANNEL
}PWM_ChannelType;

typedef enum {
	PWM_PHASE_CORRECT,
	PWM_FAST
}PWM_ModeType;

typedef enum {
	PWM_NO_CLK_SRC,
	PWM_PRESCALE_1,
	PWM_PRESCALE_8,
	PWM_PRESCALE_32,
	PWM_PRESCALE_64,
	PWM_PRESCALE_128,
	PWM_PRESCALE_256,
	PWM_PRESCALE_1024,
	PWM_EXT_CLK_FALLING_EDGE,
	PWM_EXT_CLK_RISING_EDGE
}PWM_ClockPrescaleType;

typedef enum {
	PWM_NON_INVERTED,
	PWM_INVERTED
}PWM_OutputStateType;

typedef struct {
	PWM_ChannelType Tmr_Channel;
	PWM_ModeType Mode;
	PWM_ClockPrescaleType Clk_Prescale;
	PWM_OutputStateType State;
	uint16 Prescale_Value;
	uint16 Period_ms;
	uint8 Duty_Percent;
}PWM_ConfigurationType;

/************************************************************************/
/*				Function Prototypes for PWM Module                      */
/************************************************************************/
void PWM_Init(const PWM_ConfigurationType* Config_Ptr);
void PWM_SetDuty(PWM_ChannelType Tmr_Channel, PWM_OutputStateType State, uint16 Duty_Percent);

/************************************************************************/
/*				External Variables for PWM Module                       */
/************************************************************************/
extern const PWM_ConfigurationType gaStrPWM_Config[NUM_OPERATING_PWM_CHANNELS];

#endif /* PWM_H_ */