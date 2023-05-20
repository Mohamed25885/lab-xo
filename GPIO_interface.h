#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "Types.h"

typedef enum
{
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF
}_enuGPIOx;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7 
}_enuPINx;

typedef enum
{
    INPUT = 0,
    OUTPUT
}_enuIOx;

typedef enum
{
    LOW = 0,
    HIGH
}_enuPINVALUE;

typedef enum
{
   DISABLE =0 ,
   ENABLE
}_enuDigitalEnable;


#define GPIO_PUR_DISABLED 0
#define GPIO_PUR_ENABLED 1

#define GPIO_SENSE_EDGE 0
#define GPIO_SENSE_LEVEL 1

#define GPIO_LL_FE 0
#define GPIO_HL_RE 1

#define GPIO_INTERRUPT_EVENTCONTROLLED 0
#define GPIO_INTERRUPT_BOTHEDGES 1

void GPIOSetDirection(_enuGPIOx portNum, _enuPINx pinNum, _enuIOx pinDirection);
void GPIOEnableInterrupt(_enuGPIOx portNum, _enuPINx pinNum);
void GPIODisableInterrupt(_enuGPIOx portNum, _enuPINx pinNum);
void GPIOInterruptSense(_enuGPIOx portNum, _enuPINx pinNum, unsigned char Sense);
void GPIOClearInterrupt(_enuGPIOx portNum, _enuPINx pinNum);

void GPIOUnlock(_enuGPIOx portNum);
void GPIO_Lock(_enuGPIOx portNum);
void GPIOInterruptEvent(_enuGPIOx portNum, _enuPINx pinNum, unsigned char Event);
void GPIOInterruptBE(_enuGPIOx portNum, _enuPINx pinNum , unsigned char BothEdges);
void GPIOSetValue(_enuGPIOx portNum, _enuPINx pinNum, _enuPINVALUE pinValue);
void GPIO_TogglePin(_enuGPIOx portNum, _enuPINx pinNum);
void GPIO_PinDigEnable(_enuGPIOx portNum, _enuPINx pinNum, _enuDigitalEnable DigitalEnable );
void GPIOSetPUR(_enuGPIOx portNum, _enuPINx pinNum, unsigned char PURConfig);

void GPIO_SelectAlterFunction(_enuGPIOx portNum, _enuPINx pinNum);


void PortE_Init(void);


void PortF_Init(); 
void PortB_Init();
void EnableInterrupts(void);

#endif