#ifndef SYSCLOCK_H
#define SYSCLOCK_H

/************************************************************************
 * System clock configuration settings: alter to match needs
 ************************************************************************/
#define SYSCLOCK_TICKRATE 1000UL							//Number of desired ticks per second
#define SYSCLOCK_TICKS_PER_MS (SYSCLOCK_TICKRATE / 1000UL)	//Number of ticks per ms given the desired tick rate

/************************************************************************
 * System clock data types
 ************************************************************************/
typedef long long time;

/************************************************************************
 * System clock utility macros: do NOT alter
 ************************************************************************/
#define SYSCLOCK_TICKS_TO_MS(TICKS) (TICKS / SYSCLOCK_TICKS_PER_MS)

void sysclock_start();
time sysclock_ticks();

#endif
