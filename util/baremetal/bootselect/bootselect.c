/************************************************************************
 *
 * bootselect.c
 *	A standalone rom image selector for LinuxBIOS
 *
 * Copyright 2002 Steven James <pyro@linuxlabs.com> and LinuxLabs
 * http://www.linuxlabs.com
 *
 * Licensed under the GNU General Public License (GPL) v2 or later
 *
 **********************************************************************/


#include <arch/io.h>
#include <printk.h>
#include <rom/read_bytes.h>
#include <boot/elf.h>
#include <preboot.h>


#define DPRINTF( x... ) 
//#define DPRINTF printk

char buffer[16];

extern struct stream rom_stream;

inline void reset(void)
{
	outb(0x0e, 0xcf9);
}

int main(void) {
	int blocks;


	while(1) {
		printk("Welcome to the LinuxLabs boot chooser!\n");

		DPRINTF("Got lbmem struct: %08x\n", (unsigned int) lbmem);

		switch(choose_stream(&rom_stream)) {
			case -1:
				return(-1);
				break;
			case -2:
				reset();
				break;

			default:
				elfboot(&rom_stream, preboot_param);
				break;
		}
	}

	outb(0x0e, 0x3f9);

}

