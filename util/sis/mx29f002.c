/*
 * mx29f002.c: driver for MXIC MX29F002 flash models
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
 *	MX29F002/002N data sheet
 *
 * $Id: mx29f002.c,v 1.1 2000/11/06 01:53:36 ollie Exp $
 */

#include "flash.h"
#include "jedec.h"

int probe_29f002 (struct flashchip * flash)
{
	char * bios = flash->virt_addr;
	unsigned char id1, id2, id3;

	*(bios + 0x5555) = 0xAA;
	*(bios + 0x2AAA) = 0x55;
	*(bios + 0x5555) = 0x90;
    
	id1 = *(unsigned char *) bios;
	id2 = *(unsigned char *) (bios + 0x01);
 
	*bios = 0xF0;

	usleep(10);

	if (id1 == flash->manufacture_id && id2 == flash->model_id)
		return 1;

	return 0;
}

int erase_29f002 (struct flashchip * flash)
{
	char * bios = flash->virt_addr;

 again:
	*(bios + 0x555) = 0xF0;
	*(bios + 0x555) = 0xAA;
	*(bios + 0x2AA) = 0x55;
	*(bios + 0x555) = 0x80;
	*(bios + 0x555) = 0xAA;
	*(bios + 0x2AA) = 0x55;
	*(bios + 0x555) = 0x10;

	usleep(100);
	toggle_ready_jedec(bios);

	//   while ((*bios & 0x40) != 0x40)
	//;

#if 0
	toggle_ready_jedec(bios);
	*(bios + 0x0ffff) = 0x30;
	*(bios + 0x1ffff) = 0x30;
	*(bios + 0x2ffff) = 0x30;
	*(bios + 0x37fff) = 0x30;
	*(bios + 0x39fff) = 0x30;
	*(bios + 0x3bfff) = 0x30;
#endif

}

int write_29f002 (struct flashchip * flash, char * buf)
{
    int i;
    int total_size = flash->total_size * 1024, page_size = flash->page_size;
    char * bios = flash->virt_addr;
    char * dst = bios, * src = buf;

    *bios = 0xF0;
    usleep(10);
    erase_29f002(flash);
    //*bios = 0xF0;
#if 1
   printf ("Programming Page: ");
    for (i = 0; i < total_size; i++) {
	/* write to the sector */
	printf ("address: 0x%08lx", i);
	*(bios + 0x5555) = 0xAA;
	*(bios + 0x2AAA) = 0x55;
	*(bios + 0x5555) = 0xA0;
	*dst++ = 0x33;

	/* wait for Toggle bit ready */
	toggle_ready_jedec(dst);

	printf ("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    }
#endif
    printf("\n");
}
