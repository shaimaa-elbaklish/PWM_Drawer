/*
 * DIO.c
 *
 * Created: 11/29/2021 4:32:14 PM
 *  Author: Shaimaa K. El-Baklish
 */ 

#include "ATmega32A_Config.h"
#include "Std_Types.h"
#include "Bit_Macros.h"
#include "DIO.h"

typedef enum {
	DIO_DIRECTION_REG,
	DIO_OUTPUT_REG,
	DIO_INPUT_REG
}DIO_RegisterType;

static volatile uint8* DIO_ObtainRegister(DIO_PortType Port, DIO_RegisterType Reg) {
	switch (Port) {
		case DIO_PORT_A: 
			switch (Reg) {
			case DIO_DIRECTION_REG: return PORTA_DIR_REG;
			case DIO_OUTPUT_REG: return PORTA_OUT_REG;
			case DIO_INPUT_REG: return PORTA_INP_REG;
			default: break;
			}
			break;
		case DIO_PORT_B: 
			switch (Reg) {
				case DIO_DIRECTION_REG: return PORTB_DIR_REG;
				case DIO_OUTPUT_REG: return PORTB_OUT_REG;
				case DIO_INPUT_REG: return PORTB_INP_REG;
				default: break;
			}
			break;
		case DIO_PORT_C: 
			switch (Reg) {
				case DIO_DIRECTION_REG: return PORTC_DIR_REG;
				case DIO_OUTPUT_REG: return PORTC_OUT_REG;
				case DIO_INPUT_REG: return PORTC_INP_REG;
				default: break;
			}
			break;
		case DIO_PORT_D: 
			switch (Reg) {
				case DIO_DIRECTION_REG: return PORTD_DIR_REG;
				case DIO_OUTPUT_REG: return PORTD_OUT_REG;
				case DIO_INPUT_REG: return PORTD_INP_REG;
				default: break;
			}
			break;
		default: break;
	}
	return NULL_PTR;
}

void DIO_SetPinDirection(DIO_PortType Port, DIO_PinType Pin, DIO_DirectionType Direction) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_DIRECTION_REG);
	switch (Direction) {
		case DIO_INPUT: CLEAR_BIT(*Reg_Ptr, Pin); break;
		case DIO_OUTPUT: SET_BIT(*Reg_Ptr, Pin); break;
		default: break;
	}
}

void DIO_WritePin(DIO_PortType Port, DIO_PinType Pin, DIO_StateType State) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_OUTPUT_REG);
	switch (State) {
		case DIO_LOW: CLEAR_BIT(*Reg_Ptr, Pin); break;
		case DIO_HIGH: SET_BIT(*Reg_Ptr, Pin); break;
		default: break;
	}
}

void DIO_TogglePin(DIO_PortType Port, DIO_PinType Pin) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_OUTPUT_REG);
	TOGGLE_BIT(*Reg_Ptr, Pin);
}

DIO_StateType DIO_ReadPin(DIO_PortType Port, DIO_PinType Pin) {
	DIO_StateType eLocal_State = DIO_LOW;
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_INPUT_REG);
	eLocal_State = READ_BIT(*Reg_Ptr, Pin);
	return eLocal_State;
}


void DIO_SetPortDirection(DIO_PortType Port, DIO_DirectionType Direction) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_DIRECTION_REG);
	switch (Direction) {
		case DIO_INPUT: *Reg_Ptr = 0x00U; break;
		case DIO_OUTPUT: *Reg_Ptr = 0xFFU; break;
		default: break;
	}
}

void DIO_WritePort(DIO_PortType Port, uint8 Value) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_OUTPUT_REG);
	*Reg_Ptr = Value;
}

uint8 DIO_ReadPort(DIO_PortType Port) {
	uint8 u8Local_Value = 0x00U;
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_INPUT_REG);
	u8Local_Value = *Reg_Ptr;
	return u8Local_Value;
}

void DIO_SetHighHalfPortDirection(DIO_PortType Port, DIO_DirectionType Direction) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_DIRECTION_REG);
	switch (Direction) {
		case DIO_INPUT: *Reg_Ptr &= ~(0xF0U); break;
		case DIO_OUTPUT: *Reg_Ptr |= (0xF0U); break;
		default: break;
	}
}

void DIO_SetLowHalfPortDirection(DIO_PortType Port, DIO_DirectionType Direction) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_DIRECTION_REG);
	switch (Direction) {
		case DIO_INPUT: *Reg_Ptr &= ~(0x0FU); break;
		case DIO_OUTPUT: *Reg_Ptr |= (0x0FU); break;
		default: break;
	}
}

void DIO_WriteHighHalfPort(DIO_PortType Port, uint8 HighValue) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_OUTPUT_REG);
	*Reg_Ptr &= (0x0FU);
	*Reg_Ptr |= (HighValue & 0xF0U);
}

void DIO_WriteLowHalfPort(DIO_PortType Port, uint8 LowValue) {
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_OUTPUT_REG);
	*Reg_Ptr &= (0xF0U);
	*Reg_Ptr |= (LowValue & 0x0F);
}

uint8 DIO_ReadHighHalfPort(DIO_PortType Port) {
	uint8 u8Local_Value = 0x00U;
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_INPUT_REG);
	u8Local_Value = (((*Reg_Ptr) & 0xF0U)>>4);
	return u8Local_Value;
}

uint8 DIO_ReadLowHalfPort(DIO_PortType Port) {
	uint8 u8Local_Value = 0x00U;
	volatile uint8* Reg_Ptr = DIO_ObtainRegister(Port, DIO_INPUT_REG);
	u8Local_Value = ((*Reg_Ptr) & 0x0FU);
	return u8Local_Value;
}