/*
 * am29f040.c: driver for programming AMD am29f040b models
 *
 *
 * Copyright 2000 Silicon Integrated System Corporation
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 * Reference:
 *	AMD Am29F040B data sheet
 * $Id: am29f040b.c,v 1.1 2000/11/06 01:53:36 ollie Exp $
 */

#include "flash.h"
#include "jedec.h"

static __inline__ erase_sector_29f040b (char * bios, unsigned long address)
{
	*(bios +   0x555) = 0xAA;
	*(bios +   0x2AA) = 0x55;
	*(bios +   0x555) = 0x80;
	*(bios +   0x555) = 0xAA;
	*(bios +   0x2AA) = 0x55;
	*(bios + address) = 0x30;

	sleep(2);

	/* wait for Toggle bit ready         */
	toggle_ready_jedec(bios + address);
}

static __inline__ write_sector_29f040b(char * bios, unsigned char * src,
				       unsigned char * dst, unsigned int page_size)
{
	int i;

	for (i = 0; i < page_size; i++) {
		printf("0x%08x", (unsigned long) dst - (unsigned long) bios);
	
		*(bios + 0x555) = 0xAA;
		*(bios + 0x2AA) = 0x55;
		*(bios + 0x555) = 0xA0;
		*dst++ = *src++;

		/* wait for Toggle bit ready */
		toggle_ready_jedec(bios);

		printf("\b\b\b\b\b\b\b\b\b\b");
	}
}

int probe_29f040b (struct flashchip * flash)
{
	char * bios = flash->virt_addr;
	unsigned char id1, id2;

	*(bios + 0x555) = 0xAA;
	*(bios + 0x2AA) = 0x55;
	*(bios + 0x555) = 0x90;
    
	id1 = *(unsigned char *) bios;
	id2 = *(unsigned char *) (bios + 0x01);

	*bios = 0xF0;

	usleep(10);
    
	if (id1 == flash->manufacture_id && id2 == flash->model_id)
		return 1;

	return 0;
}

int erase_29f040b (struct flashchip * flash)
{
	char * bios = flash->virt_addr;

	*(bios + 0x555) = 0xAA;
	*(bios + 0x2AA) = 0x55;
	*(bios + 0x555) = 0x80;
	*(bios + 0x555) = 0xAA;
	*(bios + 0x2AA) = 0x55;
	*(bios + 0x555) = 0x10;

	usleep(10);
	toggle_ready_jedec(bios);
}

int write_29f040b (struct flashchip * flash, char * buf)
{
	int i;
	int total_size = flash->total_size * 1024, page_size = flash->page_size;
	char * bios = flash->virt_addr;

	printf ("Programming Page: ");
	for (i = 0; i < total_size/page_size; i++) {
		/* erase the page before programming */
		erase_sector_29f040b(bios, i * page_size);

		/* write to the sector */
		printf ("%04d at address: ", i);
		write_sector_29f040b(bios, buf + i * page_size, bios + i * page_size,
				     page_size);
		printf ("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	}
	printf("\n");
}
