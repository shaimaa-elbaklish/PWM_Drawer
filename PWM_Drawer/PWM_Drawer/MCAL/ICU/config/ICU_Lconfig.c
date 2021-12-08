/*
 * ICU_Lconfig.c
 *
 * Created: 12/6/2021 1:49:14 PM
 *  Author: Shaimaa K. El-Baklish
 */ 

#include "ICU.h"

const ICU_ConfigurationType gStrICU_Config = 
{
	ICU_TIMER_1,
	ICU_PRESCALE_8,
	ICU_TRIGGER_FALLING_EDGE,
	ICU_INTERRUPT_DISABLED
};