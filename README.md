# PWM_Drawer
Drawing a PWM Signal Using GLCD and ATmega32A

## Configurations Available
The project is implemented using static configuration.
1. **Application Layer (APP):** 
   - *PWM_Drawer_Pconfig.h*
   
   | Macro | Description |
   | ----- | ----------- |
   | GENERATE_PWM_FROM_SAME_MCU | 1 = Same micro-controller is used to generate PWM signal from Timer 0 or Timer 2 channels, as well as to measure and display this PWM signal using Timer 1 and Graphical LCD |
2. **Hardware Abstraction Layer (HAL):**
   - *GLCD_Pconfig.h:*
3. **Micro-controller Abstraction Layer (MCAL)**:
   - *PWM_Lconfig.c*
   - *ICU_Lconfig.c*
