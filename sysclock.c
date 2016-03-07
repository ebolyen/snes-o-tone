#include <avr/interrupt.h>
#include "config.h"
#include "sysclock.h"

/************************************************************************
 * Internal defines for the system clock module
 ************************************************************************/
#define TIMER_COUNTS_PER_OVERFLOW 256UL
#define OVERFLOWS_PER_TICK (F_CPU / (TIMER_COUNTS_PER_OVERFLOW * SYSCLOCK_TICKRATE))

/************************************************************************
 * Variables in the static scope of this module (i.e. this .c file)
 ************************************************************************/
volatile unsigned int num_overflows;
volatile time ticks;
volatile unsigned int overflow_max;

/************************************************************************
 *
 ************************************************************************/
void sysclock_start()
{
	ticks         = 0;
	num_overflows = 0;
	overflow_max  = OVERFLOWS_PER_TICK;

	//Start timer0 with no pre-scalar
	TCCR0B |= (1 << CS00);
	TCNT0 = 0;

	//Enable the overflow interrupt for the timer 0 counter
	TIMSK0 |= (1 << TOIE0);

	/** Note - requires system interrupts to be enabled before this will start working **/
}

/************************************************************************
 *
 ************************************************************************/
time sysclock_ticks()
{
	return ticks;
}

/************************************************************************
 *
 ************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(++num_overflows >= overflow_max)
	{
		num_overflows = 0;
		++ticks;
	}
}
