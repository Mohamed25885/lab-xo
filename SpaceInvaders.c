
#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "bitmaps.h"
#include "game.h"
#include "common.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer2_Init(unsigned long period);
unsigned long TimerCount;
unsigned long Semaphore;

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
unsigned long SW1, SW2; // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)

//   Function Prototypes
void PortF_Init(void);
void EnableInterrupts(void);

// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10

int main(void)
{
  int X = 0, Y = 0;

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
  PortF_Init();       // Call initialization of port PF4, PF3, PF2, PF1, PF0
  EnableInterrupts(); // The grader uses interrupts
  while (1)
  {
    SW1 = GPIO_PORTF_DATA_R & 0x10; // read PF4 into SW1
    SW2 = GPIO_PORTF_DATA_R & 0x01; // read PF0 into SW2

    if (SW1 && (!SW2))
    { // just SW1 pressed
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
    else if ((!SW1) && SW2)
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

void PortF_Init(void)
{ 

  SYSCTL_RCGC2_R |= 0x00000020;   // 1) F clock
  delay = SYSCTL_RCGC2_R;         // delay
	GPIO_vidUnlock(GPIOF);
  GPIOF_CR_R = 0x1F;         // allow changes to PF4-0
  GPIOF_AMSEL_R = 0x00;      // 3) disable analog function
  GPIOF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIOF_AFSEL_R = 0x00;      // 6) no alternate function
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  EnableInterrupts();
}
