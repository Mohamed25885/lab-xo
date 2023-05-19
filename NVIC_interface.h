#ifndef NVIC_INTERFACE_H_

#define NVIC_INTERFACE_H_



void EnableInterrupt(unsigned char InterruptNum);
void DisableInterrupt(unsigned char InterruptNum);
void SetFlag(unsigned char InterruptNum);
void ClearFlag(unsigned char InterruptNum);

unsigned char GetFlag(unsigned char InterruptNum);

#endif