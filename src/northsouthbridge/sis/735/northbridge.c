/*
 * northbridge.c:        SiS 735 Northbridge Initialization
 *
 * Copyright 2002 International Business Machines
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 * Reference:
 *      1. SiS 735 Programing Guide
 *
 */

#include <printk.h>
#include <pciconf.h>
#include <subr.h>
#include <pci.h>
#include <pci_ids.h>

/* these functions query the hardware to figure out how much ram is in
 * the machine. They then place that information in the parameter block. 
 * This is kind of schizophrenic, but we do it this way because the 
 * functions that actually set the registers are kind of hairy, and 
 * we're not sure they can carry the full burden of also passing on 
 * the size information to the rest of the bootstrap. Besides, querying
 * hardware for ram sizes is trivial. 
 */

/* table for calculate the DRAM size, the unit is Mega Bytes */
const static int ramsizes[16] =
{
	8, 32, 32, 64, 16, 64, 64, 128,
	32, 128, 128, 256, 16, 1024, 256, 512
};
#define SIS735_BANKENABLE 0x64
#define SIS735_BANK0 0x60
#define SIS735_BANK1 0x61
#define SIS735_BANK2 0x62
#define SIS735_BANK3 0x63
unsigned 
long sizeram()
{
	struct pci_dev *pcidev;
	unsigned int dimm_slot, dimm_reg, sides;
	unsigned long total_size;
	u8 dram_status, dimm_status;

	if ((pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_735, NULL)) == NULL)
		return 0;

	pci_read_config_byte(pcidev, SIS735_BANKENABLE, &dram_status);
	dimm_status = dram_status & 0xF;

	for (dimm_slot = 0, total_size = 0, dimm_reg = SIS735_BANK0;
	     dimm_reg <= SIS735_BANK3; dimm_slot++, dimm_reg++) {
		u8 regval;
		if ((dimm_status & (1 << dimm_slot)) == 0)
			/* this DIMM slot does not have SDRAM installed */
			continue;

		pci_read_config_byte(pcidev, dimm_reg, &regval);

		/* is this DIMM single or double sided  ?? */
		if (regval & 0x20)
			sides = 2;
		else
			sides = 1;

		/* low-order 4 bits are a ram size */
		total_size += (ramsizes[regval & 0xf] * sides);
	}

	/* return the memory size in KB */
	total_size *= 1024;
	return total_size;
}

#ifdef HAVE_FRAMEBUFFER
void framebuffer_on()
{
	struct pci_dev *pcidev;
	u16 command;

	if ((pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_5591_AGP, NULL)) == NULL)
		return 0;

	pci_read_config_word(pcidev, 0x04, &command);
	command |= 0x20;
	pci_write_config_word(pcidev, 0x04, command);

	/* enable legacy VGA IO (0x3B0 - 0x3BB, 0x3C0 - 0x3DF) and MEM (0xA0000 - 0xBFFFF),
	   needed for XFree86 3.3.6 */
	pci_read_config_word(pcidev, 0x3e, &command);
	command |= 0x08;
	pci_write_config_word(pcidev, 0x3e, command);
}
#endif	/* HAVE_FRAMEBUFFER */
