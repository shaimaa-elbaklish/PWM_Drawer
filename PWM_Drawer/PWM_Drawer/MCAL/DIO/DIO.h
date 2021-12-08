/*
 * DIO.h
 *
 * Created: 11/29/2021 4:32:06 PM
 *  Author: Shaimaa K. El-Baklish
 */ 


#ifndef DIO_H_
#define DIO_H_

/************************************************************************/
/*				Data Types for DIO Module                               */
/************************************************************************/
typedef enum {
	DIO_PORT_A,
	DIO_PORT_B,
	DIO_PORT_C,
	DIO_PORT_D
}DIO_PortType;

typedef enum {
	DIO_PIN_0,
	DIO_PIN_1,
	DIO_PIN_2,
	DIO_PIN_3,
	DIO_PIN_4,
	DIO_PIN_5,
	DIO_PIN_6,
	DIO_PIN_7
}DIO_PinType;

typedef enum {
	DIO_INPUT,
	DIO_OUTPUT
}DIO_DirectionType;

typedef enum {
	DIO_LOW,
	DIO_HIGH
}DIO_StateType;

/************************************************************************/
/*				Function Prototypes for DIO Module                      */
/************************************************************************/
void DIO_SetPinDirection(DIO_PortType Port, DIO_PinType Pin, DIO_DirectionType Direction);
void DIO_WritePin(DIO_PortType Port, DIO_PinType Pin, DIO_StateType State);
void DIO_TogglePin(DIO_PortType Port, DIO_PinType Pin);
DIO_StateType DIO_ReadPin(DIO_PortType Port, DIO_PinType Pin);

void DIO_SetPortDirection(DIO_PortType Port, DIO_DirectionType Direction);
void DIO_WritePort(DIO_PortType Port, uint8 Value);
uint8 DIO_ReadPort(DIO_PortType Port);

void DIO_SetHighHalfPortDirection(DIO_PortType Port, DIO_DirectionType Direction);
void DIO_SetLowHalfPortDirection(DIO_PortType Port, DIO_DirectionType Direction);

void DIO_WriteHighHalfPort(DIO_PortType Port, uint8 HighValue);
void DIO_WriteLowHalfPort(DIO_PortType Port, uint8 LowValue);

uint8 DIO_ReadHighHalfPort(DIO_PortType Port);
uint8 DIO_ReadLowHalfPort(DIO_PortType Port);

#endif /* DIO_H_ */