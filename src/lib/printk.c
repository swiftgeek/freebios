/*
 *  blantantly copied from linux/kernel/printk.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 */

#ifndef lint
static char rcsid[] = "$Id: printk.c,v 1.8 2002/12/03 16:12:14 rminnich Exp $";
#endif

//typedef void * va_list;

#include <stdarg.h>
#include <subr.h>
#include <smp/spinlock.h>
#include <printk.h>

/* printk's without a loglevel use this.. */
#define DEFAULT_MESSAGE_LOGLEVEL 4 /* BIOS_WARNING */

/* We show everything that is MORE important than this.. */
#define MINIMUM_CONSOLE_LOGLEVEL 1 /* Minimum loglevel we let people use */

/* Keep together for sysctl support */

int console_loglevel = DEFAULT_CONSOLE_LOGLEVEL;
int default_message_loglevel = DEFAULT_MESSAGE_LOGLEVEL;
int minimum_console_loglevel = MINIMUM_CONSOLE_LOGLEVEL;
int default_console_loglevel = DEFAULT_CONSOLE_LOGLEVEL;

void display(char*);
extern int vtxprintf(void (*)(unsigned char), const char *, va_list);

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
	i = vtxprintf(display_tx_byte, fmt, args);
	va_end(args);

	display_tx_break();

	spin_unlock(&console_lock);

	return i;
}

#if (CONFIG_HEXDUMP == 1)
void hexdump(char *name, unsigned char *buffer, int size)
{
	int i;

	if (name)
		printk_info("==== %s ====\n", name);
	for(i = 0; i < size; i += 32) {
		int j;
		printk_info("%p:", buffer);
		for(j = 0; j < 32; j++) {
			printk_info("%02x ", *buffer++);
		}
		printk_info("\n");
	}
	printk_info("===\n");
			
}
#endif
