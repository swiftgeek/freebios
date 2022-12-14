/* 
    freebios/src/mainboard/cocom/voyager2/mainboard.c

    FROM: 
    Copyright (c) 2002 Christer Weinigel <wingel@hack.org>

    Mainboard fixup for the advantech pcm-5823
*/

#include <printk.h>
#include <pci.h>
#include <pci_ids.h>
#include <cpu/p5/io.h>

#include <types.h>

void
mainboard_fixup()
{

}

void
final_mainboard_fixup()
{
#if 0
	struct pci_dev *dev;
	int i;
#endif

	void final_southbridge_fixup(void);
	final_southbridge_fixup();

	printk_info("Final mainboard fixup\n");

#if 0
        dev = pci_find_slot(0, PCI_DEVFN(0x0f, 0));
        if (dev) {
                printk_debug("nano: Setting eth0 IRQ to %d (INTB)\n",
					CS5530_INTB);
                pci_write_config_byte(dev, PCI_INTERRUPT_LINE, CS5530_INTB);
        }
#endif
}

