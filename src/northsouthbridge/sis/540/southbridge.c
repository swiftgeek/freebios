
/*
 * Bootstrap code for the INTEL 
 * $Id: southbridge.c,v 1.4 2001/11/13 05:08:09 ollie Exp $
 *
 */

#ifndef lint
static char rcsid[] =
"$Id: southbridge.c,v 1.4 2001/11/13 05:08:09 ollie Exp $";
#endif


#include <printk.h>
#include <pciconf.h>
#include <subr.h>
#include <pci.h>
#include <pci_ids.h>
#include <arch/io.h>

void keyboard_on()
{
	u8 regval;
	struct pci_dev *pcidev;

	/* turn on sis630 keyboard/mouse controller */
	pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503, (void *)NULL);
	if (pcidev != NULL) {
		/* Register 0x47, Keyboard Controller */
		pci_read_config_byte(pcidev, 0x47, &regval);
		/* enable both integrated keyboard and PS/2 mouse controller */
		regval |= 0x0c;
		pci_write_config_byte(pcidev, 0x47, regval);
	}
	pc_keyboard_init();
}

void nvram_on()
{
	struct pci_dev *pcidev;

	/* turn on sis540 nvram. */
	pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503, (void *)NULL);
	if (pcidev != NULL) {
		/* Enable FFF80000 to FFFFFFFF decode. You have to also enable
		   PCI Posted write for devices on sourthbridge */
		pci_write_config_byte(pcidev, 0x40, 0x33);
		/* Flash can be flashed */
		pci_write_config_byte(pcidev, 0x45, 0x40);
		printk_debug("Enabled in SIS 503 regs 0x40 and 0x45\n");

	}
	printk_debug("Now try to turn off shadow\n");
#if !defined(STD_FLASH)
	/* turn off nvram shadow in 0xc0000 ~ 0xfffff, i.e. accessing segment C - F
	   is actually to the DRAM not NVRAM. For 512KB NVRAM case, this one should be
	   disabled */
	pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_540, (void *)NULL);
	printk_debug("device for SiS 540 is 0x%x\n", pcidev);
	if (pcidev != NULL) {
		/* read cycle goes to System Memory */
		/* write cycle goest to System Memory */
		pci_write_config_word(pcidev, 0x70, 0xFFFF);
		pci_write_config_word(pcidev, 0x72, 0xFFFF);
		pci_write_config_word(pcidev, 0x74, 0xFFFF);
		pci_write_config_byte(pcidev, 0x76, 0xFF);
		printk_debug("Shadow memory disabled in SiS 540\n");

	}
#endif
}

/* serial_irq_fixup: Enable Serial Interrupt. Serial interrupt is the IRQ line from SiS 950
 *	LPC to Host Controller. Serial IRQ is neceressary for devices on SiS 950
 *	ie.e floppy, COM, LPT etc
 */
static void
serial_irq_fixedup(void)
{
	struct pci_dev *pcidev;

	pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503, (void *)NULL);
	if (pcidev != NULL) {
		/* enable Serial Interrupt (SIRQ) */
		pci_write_config_byte(pcidev, 0x70, 0x80); 
		// skip the SMI, inta, etc. stuff. 
		// enable IRQs 7 to 1
		pci_write_config_byte(pcidev, 0x72, 0xfd);
		// enable IRQs 15 to 8
		pci_write_config_byte(pcidev, 0x73, 0xff);
	}
}

static void
acpi_fixup(void)
{
	struct pci_dev *pcidev;

	pcidev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503, (void *)NULL);
	if (pcidev != NULL) {
		unsigned char val;
		unsigned short acpibase = 0xc000, temp;
		int i;

		// the following is to turn off software watchdogs. 
		// we co-op the address space from c000-cfff here. Temporarily. 
		// Later, we need a better way to do this. 
		// But since Linux doesn't even understand this yet, no issue. 
		// Set a base address for ACPI of 0xc000
		pci_read_config_word(pcidev, 0x74, &temp);

		printk_debug("acpibase was 0x%x\n", temp);
		pci_write_config_word(pcidev, 0x74, acpibase);
		pci_read_config_word(pcidev, 0x74, &temp);
		printk_debug("acpibase is 0x%x\n", temp);

		// now enable acpi
		pci_read_config_byte(pcidev, 0x40, &val);
		printk_debug("acpi enable reg was 0x%x\n", val);
		val |= 0x80;
		pci_write_config_byte(pcidev, 0x40, val);
		pci_read_config_byte(pcidev, 0x40, &val);
		printk_debug("acpi enable reg after set is 0x%x\n", val);
		printk_debug("acpi status: word at 0x56 is 0x%x\n",
		       inw(acpibase+0x56));
		printk_debug("acpi status: byte at 0x4b is 0x%x\n", 
		       inb(acpibase + 0x4b));

		// now that it's on, get in there and call off the dogs. 
		// that's the recommended thing to do if MD40 iso on. 
		outw(0, acpibase + 0x56);
		// does this help too? 
		outb(0, acpibase + 0x4b);
		// ah ha! have to SET, NOT CLEAR!
		outb(0x40, acpibase + 0x56);
		printk_debug("acpibase + 0x56 is 0x%x\n", 
		       inb(acpibase+0x56));
		val &= (~0x80);
		pci_write_config_byte(pcidev, 0x40, val);
		pci_read_config_byte(pcidev, 0x40, &val);
		printk_debug("acpi disable reg after set is 0x%x\n", val);
	} else {
		printk_emerg("Can't find south bridge!\n");
	}
	
}

// simple fixup (which we hope can leave soon) for the sis southbridge part
void
final_southbridge_fixup()
{
	struct pci_dev *pcidev;

	serial_irq_fixedup();
	acpi_fixup();

	printk_debug("Southbridge fixup done for SIS 503\n");
}
