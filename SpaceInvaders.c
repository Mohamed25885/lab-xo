#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "bitmaps.h"
#include "game.h"
#include "common.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer2_Init(unsigned long period);
unsigned long TimerCount;
unsigned long Semaphore;

#define GPIOE_BASE_ADDRESS    0x40024000
#define GPIOE_IBE_R        (*((volatile unsigned long *) GPIOE_BASE_ADDRESS + 0x408))
#define GPIOE_IEV_R        (*((volatile unsigned long *) GPIOE_BASE_ADDRESS + 0x40C))
#define GPIOE_IM_R         (*((volatile unsigned long *) GPIOE_BASE_ADDRESS + 0x410))
#define GPIOE_ICR_R        (*((volatile unsigned long *) GPIOE_BASE_ADDRESS + 0x41C))
#define GPIOE_IS_R         (*((volatile unsigned long *) GPIOE_BASE_ADDRESS + 0x404))
	
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *)0x40025400))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTF_AFSEL_R (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_LOCK_R (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_CR_R (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R (*((volatile unsigned long *)0x4002552C))

// 2. Declarations Section
//   Global Variables
//right left up down press
unsigned long SW1, SW2, swRight, swLeft, swUp, swDown, swPress; // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)

//   Function Prototypes
void PortE_Init(void);
void EnableInterrupts(void);

// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10
int X = 0, Y = 0;
int main(void)
{
  

  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Random_Init(1);
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  Nokia5110_DisplayBuffer(); // draw buffer

  Nokia5110_PrintBMP(5, 13, SelectHere, 0); // player ship middle bottom
  DrawPlayedGrid();
  Nokia5110_DisplayBuffer(); // draw buffer
  DrawGrid();

  // TExaS_Init initializes the real board grader for lab 4
  PortE_Init();       // Call initialization of port PF4, PF3, PF2, PF1, PF0
  EnableInterrupts(); // setting the PRIMASK register bit no 0 with value 0 to enable
  //all inturrupts 'global inturrupt register'
  while (1)
  {
		
		swRight = GPIO_PORTE_DATA_R & 0x20; // read Pe5 into swRight
    swLeft = GPIO_PORTE_DATA_R & 0x10; // read Pe4 into SWLeft
		swUp = GPIO_PORTE_DATA_R & 0x08; //pf3
		swDown = GPIO_PORTE_DATA_R & 0x04; //pe2
		swPress = GPIO_PORTE_DATA_R & 0x02; //pe1
		
		/*
    if(!swLeft){
			 NVIC_EN0_R = (1 << 4);
       NVIC_PEND0_R = (1 << 4);
		}
		
		if(!swRight){
			 NVIC_EN0_R = (1 << 4);
       NVIC_PEND0_R = (1 << 4);
		}
		
		if(!swUp){
			 NVIC_EN0_R = (1 << 4);
       NVIC_PEND0_R = (1 << 4);
		}
		
		if(!swDown){
			 NVIC_EN0_R = (1 << 4);
       NVIC_PEND0_R = (1 << 4);
		}
		
		if(!swPress){
			 NVIC_EN0_R = (1 << 4);
       NVIC_PEND0_R = (1 << 4);
		}
*/
    if (!swRight && swLeft && swUp && swDown && swPress)
    { // just SWRight pressed
      Nokia5110_ClearBuffer();
      StepRight(&X, &Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
		else if (swRight && !swLeft && swUp && swDown && swPress)
    { // just SWLeft pressed
      Nokia5110_ClearBuffer();
      StepLeft(&X, &Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
		else if (swRight && swLeft && !swUp && swDown && swPress)
    { // just SWUp pressed
      Nokia5110_ClearBuffer();
      StepUp(&Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
		else if (swRight && swLeft && swUp && !swDown && swPress)
    { // just SWDown pressed
      Nokia5110_ClearBuffer();
      StepDown(&Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
    else if (swRight && swLeft && swUp && swDown && !swPress)
    {

      if (!GAME_GRID[Y][X])
      {
        Nokia5110_ClearBuffer();
        GAME_GRID[Y][X] = current_player + 1;
        DrawPlayedGrid();
        if (GAME_GRID[Y][X] == 1)
        {
          Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
        }
        else if (GAME_GRID[Y][X] == 2)
        {
          Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
        }
        current_player = current_player == 0 ? 1 : 0;
        Nokia5110_DisplayBuffer(); // draw buffer
        DrawGrid();
        Delay100ms(2);
      }
    }
		Delay100ms(5);
		
  }
}

// You can use this timer only if you learn how it works
void Timer2_Init(unsigned long period)
{
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04; // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;                             // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;                             // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;                            // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period - 1;                           // 4) reload value
  TIMER2_TAPR_R = 0;                                     // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;                             // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;                             // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; // 8) priority 4
                                                         // interrupts enabled in the main program after all devices initialized
                                                         // vector number 39, interrupt number 23
  NVIC_EN0_R = 1 << 23;                                  // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;                             // 10) enable timer2A
}
void Timer2A_Handler(void)
{
  TIMER2_ICR_R = 0x00000001; // acknowledge timer2A timeout
  TimerCount++;
  Semaphore = 1; // trigger
}

void PortE_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;   // 1) F clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTE_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0
  GPIO_PORTE_CR_R = 0xFF;         // allow changes to PF4-0
  GPIO_PORTE_AMSEL_R = 0x00;      // 3) disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTE_DIR_R = 0x00;        // 5) PF4,PF0, PF3,PF2,PF1 input
  GPIO_PORTE_AFSEL_R = 0x00;      // 6) no alternate function
  GPIO_PORTE_PUR_R = 0xFF;        // enable pullup resistors on PF4->PF0
  GPIO_PORTE_DEN_R = 0xFF;        // 7) enable digital pins PF4-PF0
  /*
	NVIC_PRI0_R = (NVIC_PRI0_R & 0x00ffffff) | 0x00A00000;
	GPIO_PORTE_IM_R  = 0xFF;
	GPIO_PORTE_IS_R  = 0x00;
  GPIO_PORTE_IBE_R  = 0x00;
  GPIO_PORTE_IEV_R = 0xFF; 
  NVIC_PRI1_R |= 0x00200000;
  NVIC_EN0_R |= 0x10;
  __enable_irq();
*/
}



//test


void GPIOE_Handler(void)
{
  while (GPIO_PORTE_MIS_R != 0)
  {
		
	 if (GPIO_PORTE_MIS_R & 0x02) 
    {                                 
			Delay100ms(5);
      if (!GAME_GRID[Y][X])
      {
        Nokia5110_ClearBuffer();
        GAME_GRID[Y][X] = current_player + 1;
        DrawPlayedGrid();
        if (GAME_GRID[Y][X] == 1)
        {
          Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
        }
        else if (GAME_GRID[Y][X] == 2)
        {
          Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
        }
        current_player = current_player == 0 ? 1 : 0;
        Nokia5110_DisplayBuffer(); // draw buffer
        DrawGrid();
        Delay100ms(2);
      }
    }
		if (GPIO_PORTE_MIS_R & 0x04) 
    {                                 
			Delay100ms(5);
      // just SWDown pressed
      Nokia5110_ClearBuffer();
      StepDown(&Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
		
		if (GPIO_PORTE_MIS_R & 0x08) {
		// just SWUp pressed
      Nokia5110_ClearBuffer();
      StepUp(&Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
		
		}
		
		if (GPIO_PORTE_MIS_R & 0x10) {
		// just SWLeft pressed
      Nokia5110_ClearBuffer();
      StepLeft(&X, &Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
		}
		
    if (GPIO_PORTE_MIS_R & 0x20) 
    {// just SWRight pressed
      Nokia5110_ClearBuffer();
      StepRight(&X, &Y);
      DrawPlayedGrid();
      if (GAME_GRID[Y][X] == 1)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedXShape, 0); // player ship middle bottom
      }
      else if (GAME_GRID[Y][X] == 2)
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, InvertedOShape, 0); // player ship middle bottom
      }
      else
      {
        Nokia5110_PrintBMP(5 + 20 * X, 13 + 17 * Y, SelectHere, 0); // player ship middle bottom
      }
      Nokia5110_DisplayBuffer(); // draw buffer
      DrawGrid();
      Delay100ms(2);
    }
		
    else
    { 
      GPIO_PORTE_ICR_R = GPIO_PORTE_MIS_R;
    }
  }
}
