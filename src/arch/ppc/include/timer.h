/* $Id: timer.h,v 1.1 2003/04/15 18:29:11 rminnich Exp $ */
/* Copyright 2000  AG Electronics Ltd. */
/* This code is distributed without warranty under the GPL v2 (see COPYING) */

#ifndef _TIMER_H
#define __TIMER_H

unsigned get_hz(void);
unsigned ticks_since_boot(void);
void sleep_ticks(unsigned);

#endif