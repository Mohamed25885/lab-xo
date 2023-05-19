#include "Types.h"
#include "GPIO_config.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "../tm4c123gh6pm.h"
#include "TExaS.h"
#include "Timer.h"
#include "NVIC_interface.h"

volatile unsigned long delay;

void GPIOSetDirection(_enuGPIOx portNum, _enuPINx pinNum, _enuIOx pinDirection) {
	switch (portNum) {
		case GPIOA:
			if (pinDirection == OUTPUT) {
				GPIOA_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOA_DIR_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOB:
			if (pinDirection == OUTPUT) {
				GPIOB_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOB_DIR_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOC:
			if (pinDirection == OUTPUT) {
				GPIOC_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOC_DIR_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOD:
			if (pinDirection == OUTPUT) {
				GPIOD_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOD_DIR_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOE:
			if (pinDirection == OUTPUT) {
				GPIOE_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOE_DIR_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOF:
			if (pinDirection == OUTPUT) {
				GPIOF_DIR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOF_DIR_R &= ~(1 << (pinNum));
			}
			break;
	}

}

void GPIOEnableInterrupt(_enuGPIOx portNum, _enuPINx pinNum)
{
switch(portNum) {
		case GPIOA:
			GPIOA_IM_R |=  (1 << (pinNum));
			break;
		case GPIOB:
			GPIOB_IM_R |=  (1 << (pinNum));
			break;
		case GPIOC:
			GPIOC_IM_R |=  (1 << (pinNum));
			break;
		case GPIOD:
			GPIOD_IM_R |=  (1 << (pinNum));
			break;
		case GPIOE:
			GPIOE_IM_R |=  (1 << (pinNum));
			break;
		case GPIOF:
			GPIOF_IM_R |=  (1 << (pinNum));
			break;
	}
}
void GPIODisableInterrupt(_enuGPIOx portNum, _enuPINx pinNum)
{
switch(portNum) {
		case GPIOA:
			GPIOA_IM_R&= ~(1 << (pinNum));
			break;
		case GPIOB:
			GPIOB_IM_R&= ~(1 << (pinNum));
			break;
		case GPIOC:
			GPIOC_IM_R&= ~(1 << (pinNum));
			break;
		case GPIOD:
			GPIOD_IM_R&= ~(1 << (pinNum));
			break;
		case GPIOE:
			GPIOE_IM_R&= ~(1 << (pinNum));
			break;
		case GPIOF:
			GPIOF_IM_R&= ~(1 << (pinNum));
			break;
	}
}


void GPIOInterruptSense(_enuGPIOx portNum, _enuPINx pinNum, unsigned char Sense)
{
	switch (portNum)
	{
		case GPIOA:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOA_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOA_IS_R |=  (1 << (pinNum));
			}
			break;
		case GPIOB:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOB_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOB_IS_R |=  (1 << (pinNum));
			}
			break;
		case GPIOC:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOC_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOC_IS_R |=  (1 << (pinNum));
			}
			break;
		case GPIOD:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOD_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOD_IS_R |=  (1 << (pinNum));
			}
			break;
		case GPIOE:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOE_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOE_IS_R |=  (1 << (pinNum));
			}
			break;
    	case GPIOF:
			if (Sense == GPIO_SENSE_EDGE)
			{
				GPIOF_IS_R&= ~(1 << (pinNum))
			}
			else
			{
				GPIOF_IS_R |=  (1 << (pinNum));
			}
			break;
	}

}



void GPIOClearInterrupt(_enuGPIOx portNum, _enuPINx pinNum)
{
	switch(portNum)
	{
		case GPIOA:
			GPIOA_ICR_R |=  (1 << (pinNum));
			break;
		case GPIOB:
			GPIOB_ICR_R |=  (1 << (pinNum));
			break;
		case GPIOC:
			GPIOC_ICR_R |=  (1 << (pinNum));
			break;
		case GPIOD:
			GPIOD_ICR_R |=  (1 << (pinNum));
			break;
		case GPIOE:
			GPIOE_ICR_R |=  (1 << (pinNum));
			break;
		case GPIOF:
			GPIOF_ICR_R |=  (1 << (pinNum));
			break;
	}
}

