#ifndef NVIC_PRIVATE_H_ 

#define NVIC_PRIVATE_H_

/*NVIC_EN0_R enables interrupts from interrupt sources 0 to 31,
which includes interrupts from peripherals like GPIO ports, UARTs, and timers.*/
/*NVIC_EN1_R enables interrupts from interrupt sources 32 to 63,
which includes interrupts from peripherals like the ADC, USB, and Ethernet.*/
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1_R              (*((volatile unsigned long *)0xE000E104))


/*like EN0_R but disable*/
#define NVIC_DIS0_R             (*((volatile unsigned long *)0xE000E180))
#define NVIC_DIS1_R             (*((volatile unsigned long *)0xE000E184))


/*The NVIC_PEND0_R and NVIC_PEND1_R registers 
are used to trigger pending interrupts from the various peripherals.*/
#define NVIC_PEND0_R            (*((volatile unsigned long *)0xE000E200))
#define NVIC_PEND1_R            (*((volatile unsigned long *)0xE000E204))

#define NVIC_UNPEND0_R          (*((volatile unsigned long *)0xE000E280))
#define NVIC_UNPEND1_R          (*((volatile unsigned long *)0xE000E284))


/*The NVIC_ACTIVE0_R and NVIC_ACTIVE1_R registers are used
to indicate which interrupts are currently being serviced by the NVIC.
and a bit set to 1 indicates that the corresponding interrupt
is currently being serviced. */
#define NVIC_ACTIVE0_R          (*((volatile unsigned long *)0xE000E300))
#define NVIC_ACTIVE1_R          (*((volatile unsigned long *)0xE000E304))

/*Note that triggering a pending interrupt request does not 
immediately jump to the corresponding interrupt handler,
but instead waits for the current instruction to complete before
handling the interrupt. The NVIC manages the priorities of pending interrupt requests and
handles them in the order of their priorities.*/
#endif