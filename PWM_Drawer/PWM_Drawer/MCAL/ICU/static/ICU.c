/*
 * ICU.c
 *
 * Created: 12/6/2021 1:49:23 PM
 *  Author: Shaimaa K. El-Baklish
 */ 

#include "ICU.h"
#include "Bit_Macros.h"

/************************************************************************/
/*					Private Functions Prototypes                        */
/************************************************************************/
void ICU_InitTimer1(const ICU_ConfigurationType* Config_Ptr);
void ICU_GetDutyCycle_Timer1(uint16 Prescale_Value, ICU_DutyCycleType* Duty_Ptr);

/************************************************************************/
/*					Functions Implementations                           */
/************************************************************************/
void ICU_Init(const ICU_ConfigurationType* Config_Ptr) {
	switch (Config_Ptr->Tmr_Channel) {
		case ICU_TIMER_1: ICU_InitTimer1(Config_Ptr); break;
		default: break;
	}
}

void ICU_SetTriggerEdge(ICU_TimerChannelType Tmr_Channel, ICU_TriggerEdgeType Edge) {
	CLEAR_BIT(*TIMER1_CTRL_REG_B, ICU_TIMER1_EDGE_SELECT_BIT);
	switch (Tmr_Channel) {
		case ICU_TIMER_1: *TIMER1_CTRL_REG_B |= (Edge<<ICU_TIMER1_EDGE_SELECT_BIT); break;
		default: break;
	}
}

void ICU_ClearTimerValue(ICU_TimerChannelType Tmr_Channel) {
	switch (Tmr_Channel) {
		case ICU_TIMER_1: *(uint16*)TIMER1_CNTR_REG_L = 0x0000U; break;
		default: break;
	}
}

uint16 ICU_GetInputCaptureValue(ICU_TimerChannelType Tmr_Channel) {
	uint16 u16Local_Value = 0U;
	switch (Tmr_Channel) {
		case ICU_TIMER_1: u16Local_Value = (*(uint16*)TIMER1_INP_CAPT_REG_L);
		default: break;
	}
	return u16Local_Value;
}

ICU_StatusType ICU_GetStatus(ICU_TimerChannelType Tmr_Channel) {
	switch (Tmr_Channel) {
		case ICU_TIMER_1: 
			if (READ_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT) == 1) {
				SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);  /* Clear Flag */
				return ICU_EVENT_CATURED;
			} else {
				return ICU_RUNNING;
			}
		default: break;
	}
	return ICU_RUNNING;
}

void ICU_GetDutyCycle(ICU_TimerChannelType Tmr_Channel, uint16 Prescale_Value, ICU_DutyCycleType* Duty_Ptr) {
	switch (Tmr_Channel) {
		case ICU_TIMER_1:
			ICU_GetDutyCycle_Timer1(Prescale_Value, Duty_Ptr);
			break;
		default: break;
	}
}

/************************************************************************/
/*					Private Functions Implementations                   */
/************************************************************************/
void ICU_InitTimer1(const ICU_ConfigurationType* Config_Ptr) {
	/* Set ICP1 Pin (on PD6) as Input to trigger the ICU */
	CLEAR_BIT(*PORTD_DIR_REG, 6U);
	/* Clear Configurations on TCCR1A and TCCR1B */
	*TIMER1_CTRL_REG_A = 0x00U;
	*TIMER1_CTRL_REG_B = 0x00U;
	/* Timer 1 mode is set to normal */
	/* Set Prescaler */
	*TIMER1_CTRL_REG_B |= (Config_Ptr->Clk_Prescale);
	/* Set Trigger Edge (Falling or Rising) */
	*TIMER1_CTRL_REG_B |= ((Config_Ptr->Trigger_Edge)<<ICU_TIMER1_EDGE_SELECT_BIT);
	/* Set Interrupt State */
	*TIMERS_INT_MASK_REG |= ((Config_Ptr->Int_State)<<ICU_TIMER1_INT_BIT);
	/* Clear Timer 1 and ICR Values */
	*(uint16*)TIMER1_CNTR_REG_L = 0x0000U;
	*(uint16*)TIMER1_INP_CAPT_REG_L = 0x0000U;
}

void ICU_GetDutyCycle_Timer1(uint16 Prescale_Value, ICU_DutyCycleType* Duty_Ptr) {
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_RISING_EDGE);
	/* Wait for the start of the period at rising edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING) {
		; // Do Nothing
	}

	uint32 u32Local_ON_Counts = 0U;
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_FALLING_EDGE);
	ICU_ClearTimerValue(ICU_TIMER_1);
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	/* Wait for the end of the high time at falling edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING) {
		if (READ_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT) == 1) {
			SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT);
			u32Local_ON_Counts += ICU_TIMER1_RESOLUTION;
		}
	}
	u32Local_ON_Counts += ICU_GetInputCaptureValue(ICU_TIMER_1);

	uint32 u32Local_OFF_Counts = 0U;
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_RISING_EDGE);
	ICU_ClearTimerValue(ICU_TIMER_1);
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	/* Wait for the end of the period at rising edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING) {
		if (READ_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT) == 1) {
			SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT);
			u32Local_OFF_Counts += ICU_TIMER1_RESOLUTION;
		}
	}
	u32Local_OFF_Counts = ICU_GetInputCaptureValue(ICU_TIMER_1);

	/* Set counts */
	//strLocal_Duty.High_Time = u32Local_ON_Counts;
	//strLocal_Duty.Period_Time = u32Local_ON_Counts + u32Local_OFF_Counts;
	/* Convert these into milliseconds */
	Duty_Ptr->High_Time = (float32)(u32Local_ON_Counts * Prescale_Value * 1000.0 / F_CPU);
	Duty_Ptr->Period_Time = (float32)((u32Local_ON_Counts+u32Local_OFF_Counts) * Prescale_Value * 1000.0 / F_CPU);
}
