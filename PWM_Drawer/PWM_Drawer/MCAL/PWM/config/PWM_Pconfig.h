/*
 * PWM_Pconfig.h
 *
 * Created: 12/4/2021 11:30:05 AM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef PWM_PCONFIG_H_
#define PWM_PCONFIG_H_

#define NUM_OPERATING_PWM_CHANNELS			(1U) /* Input the number of operating Timers for PWM */
#define PWM_TIMER_0_RESOLUTION				(255U)
#define PWM_TIMER_1_RESOLUTION				(65535U)
#define PWM_TIMER_2_RESOLUTION				(255U)


#if NUM_OPERATING_PWM_CHANNELS > 4
	#pragma GCC error "ATmega32A has only 3 timers with 4 PWM channels!! Fix NUM_OPERATING_PWM_CHANNELS."
#endif



#endif /* PWM_PCONFIG_H_ */