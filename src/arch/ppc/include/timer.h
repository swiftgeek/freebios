/* $Id: timer.h,v 1.2 2003/06/06 14:38:08 jarrah Exp $ */
/* Copyright 2000  AG Electronics Ltd. */
/* This code is distributed without warranty under the GPL v2 (see COPYING) */

#ifndef _TIMER_H
#define __TIMER_H

unsigned get_hz(void);
unsigned ticks_since_boot(void);
void sleep_ticks(unsigned);
void udelay(int);

#endif
