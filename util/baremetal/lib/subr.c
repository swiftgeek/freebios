/*
 * Bootstrap code for the INTEL 
 * $Id: subr.c,v 1.1 2002/11/12 17:20:38 pyro9 Exp $
 *
 */

#ifndef lint
static char rcsid[] = "$Id: subr.c,v 1.1 2002/11/12 17:20:38 pyro9 Exp $";
#endif

#include <config.h>
#include <arch/io.h>

#include <printk.h>
#include <subr.h>
#include <string.h>
#include <pc80/mc146818rtc.h>

#ifdef SERIAL_CONSOLE
#include <serial_subr.h>
#endif
#ifdef VIDEO_CONSOLE
#include <video_subr.h>
#endif
#ifdef LOGBUF_CONSOLE
#include <logbuf_subr.h>
#endif

#define SERIAL_CONSOLE
// initialize the display
void displayinit(void)
{

#ifdef VIDEO_CONSOLE
	video_init();
#endif
#ifdef SERIAL_CONSOLE
	ttys0_init();
#endif
}

static void __display_tx_byte(unsigned char byte)
{
#ifdef VIDEO_CONSOLE
	video_tx_byte(byte);
#endif
#ifdef SERIAL_CONSOLE
	ttys0_tx_byte(byte);
#endif
#ifdef SROM_CONSOLE
	srom_tx_byte(byte);
#endif
#ifdef LOGBUF_CONSOLE
	logbuf_tx_byte(byte);
#endif
}

void display_tx_break(void)
{
}

void display_tx_byte(unsigned char byte)
{
	if (byte == '\n')
		__display_tx_byte('\r');
	__display_tx_byte(byte);
}

void display(char *string)
{
	while(*string) {
		display_tx_byte(*string);
		string++;
	}
	display_tx_break();
}

void error(char errmsg[])
{
	display(errmsg);
	post_code(0xff);
	while (1);		/* Halt */
}

/*
 *    Write POST information
 */
void post_code(uint8_t value)
{
#if SERIAL_POST
	unsigned long hi, lo;
	// DAMMIT! This just broke!
	//rdtsc(lo, hi);
	printk_info("POST: 0x%02x, TSC Lo: %d, Hi: %d\n",
	       value, lo, hi);
#endif
	outb(value, 0x80);
}

