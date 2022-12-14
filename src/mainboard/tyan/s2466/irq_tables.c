/* PCI: Interrupt Routing Table found at 0x4011cf00 size = 224 */

#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	0x52495024, /* u32 signature */
	0x0100,     /* u16 version   */
	224,        /* u16 Table size 32+(16*devices)  */
	0x00,       /* u8 Bus 0 */
	0x3b,       /* u8 Device 1, Function 0 */
	0x0000,     /* u16 reserve IRQ for PCI */
	0x1022,     /* u16 Vendor */
	0x7400,     /* Device ID */
	0x00000000, /* u32 miniport_data */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0x52,   /*  u8 checksum - mod 256 checksum must give zero */
	{  /* bus, devfn, {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap}, slot, rfu  */
	    {0x00, 0x40, {{0x01, 0xdef8}, {0x02, 0xdef8}, {0x03, 0xdef8}, {0x04, 0xdef8}}, 0x01,  0x00},
	    {0x00, 0x48, {{0x02, 0xdef8}, {0x03, 0xdef8}, {0x04, 0xdef8}, {0x01, 0xdef8}}, 0x02,  0x00},
	    {0x02, 0x20, {{0x01, 0xdef8}, {0x02, 0xdef8}, {0x03, 0xdef8}, {0x04, 0xdef8}}, 0x03,  0x00},
	    {0x02, 0x28, {{0x02, 0xdef8}, {0x03, 0xdef8}, {0x04, 0xdef8}, {0x01, 0xdef8}}, 0x04,  0x00},
	    {0x02, 0x30, {{0x03, 0xdef8}, {0x04, 0xdef8}, {0x01, 0xdef8}, {0x02, 0xdef8}}, 0x05,  0x00},
	    {0x02, 0x38, {{0x04, 0xdef8}, {0x01, 0xdef8}, {0x02, 0xdef8}, {0x03, 0xdef8}}, 0x06,  0x00},
	    {0x00, 0x80, {{0x02, 0xdef8}, {0x03, 0xdef8}, {0x04, 0xdef8}, {0x01, 0xdef8}}, 0x00,  0x00},
	    {0x00, 0x00, {{0x00, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}}, 0x00,  0x00},
	    {0x00, 0x08, {{0x02, 0xdef8}, {0x03, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}}, 0x00,  0x00},
	    {0x01, 0x28, {{0x03, 0xdef8}, {0x04, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}}, 0x0d,  0x00},
	    {0x02, 0x00, {{0x00, 0xdef8}, {0x00, 0xdef8}, {0x00, 0xdef8}, {0x04, 0xdef8}}, 0x00,  0x00},
	    {0x02, 0x40, {{0x04, 0xdef8}, {0x04, 0xdef8}, {0x04, 0xdef8}, {0x04, 0xdef8}}, 0x00,  0x00}
	}
};
