#include <pci.h>
#include <pci_ids.h>
#include <pc80/keyboard.h>
#include <printk.h>

void
southbridge_fixup()
{
    struct pci_dev *pcidev;
    
    pcidev = pci_find_device(PCI_VENDOR_ID_ACER, 
	PCI_DEVICE_ID_ACER_M1535D, (void *)NULL);
    if (!pcidev) {
	printk(KERN_ERR __FUNCTION__ "no southbridge for 0x%x:0x%x\n",
	    PCI_VENDOR_ID_ACER, PCI_DEVICE_ID_ACER_M1535D);
	return;
    }
    /* enable legacy decode */
    pci_write_config_dword(pcidev, 0x70, 0xffffffff);
    
    /* ENABLE SERIAL IRQ */
    pci_write_config_byte(pcidev, 0x70, 0x8);
    
    /* ENABLE IDE CONTROLLER */
    pci_write_config_byte(pcidev, 0x58, 0x4c);
    
}

void nvram_on()
{
        struct pci_dev *pcidev;

        pcidev = pci_find_device(PCI_VENDOR_ID_ACER, 
	    PCI_DEVICE_ID_ACER_M1535D, (void *)NULL);
	if (!pcidev) {
	    printk(KERN_ERR __FUNCTION__ "no southbridge for 0x%x:0x%x\n",
		    PCI_VENDOR_ID_ACER, PCI_DEVICE_ID_ACER_M1535D);
		    return;
	}
	/* turn on the rom at the high addresses, i.e. 0xfff80000 - 0xffffffff */
	/* also make it writeable */
	/* 0x47 is the register. the 0x47 value means: writeenable, enable addresses 
	 * 0xfffc0000-0xfffdffff, 0xfffe0000-0xfffeffff, 0xffff0000-0xffffffff */
	pci_write_config_byte(pcidev, 0x47, 0x47);
	pci_write_config_byte(pcidev, 0x70, 1);
	
	/* ENABLE 8 MBIT FLASH ROM FUNCTION */
	pci_write_config_byte(pcidev, 0x4E, 0x2);
	
}


void keyboard_on()
{
}

