# PWM_Drawer
Drawing a PWM Signal Using GLCD and ATmega32A

## Configurations Available
The project is implemented using static configuration.
1. **Application Layer (APP):** 
   - ***PWM_Drawer_Pconfig.h***
   
   | Macro | Description |
   | ----- | ----------- |
   | GENERATE_PWM_FROM_SAME_MCU | 1 = Same micro-controller is used to generate PWM signal from Timer 0 or Timer 2 channels, as well as to measure and display this PWM signal using Timer 1 and Graphical LCD; 0 = 2 separate micro-controllers used |
   | GLCD_MCU | This is only defined when 2 seperate micro-controllers are used (i.e. GENERATE_PWM_FROM_SAME_MCU = 1); 1 = this code (specifically in initialization) belongs to the microcontroller measuring the PWM signal and displaying it on the Graphical LCD; 0 = this code (specifically in initialization) belongs to the micro-controller generating the PWM signal only. |
2. **Hardware Abstraction Layer (HAL):**
   - ***GLCD_Pconfig.h***

   | Macro | Description |
   | ----- | ----------- |
   | GLCD_USE_TIMERS_FOR_DELAY | 1 = use GPT module (for Timers) to generate delays; 0 = use delay.h to generate delays. |
   | GLCD_CTRL_PORT | For hardware connection of all Graphical LCD control pins; Can be set to DIO_PORT_A, DIO_PORT_B, DIO_PORT_C or DIO_PORT_D. This includes the following pins: GLCD_ENABLE_PIN, GLCD_RW_PIN, GLCD_RS_PIN, GLCD_PAGE_SELECT_PIN_1, GLCD_PAGE_SELECT_PIN_2 and GLCD_RESET_PIN.|
   | GLCD_DATA_PORT | For hardware connection of all Graphical LCD data pins; Can be set to DIO_PORT_A, DIO_PORT_B, DIO_PORT_C or DIO_PORT_D. This includes the following pins: GLCD_DATA_D0_PIN - GLCD_DATA_D7_PIN. These pins are for 8-bit parallel communication. |
3. **Micro-controller Abstraction Layer (MCAL)**:
   - ***PWM_Pconfig.h***
   
   | Macro | Description |
   | ----- | ----------- |
   | NUM_OPERATING_PWM_CHANNELS | Number of operating PWM channels; Can be set from 1 to 4. |
   - ***PWM_Lconfig.c***
   
   This defines an array of configuration structs "*gaStrPWM_Config[NUM_OPERATING_PWM_CHANNELS]*".
   | Struct Member | Description |
   | ------------- | ----------- |
   | Tmr_Channel | Timer PWM Channel (enum); Can be PWM_TIMER_0_CHANNEL, PWM_TIMER_1_CHANNEL_A, PWM_TIMER_1_CHANNEL_B, or PWM_TIMER_2_CHANNEL. |
   | Mode | PWM mode (enum); Can be PWM_PHASE_CORRECT, or PWM_FAST. |
   | Clk_Prescale | Prescale used (enum); Can be PWM_NO_CLK_SRC, PWM_PRESCALE_1, PWM_PRESCALE_8, PWM_PRESCALE_32 (Timer 2 only), PWM_PRESCALE_64, PWM_PRESCALE_128 (Timer 2 only), PWM_PRESCALE_256, PWM_PRESCALE_1024, PWM_EXT_CLK_FALLING_EDGE (External Clock Source for Timers 0 and 1 only), or PWM_EXT_CLK_RISING_EDGE (External Clock Source for Timers 0 and 1 only). |
   | State | PWM output state (enum); Can be PWM_NON_INVERTED, or PWM_INVERTED. |
   | Prescale_Value | Integer for prescale value selected. |
   | Period_ms | Integer for desired period time in millisecond; Used for Timer 1 only; For other times, select appropriate prescalers to adjust period. |
   | Duty_Percent | Integer for desired duty cycle in percentage (i.e. 0 to 100). |
   - ***ICU_Lconfig.c***

   This defines an array of configuration structs "*gStrICU_Config*".
   | Struct Member | Description |
   | ------------- | ----------- |
   | Tmr_Channel | Timer Input Capture Channel (enum); Can only be ICU_TIMER_1_CHANNEL in ATmega32A. |
   | Clk_Prescale | Prescale used (enum); Can be PWM_NO_CLK_SRC, PWM_PRESCALE_1, PWM_PRESCALE_8, PWM_PRESCALE_64, PWM_PRESCALE_256, PWM_PRESCALE_1024, PWM_EXT_CLK_FALLING_EDGE (External Clock Source), or PWM_EXT_CLK_RISING_EDGE (External Clock Source). |
   | Trigger_Edge | Edge upon which the input capture unit is triggered (enum); Can be ICU_TRIGGER_FALLING_EDGE, or ICU_TRIGGER_RISING_EDGE. |
   | Int_State | Interrupt State of ICU Module (num); Can be ICU_INTERRUPT_DISABLED, or ICU_INTERRUPT_ENABLED; In case of enabling interrupts, an ISR must be provided. For the PWM_Drawer application, the interrupts are disabled in order to carefully measure the attributes of the PWM signal (period time, duty cycle and frequency). |
