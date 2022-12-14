#include <arch/pirq_routing.h>

#define CHECKSUM 0xe6
const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE,	/* u32 signature */
	PIRQ_VERSION,	/* u16 version   */
	32+16*5,	/* there can be total 5 devices on the bus */
	0x00,		/* Bus 0 */
	0x08,		/* Device 1, Function 0 */
	0x0A20,		/* reserve IRQ 11, 9, 5, for PCI */
	0x1039,		/* Silicon Integrated System */
	0x0008,		/* SiS 85C503/5513 ISA Bridge */
	0x00,		/*  u8 miniport_data  - "crap" */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	CHECKSUM,	/*  u8 checksum       - mod 256 checksum must give zero */
	{
		/* bus, devfn, {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap}, slot, rfu  */
		{0x00, 0x58, {{0x43, 0xdef8}, {0x44, 0xdef8}, {0x41, 0xdef8}, {0x42, 0xdef8}},
		 0x01, 0x00},
		{0x00, 0x60, {{0x44, 0xdef8}, {0x41, 0xdef8}, {0x42, 0xdef8}, {0x43, 0xdef8}},
		 0x02, 0x00},
		{0x00, 0x01, {{0x61, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}},
		 0x00, 0x00},
		{0x00, 0x10, {{0x41, 0xdef8}, {0x42, 0xdef8}, {0x43, 0xdef8}, {0x44, 0xdef8}},
		 0x00, 0x00},
		{0x00, 0x0a, {{0x41, 0xdef8}, {0x42, 0xdef8}, {0x43, 0xdef8}, {0x44, 0xdef8}},
		 0x00, 0x00},
	}
};
