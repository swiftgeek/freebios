
/*
 * Bootstrap code for the INTEL 
 * $Id: northbridge.c,v 1.2 2000/10/17 03:24:23 rminnich Exp $
 *
 */

#ifndef lint
static char rcsid[] =
"$Id: northbridge.c,v 1.2 2000/10/17 03:24:23 rminnich Exp $";
#endif


#include <printk.h>
#include <pciconf.h>
#include <subr.h>
#include <pci.h>
#include <pci_ids.h>
#include <northsouthbridge/sis/630/param.h>

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
	32, 128, 128, 256, 16, 256, 256, 512
};
#define SIS630_BANKENABLE 0x63
#define SIS630_BANK0 0x60
#define SIS630_BANK1 0x61
#define SIS630_BANK2 0x62
#define SIS630_DIMM_LOCATION_FOR_SMA 0x65
unsigned long sizeram()
{
	struct pci_dev *pcidev;
	unsigned int dimm_slot, dimm_reg, sides;
	unsigned long total_size;
	u8 dram_status, dimm_status;
	u8 sma_enable, sma_size, sma_size_bits, sma_location;

	if ((pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_630, NULL)) == NULL)
		return 0;

	pci_read_config_byte(pcidev, SIS630_BANKENABLE, &dram_status);
	dimm_status = dram_status & 0x7;
	sma_enable = dram_status & 0x80;

	pci_read_config_byte(pcidev, SIS630_DIMM_LOCATION_FOR_SMA, &sma_location);
	sma_location &= 0x03;

	/* compute Shared Menory Area (SMA) size in Mega Bytes */
	sma_size_bits = (dram_status >> 4) & 0x7;
	if (sma_size_bits > 5)
		// this is invalid!
		sma_size = 0;
	else {
		sma_size = (2 << sma_size_bits);
	}

	for (dimm_slot = 0, total_size = 0, dimm_reg = SIS630_BANK0;
	     dimm_reg <= SIS630_BANK2; dimm_slot++, dimm_reg++) {
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

	/* the total memory visible to the system is physical memory installed minus the
	   amount used by VGA (sma_size) */
	total_size -= sma_size;

	/* return the memory size in KB */
	total_size *= 1024;
	return total_size;
}

#ifdef HAVE_FRAMEBUFFER

void framebuffer_on()
{
	unsigned long devfn = PCI_DEVFN(0, 0);
	//	unsigned int bus = 0;
	//	u8 dramstatus;
	u32 command;

#if 0
	/* No, you can not do this here, but WHY ??? */
	/* TODO:
	   1. clean up the memory footprint to make this work.
	   2. make the share size configurable.
	   3. use the information found from DRAM sizing to select whic DIMM is to be shared */
	pcibios_read_config_byte(0, devfn, SIS630_BANKENABLE, &dramstatus);
	dramstatus |= 0x90;
	pcibios_write_config_byte(0, devfn, SIS630_BANKENABLE, dramstatus);
#endif

	/* enable legacy VGA register (0x3?4, 0x3?5), not actually needed */
	devfn = PCI_DEVFN(2, 0);
	pcibios_read_config_dword(0, devfn, 0x3e, &command);
	command |= 0x08;
	pcibios_write_config_dword(0, devfn, 0x3e, command);
}

#endif	/* HAVE_FRAMEBUFFER */

#define RTABLE_DEST 0xf0000

void copy_irq_routing_table(void)
{
#ifdef SIS630
	memcpy((char *) RTABLE_DEST, &intel_irq_routing_table, intel_irq_routing_table.size);
#endif
}

