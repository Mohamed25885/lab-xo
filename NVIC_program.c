
#include "./headers/NVIC_interface.h"
#include "./headers/NVIC_private.h"
#include "./headers/NVIC_config.h"


void SetFlag(unsigned char InterruptNum)
{
    if(InterruptNum <= 31)
    {
        NVIC_PEND0_R = (1 << InterruptNum);
    }
    else if(InterruptNum <= 63)
    {
        InterruptNum -= 32;
       NVIC_PEND1_R= (1 << InterruptNum);
    }
    else
    {
    
    }
}

void ClearFlag(unsigned char InterruptNum)
{
    if(InterruptNum<= 31)
    {
        NVIC_UNPEND0_R = (1 << InterruptNum);
    }
    else if(InterruptNum <= 63)
    {
        InterruptNum -= 32;
       NVIC_UNPEND1_R = (1 << InterruptNum);
    }
    else
    {
    
    }
}



unsigned char GetFlag(unsigned char InterruptNum)
{
	unsigned char Res;
	
	if ( InterruptNum <= 31)
	{
		Res = ((NVIC_ACTIVE0_R >>InterruptNum) & 1  );
	}
	
	else if ( InterruptNum <= 63)
	{
		InterruptNum -= 32;
		Res = ((NVIC_ACTIVE1_R >>InterruptNum) & 1  );
	}
	
	else
	{

	}
	
	return Res;
	
}

void EnableInterrupt(unsigned char InterruptNum)
{
    if(InterruptNum <= 31)
    {
        NVIC_EN0_R = (1 << InterruptNum);
    }
    else if(InterruptNum<= 63)
    {
        InterruptNum -= 32;
        NVIC_EN1_R = (1 << InterruptNum);
    }
    else
    {
    
    }
}


void DisableInterrupt(unsigned char InterruptNum)
{
    if(InterruptNum <= 31)
    {
        NVIC_DIS0_R = (1 << InterruptNum);
    }
    else if(InterruptNum<= 63)
    {
        InterruptNum -= 32;
        NVIC_DIS1_R = (1 << InterruptNum);
    }
    else
    {
    
    }
}



