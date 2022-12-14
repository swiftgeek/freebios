/* This file was generated by getpir.c, do not modify! 
   (but if you do, please run checkpir on it to verify)
   Contains the IRQ Routing Table dumped directly from your memory , wich BIOS sets up

   Documentation at : http://www.microsoft.com/hwdev/busbios/PCIIRQ.HTM
*/
#define IRQ_SLOT_COUNT 19
#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE, /* u32 signature */
	PIRQ_VERSION,   /* u16 version   */
	32+16*19,        /* there can be total 19 devices on the bus */
	0,           /* Where the interrupt router lies (bus) */
	0x38,           /* Where the interrupt router lies (dev) */
	0,         /* IRQs devoted exclusively to PCI usage */
	0x8086,         /* Vendor */
	0x122e,         /* Device */
	0,         /* Crap (miniport) */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0x72,         /*  u8 checksum , this hase to set to some value that would give 0 after the sum of all bytes for this structure (including checksum) */
	{
		{0,0x80, {{0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}}, 0, 0},
		{0,0x48, {{0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}}, 0x1, 0},
		{0,0x50, {{0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}}, 0x2, 0},
		{0,0x58, {{0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}, {0x61, 0xdea0}}, 0x3, 0},
		{0,0x60, {{0x63, 0xdea0}, {0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}}, 0x4, 0},
		{0,0x38, {{0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}}, 0, 0},
		{0,0xa0, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x50, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x88, {{0x62, 0xdea0}, {0x63, 0xdea0}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x98, {{0x61, 0xdea0}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x90, {{0x60, 0xdea0}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x78, {{0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}}, 0, 0},
		{0x1,0x48, {{0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}}, 0x1, 0},
		{0x1,0x50, {{0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}}, 0x2, 0},
		{0x1,0x58, {{0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}, {0x61, 0xdea0}}, 0x3, 0},
		{0x1,0x60, {{0x63, 0xdea0}, {0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}}, 0x4, 0},
		{0x1,0x68, {{0x60, 0xdea0}, {0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}}, 0x5, 0},
		{0x1,0x70, {{0x61, 0xdea0}, {0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}}, 0x6, 0},
		{0x1,0x78, {{0x62, 0xdea0}, {0x63, 0xdea0}, {0x60, 0xdea0}, {0x61, 0xdea0}}, 0x7, 0},
	}
};
