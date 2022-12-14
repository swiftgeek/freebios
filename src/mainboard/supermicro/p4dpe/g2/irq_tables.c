/* This file was generated by getpir.c, do not modify! 
   (but if you do, please run checkpir on it to verify)
   Contains the IRQ Routing Table dumped directly from your memory , wich BIOS sets up

   Documentation at : http://www.microsoft.com/hwdev/busbios/PCIIRQ.HTM
*/

#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE, /* u32 signature */
	PIRQ_VERSION,   /* u16 version   */
	32+16*29,        /* there can be total 29 devices on the bus */
	0,           /* Where the interrupt router lies (bus) */
	0xf8,           /* Where the interrupt router lies (dev) */
	0,         /* IRQs devoted exclusively to PCI usage */
	0x8086,         /* Vendor */
	0x122e,         /* Device */
	0,         /* Crap (miniport) */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0x19,         /*  u8 checksum , this hase to set to some value that would give 0 after the sum of all bytes for this structure (including checksum) */
	{
		{0,0, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0x10, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x1,0xe8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x2,0x8, {{0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}}, 0x6, 0},
		{0x2,0x10, {{0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}}, 0x7, 0},
		{0x1,0xf8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x3,0x8, {{0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}}, 0x5, 0},
		{0x3,0x10, {{0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}, {0x68, 0xdcb8}}, 0xb, 0},
		{0,0x18, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x4,0xe8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x5,0x8, {{0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}}, 0x3, 0},
		{0x5,0x10, {{0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}}, 0x2, 0},
		{0x5,0x18, {{0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}}, 0x1, 0},
		{0x4,0xf8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x6,0x8, {{0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}}, 0x4, 0},
		{0x6,0x10, {{0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}, {0x69, 0xdcb8}}, 0x9, 0},
		{0,0x20, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x10,0xe8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x11,0x8, {{0x63, 0xdcb8}, {0x63, 0xdcb8}, {0x63, 0xdcb8}, {0x63, 0xdcb8}}, 0x8, 0},
		{0x10,0xf8, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x12,0x8, {{0x63, 0xdcb8}, {0x63, 0xdcb8}, {0x63, 0xdcb8}, {0x63, 0xdcb8}}, 0x7, 0},
		{0,0xf0, {{0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0x7,0x8, {{0x60, 0xdcb8}, {0x60, 0xdcb8}, {0x60, 0xdcb8}, {0x60, 0xdcb8}}, 0xa, 0},
		{0x7,0x10, {{0x61, 0xdcb8}, {0x61, 0xdcb8}, {0x61, 0xdcb8}, {0x61, 0xdcb8}}, 0xb, 0},
		{0x7,0x18, {{0x62, 0xdcb8}, {0x62, 0xdcb8}, {0x62, 0xdcb8}, {0x62, 0xdcb8}}, 0xc, 0},
		{0,0xe8, {{0x60, 0xdcb8}, {0, 0xdef8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0xe9, {{0, 0xdef8}, {0x63, 0xdcb8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
		{0,0xea, {{0, 0xdef8}, {0, 0xdef8}, {0x62, 0xdcb8}, {0, 0xdef8}}, 0, 0},
		{0,0xf8, {{0x62, 0xdcb8}, {0x61, 0xdcb8}, {0, 0xdef8}, {0, 0xdef8}}, 0, 0},
	}
};
