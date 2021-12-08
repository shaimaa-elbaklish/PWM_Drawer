/*
 * PWM_Drawer.h
 *
 * Created: 12/7/2021 12:05:32 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef PWM_DRAWER_H_
#define PWM_DRAWER_H_

#include "ATmega32A_Config.h"
#include "Std_Types.h"
#include "GLCD.h"
#include "PWM.h"
#include "ICU.h"
#include "PWM_Drawer_Pconfig.h"

#define NUM_SPECIAL_CHARACTERS				(7U)
/************************************************************************/
/*				Signal Patterns Characters (Font = 5 x 8)               */
/************************************************************************/
#define PWM_DRAWER_GLCD_HIGH_LINE					(0x0202020202UL)
#define PWM_DRAWER_GLCD_LOW_LINE					(0x4040404040UL)
#define PWM_DRAWER_GLCD_RISING_EDGE					(0x02027E4040UL)
#define PWM_DRAWER_GLCD_FALLING_EDGE				(0x40407E0202UL)
#define PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD			(0x003E081C2AUL)
#define PWM_DRAWER_GLCD_LEFT_ARROW_HEAD				(0x2A1C083E00UL)
#define PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY			(0x0808080808UL)

/************************************************************************/
/*				Data Types for PWM Drawer Application                   */
/************************************************************************/

typedef struct {
	uint8 Duty_Percent;
	float32 High_Time_ms;
	float32 Low_Time_ms;
	float32 Period_Time_ms;
	float32 Freq_kHz;
}PWMDrawer_SignalAttributesType;

/************************************************************************/
/*			Function Prototypes for PWM Drawer Application              */
/************************************************************************/
void PWMDrawer_Init(void);
void PWMDrawer_MeasureSignal(PWMDrawer_SignalAttributesType* Signal_Data_Ptr);
void PWMDrawer_DrawSignal(PWMDrawer_SignalAttributesType* Signal_Data_Ptr, float32 Scale_ms);


#endif /* PWM_DRAWER_H_ */