void GPIOUnlock(_enuGPIOx portNum)
{
	switch(portNum)
	{
		case GPIOA:
				GPIOA_LOCK_R = 0x4C4F434B;
			break;
		case GPIOB:
				GPIOB_LOCK_R = 0x4C4F434B;
			break;
		case GPIOC:
				GPIOC_LOCK_R = 0x4C4F434B;
			break;
		case GPIOD:
				GPIOD_LOCK_R = 0x4C4F434B;
			break;
		case GPIOE:
				GPIOE_LOCK_R = 0x4C4F434B;
			break;
		case GPIOF:
				GPIOF_LOCK_R = 0x4C4F434B;
			break;
	}
}

void GPIO_Lock(_enuGPIOx portNum)
{
	switch(portNum)
	{
		case GPIOA:
			GPIOA_LOCK_R = 0;
			break;
		case GPIOB:
			GPIOB_LOCK_R = 0;
			break;
		case GPIOC:
			GPIOC_LOCK_R = 0;
			break;
		case GPIOD:
			GPIOD_LOCK_R = 0;
			break;
		case GPIOE:
			GPIOE_LOCK_R = 0;
			break;
		case GPIOF:
			GPIOF_LOCK_R = 0;
			break;
	}
}



void GPIOInterruptEvent(_enuGPIOx portNum, _enuPINx pinNum, unsigned char Event)
{
	switch(portNum)
	{
		case GPIOA:
			if (Event == GPIO_HL_RE)
			{
				GPIOA_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOA_IEV_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOB:
			if (Event == GPIO_HL_RE)
			{
				GPIOB_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOB_IEV_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOC:
			if (Event == GPIO_HL_RE)
			{
				GPIOC_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOC_IEV_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOD:
			if (Event == GPIO_HL_RE)
			{
				GPIOD_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOD_IEV_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOE:
			if (Event == GPIO_HL_RE)
			{
				GPIOE_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOE_IEV_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOF:
			if (Event == GPIO_HL_RE)
			{
				GPIOF_IEV_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOF_IEV_R&= ~(1 << (pinNum))
			}
			break;
	}
}


void GPIOInterruptBE(_enuGPIOx portNum, _enuPINx pinNum , unsigned char BothEdges)
{
	switch(portNum)
	{
		case GPIOA:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOA_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOA_IBE_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOB:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOB_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOB_IBE_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOC:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOC_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOC_IBE_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOD:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOD_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOD_IBE_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOE:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOE_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOE_IBE_R&= ~(1 << (pinNum))
			}
			break;
		case GPIOF:
			if (BothEdges == GPIO_INTERRUPT_BOTHEDGES)
			{
				GPIOF_IBE_R |=  (1 << (pinNum));
			}
			else
			{
				GPIOF_IBE_R&= ~(1 << (pinNum))
			}
			break;
	}
}
void GPIOSetValue(_enuGPIOx portNum, _enuPINx pinNum, _enuPINVALUE pinValue) {
	switch (portNum) {
		case GPIOA:
			if (pinValue == HIGH) {
				GPIOA_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOA_DATA_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOB:
			if (pinValue == HIGH) {
				GPIOB_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOB_DATA_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOC:
			if (pinValue == HIGH) {
				GPIOC_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOC_DATA_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOD:
			if (pinValue == HIGH) {
				GPIOD_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOD_DATA_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOE:
			if (pinValue == HIGH) {
				GPIOE_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOE_DATA_R &= ~(1 << (pinNum));
			}
			break;
		case GPIOF:
			if (pinValue == HIGH) {
				GPIOF_DATA_R |=  (1 << (pinNum));	
			}
			else {
				GPIOF_DATA_R &= ~(1 << (pinNum));
			}
			break;
	}
}

_enuPINVALUE GPIOReadPinValue(_enuGPIOx portNum, _enuPINx pinNum)
{
     _enuPINVALUE enuPinReturnedValue;

	switch(portNum)
	{
		case GPIOA:
			enuPinReturnedValue = ((GPIOA_DATA_R >> pinNum) & 1  );
			break;
		case GPIOB:
			enuPinReturnedValue = ((GPIOB_DATA_R >> pinNum) & 1  );
			break;
		case GPIOC:
			enuPinReturnedValue = ((GPIOC_DATA_R >> pinNum) & 1  );
			break;
		case GPIOD:
			enuPinReturnedValue = ((GPIOD_DATA_R >> pinNum) & 1  );
			break;
		case GPIOE:
			enuPinReturnedValue = ((GPIOE_DATA_R >> pinNum) & 1  );
			break;
		case GPIOF:
			enuPinReturnedValue = ((GPIOF_DATA_R >> pinNum) & 1  );
			break;
	}
	return enuPinReturnedValue;
}


void GPIO_TogglePin(_enuGPIOx portNum, _enuPINx pinNum)
{
	switch(portNum)
	{
		case GPIOA:
			GPIOA_DATA_R ^=  (1 << (pinNum))
		break;
		case GPIOB:
			GPIOB_DATA_R ^=  (1 << (pinNum))
		break;
		case GPIOC:
			GPIOC_DATA_R ^=  (1 << (pinNum))
		break;
		case GPIOD:
			GPIOD_DATA_R ^=  (1 << (pinNum))
			break;
		case GPIOE:
			GPIOE_DATA_R ^=  (1 << (pinNum))
			break;
		case GPIOF:
			GPIOF_DATA_R ^=  (1 << (pinNum))
			break;
	}
}

void GPIO_PinDigEnable(_enuGPIOx portNum, _enuPINx pinNum, _enuDigitalEnable DigitalEnable ) {
	switch (portNum) {
		case GPIOA:
			if (DigitalEnable == ENABLE) {
				GPIOA_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOA_DEN_R&= ~(1 << (pinNum));
			}
		case GPIOB:
			if (DigitalEnable == ENABLE) {
				GPIOB_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOB_DEN_R&= ~(1 << (pinNum));
			}
		case GPIOC:
			if (DigitalEnable == ENABLE) {
				GPIOC_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOC_DEN_R&= ~(1 << (pinNum));
			}
		case GPIOD:
			if (DigitalEnable == ENABLE) {
				GPIOD_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOD_DEN_R&= ~(1 << (pinNum));
			}
		case GPIOE:
			if (DigitalEnable == ENABLE) {
				GPIOE_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOE_DEN_R&= ~(1 << (pinNum));
	          }

	    case GPIOF:
			if (DigitalEnable == ENABLE) {
				GPIOF_DEN_R |=  (1 << (pinNum));	
			}
			else {
				GPIOF_DEN_R&= ~(1 << (pinNum));
	          }
			}
}

void GPIOSetPUR(_enuGPIOx portNum, _enuPINx pinNum, unsigned char PURConfig)
{
switch (portNum) {
		case GPIOA:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOA_PUR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOA_PUR_R&= ~(1 << (pinNum));
			}
			break;
		case GPIOB:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOB_PUR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOB_PUR_R&= ~(1 << (pinNum));
			}
			break;
		case GPIOC:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOC_PUR_R |=  (1 << (pinNum));	
			}
			else {
				GPIOC_PUR_R&= ~(1 << (pinNum));
			}
			break;
		case GPIOD:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOD_PUR_R |=  (1 << (pinNum));
			}
			else {
				GPIOD_PUR_R&= ~(1 << (pinNum));
			}
			break;
		case GPIOE:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOE_PUR_R |=  (1 << (pinNum));
			}
			else {
				GPIOE_PUR_R&= ~(1 << (pinNum));
			}
			break;
		case GPIOF:
			if (PURConfig == GPIO_PUR_ENABLED) {
				GPIOF_PUR_R |=  (1 << (pinNum));
			}
			else {
				GPIOF_PUR_R&= ~(1 << (pinNum));
			}
			break;
	}
}

void GPIO_SelectAlterFunction(_enuGPIOx portNum, _enuPINx pinNum)
 {
	switch(portNum) {
		case GPIOA:
			GPIOA_AFSEL_R |=  (1 << (pinNum));
			break;
		case GPIOB:
			GPIOB_AFSEL_R |=  (1 << (pinNum));
			break;
		case GPIOC:
			GPIOC_AFSEL_R |=  (1 << (pinNum));
			break;
		case GPIOD:
			GPIOD_AFSEL_R |=  (1 << (pinNum));
			break;
		case GPIOE:
			GPIOE_AFSEL_R |=  (1 << (pinNum));
			break;
		case GPIOF:
			GPIOF_AFSEL_R |=  (1 << (pinNum));
			break;
	}
}



void PortE_Init(void)
{ 

  SYSCTL_RCGC2_R |= 0x00000010;   // 1) E clock
  delay = SYSCTL_RCGC2_R;         // delay
	GPIOUnlock(GPIOF);
  GPIOF_CR_R = 0x1F;         // allow changes to PF4-0
  GPIOF_AMSEL_R = 0x00;      // 3) disable analog function
  GPIOF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIOF_AFSEL_R = 0x00;      // 6) no alternate function
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  EnableInterrupts();
}


