/*
 * PWM_Lconfig.c
 *
 * Created: 12/4/2021 11:30:14 AM
 *  Author: Shaimaa K. El-Baklish
 */ 

#include "PWM.h"

const PWM_ConfigurationType gaStrPWM_Config[NUM_OPERATING_PWM_CHANNELS] = 
{
	{
		PWM_TIMER_0_CHANNEL,
		PWM_FAST,
		PWM_PRESCALE_8,
		PWM_INVERTED,
		256U,
		4U,
		90U
	}
};