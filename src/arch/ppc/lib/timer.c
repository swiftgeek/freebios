/* $Id: timer.c,v 1.1 2003/04/15 18:29:11 rminnich Exp $ */
/* Copyright 2000  AG Electronics Ltd. */
/* This code is distributed without warranty under the GPL v2 (see COPYING) */

#include <timer.h>
#include <bsp.h>

unsigned get_hz(void)
{
	return bsp_clock_speed() >> 16;
}

unsigned ticks_since_boot(void)
{
	extern unsigned long long _timebase(void);
	return (unsigned) (_timebase() >> 16);
}

void sleep_ticks(unsigned ticks)
{
	unsigned then = ticks + ticks_since_boot();
	while(ticks_since_boot() < then)
		;
}

void udelay(int usecs)
{
	unsigned ticksperusec = get_hz() / 1000000;

	sleep_ticks(ticksperusec * usecs);
}