#include <stdio.h>
#include <pci/pci.h>
#include "pci.h"

#define PCITAG struct pci_filter *

#define DEBUG_PCI 1

struct pci_access *pacc;
struct pci_dev *dev;

struct pci_filter ltag;


int pciNumBuses = 0;

int pciInit(void)
{
	pacc = pci_alloc();

	pci_init(pacc);
	pci_scan_bus(pacc);
	for (dev = pacc->devices; dev; dev = dev->next) {
		pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES);
	}
	return 0;
}

int pciExit(void)
{
	pci_cleanup(pacc);
	return 0;
}

PCITAG findPci(unsigned short bx)
{
	PCITAG tag = &ltag;

	int bus = (bx >> 8) & 0xFF;
	int slot = (bx >> 3) & 0x1F;
	int func = bx & 0x7;

	tag->bus = bus;
	tag->slot = slot;
	tag->func = func;

	if (pci_get_dev(pacc, bus, slot, func))
		return tag;

	return NULL;
}

u32 pciSlotBX(PCITAG tag)
{
	return (tag->bus << 8) | (tag->slot << 3) | (tag->func);
}

u8 pciReadByte(PCITAG tag, u32 idx)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		return pci_read_byte(d, idx);
#ifdef DEBUG_PCI
	printf("PCI: device not found while read byte (%x:%x.%x)\n",
	       tag->bus, tag->slot, tag->func);
#endif
	return 0;
}

u16 pciReadWord(PCITAG tag, u32 idx)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		return pci_read_word(d, idx);
#ifdef DEBUG_PCI
	printf("PCI: device not found while read word (%x:%x.%x)\n",
	       tag->bus, tag->slot, tag->func);
#endif
	return 0;
}

u32 pciReadLong(PCITAG tag, u32 idx)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		return pci_read_long(d, idx);
#ifdef DEBUG_PCI
	printf("PCI: device not found while read long (%x:%x.%x)\n",
	       tag->bus, tag->slot, tag->func);
#endif
	return 0;
}


void pciWriteLong(PCITAG tag, u32 idx, u32 data)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		pci_write_long(d, idx, data);
#ifdef DEBUG_PCI
	else
		printf
		    ("PCI: device not found while write long (%x:%x.%x)\n",
		     tag->bus, tag->slot, tag->func);
#endif
}

void pciWriteWord(PCITAG tag, u32 idx, u16 data)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		pci_write_word(d, idx, data);
#ifdef DEBUG_PCI
	else
		printf
		    ("PCI: device not found while write word (%x:%x.%x)\n",
		     tag->bus, tag->slot, tag->func);
#endif

}

void pciWriteByte(PCITAG tag, u32 idx, u8 data)
{
	struct pci_dev *d;
	if ((d = pci_get_dev(pacc, tag->bus, tag->slot, tag->func)))
		pci_write_long(d, idx, data);
#ifdef DEBUG_PCI
	else
		printf
		    ("PCI: device not found while write long (%x:%x.%x)\n",
		     tag->bus, tag->slot, tag->func);
#endif
}
