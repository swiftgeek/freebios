/* This file was generated by getpir.c, do not modify! 
   (but if you do, please run checkpir on it to verify)
   Contains the IRQ Routing Table dumped directly from your memory , wich BIOS sets up

   Documentation at : http://www.microsoft.com/hwdev/busbios/PCIIRQ.HTM
*/

#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE, /* u32 signature */
	PIRQ_VERSION,   /* u16 version   */
	32+16*6,        /* there can be total 6 devices on the bus */
	0,           /* Where the interrupt router lies (bus) */
	0x90,           /* Where the interrupt router lies (dev) */
	0x800,         /* IRQs devoted exclusively to PCI usage */
	0x1078,         /* Vendor */
	0x2,         /* Device */
	0,         /* Crap (miniport) */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0x3b,         /*  u8 checksum , this hase to set to some value that would give 0 after the sum of all bytes for this structure (including checksum) */
	{
		{0,0x70, {{0x2, 0xdeb8}, {0x1, 0xdeb8}, {0x4, 0xdeb8}, {0x3, 0xdeb8}}, 0x1, 0},
		{0,0x78, {{0x3, 0xdeb8}, {0x2, 0xdeb8}, {0x1, 0xdeb8}, {0x4, 0xdeb8}}, 0x2, 0},
		{0,0x68, {{0x4, 0xdeb8}, {0x3, 0xdeb8}, {0x2, 0xdeb8}, {0x1, 0xdeb8}}, 0x3, 0},
		{0,0x60, {{0x1, 0xdeb8}, {0x4, 0xdeb8}, {0x3, 0xdeb8}, {0x2, 0xdeb8}}, 0x4, 0},
		{0,0x88, {{0x4, 0xdeb8}, {0x4, 0xdeb8}, {0x4, 0xdeb8}, {0x4, 0xdeb8}}, 0x5, 0},
		{0,0x80, {{0x1, 0xdeb8}, {0x1, 0xdeb8}, {0x1, 0xdeb8}, {0x1, 0xdeb8}}, 0, 0},
	}
};
