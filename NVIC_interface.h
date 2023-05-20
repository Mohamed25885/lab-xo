#ifndef NVIC_INTERFACE_H_

#define NVIC_INTERFACE_H_
#include "Types.h"


void NVIC_vidEnableInterrupt(u8 u8InterruptNumber);
void NVIC_vidDisableInterrupt(u8 u8InterruptNumber);
void NVIC_vidSetPendingFlag(u8 u8InterruptNumber);
void NVIC_vidClearPendingFlag(u8 u8InterruptNumber);

u8 NVIC_u8GetActiveFlag(u8 u8InterruptNumber);

#endif