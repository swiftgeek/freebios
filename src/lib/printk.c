/*
 *  blantantly copied from linux/kernel/printk.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 */

#ifndef lint
static char rcsid[] = "$Id: printk.c,v 1.3 2001/08/08 02:45:09 ebiederm Exp $";
#endif

//typedef void * va_list;

#include <stdarg.h>
#include <smp/spinlock.h>

static char buf[1024];

/* printk's without a loglevel use this.. */
#define DEFAULT_MESSAGE_LOGLEVEL 4 /* BIOS_WARNING */

/* We show everything that is MORE important than this.. */
#define MINIMUM_CONSOLE_LOGLEVEL 1 /* Minimum loglevel we let people use */

#ifndef DEFAULT_CONSOLE_LOGLEVEL
#define DEFAULT_CONSOLE_LOGLEVEL 8 /* anything MORE serious than BIOS_SPEW */
#endif

/* Keep together for sysctl support */

int console_loglevel = DEFAULT_CONSOLE_LOGLEVEL;
int default_message_loglevel = DEFAULT_MESSAGE_LOGLEVEL;
int minimum_console_loglevel = MINIMUM_CONSOLE_LOGLEVEL;
int default_console_loglevel = DEFAULT_CONSOLE_LOGLEVEL;

void display(char*);
extern int vsprintf(char *buf, const char *, va_list);

spinlock_t console_lock = SPIN_LOCK_UNLOCKED;

int do_printk(int msg_level, const char *fmt, ...)
{
	va_list args;
	int i;

	if (msg_level >= console_loglevel) {
		return 0;
	}

	spin_lock(&console_lock);

	va_start(args, fmt);
	i = vsprintf(buf, fmt, args); /* hopefully i < sizeof(buf)-4 */
	va_end(args);

	display(buf);

	spin_unlock(&console_lock);

	return i;
}

