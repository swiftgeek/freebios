#if defined(IOAPIC)
#include <arch/ioapic.h>
#include <printk.h>

/* TODO: this must move to chip/intel */
/* we have to do more than we thought. I assumed Linux would do all the
 * interesting parts, and I was wrong. 
 */
struct ioapicreg {
	unsigned int reg;
	unsigned int value_low, value_high;
};
struct ioapicreg ioapicregvalues[] = {
#define ALL		(0xff << 24)
#define NONE		(0)
#define DISABLED	(1 << 16)
#define ENABLED		(0 << 16)
#define TRIGGER_EDGE	(0 << 15)
#define TRIGGER_LEVEL	(1 << 15)
#define POLARITY_HIGH	(0 << 13)
#define POLARITY_LOW	(1 << 13)
#define PHYSICAL_DEST	(0 << 11)
#define LOGICAL_DEST	(1 << 11)
#define ExtINT		(7 << 8)
#define NMI		(4 << 8)
#define SMI		(2 << 8)
#define INT		(1 << 8)
#if 0 /* L440GX */
	{0x00, DISABLED, NONE},
	{0x01, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x59, ALL},
	{0x02, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x51, ALL},
	{0x03, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x61, NONE},
	{0x04, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x69, ALL},
	{0x05, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x71, NONE},
	{0x06, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x79, NONE},
	{0x07, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x81, NONE},
	{0x08, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x89, ALL},
	{0x09, DISABLED, NONE},
	{0x0a, DISABLED, NONE},
	{0x0b, DISABLED, NONE},
	{0x0c, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x91, ALL},
	{0x0d, DISABLED, NONE},
	{0x0e, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x99, ALL},
	{0x0f, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xa1, ALL},
	{0x10, DISABLED, NONE},
	{0x11, DISABLED, NONE},
	{0x12, DISABLED, NONE},
	{0x13, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0xa9, ALL},
	{0x14, DISABLED, NONE},
	{0x15, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0xb1, ALL},
	{0x16, DISABLED, NONE},
	{0x17, DISABLED, NONE}
#endif
#if 0 /* tyan guinness */
	/* mask, trigger, polarity, destination, delivery, vector */
	{0x00, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|ExtINT|0x0,	ALL},
	{0x01, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x1,		ALL},
	{0x02, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x0,		ALL},
	{0x03, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x3,		ALL},
	{0x04, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x4,		ALL},
	{0x05, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x5,		ALL},
	{0x06, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x6,		ALL},
	{0x07, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x7,		ALL},
	{0x08, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x8,		ALL},
	{0x09, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0x9,		ALL},
	{0x0a, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xa,		ALL},
	{0x0b, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xb,		ALL},
	{0x0c, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xc,		ALL},
	{0x0d, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xd,		ALL},
	{0x0e, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xe,		ALL},
	{0x0f, ENABLED|TRIGGER_EDGE|POLARITY_HIGH|LOGICAL_DEST|INT|0xf,		ALL},
	{0x10, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0x10,	ALL},
	{0x11, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0x11,	ALL},
	{0x12, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0x12,	ALL},
	{0x13, ENABLED|TRIGGER_LEVEL|POLARITY_LOW|LOGICAL_DEST|INT|0x13,	ALL},
	{0x14, DISABLED, NONE},
	{0x14, DISABLED, NONE},
	{0x15, DISABLED, NONE},
	{0x16, DISABLED, NONE},
	{0x17, DISABLED, NONE},
#endif
#if 1
	/* mask, trigger, polarity, destination, delivery, vector */
	{0x00, DISABLED, NONE},
	{0x01, DISABLED, NONE},
	{0x02, DISABLED, NONE},
	{0x03, DISABLED, NONE},
	{0x04, DISABLED, NONE},
	{0x05, DISABLED, NONE},
	{0x06, DISABLED, NONE},
	{0x07, DISABLED, NONE},
	{0x08, DISABLED, NONE},
	{0x09, DISABLED, NONE},
	{0x0a, DISABLED, NONE},
	{0x0b, DISABLED, NONE},
	{0x0c, DISABLED, NONE},
	{0x0d, DISABLED, NONE},
	{0x0e, DISABLED, NONE},
	{0x0f, DISABLED, NONE},
	{0x10, DISABLED, NONE},
	{0x11, DISABLED, NONE},
	{0x12, DISABLED, NONE},
	{0x13, DISABLED, NONE},
	{0x14, DISABLED, NONE},
	{0x14, DISABLED, NONE},
	{0x15, DISABLED, NONE},
	{0x16, DISABLED, NONE},
	{0x17, DISABLED, NONE},
#endif
};

void setup_ioapic(void)
{
	int i;
	unsigned long value_low, value_high;
	unsigned long nvram = 0xfec00000;
	volatile unsigned long *l;
	struct ioapicreg *a = ioapicregvalues;

	l = (unsigned long *) nvram;
	for (i = 0; i < sizeof(ioapicregvalues) / sizeof(ioapicregvalues[0]);
	     i++, a++) {
		l[0] = (a->reg * 2) + 0x10;
		l[4] = a->value_low;
		value_low = l[4];
		l[0] = (a->reg *2) + 0x11;
		l[4] = a->value_high;
		value_high = l[4];
		if ((i==0) && (value_low == 0xffffffff)) {
			printk_warning("IO APIC not responding.\n");
			return;
		}
		printk_spew("for IRQ, reg 0x%08x value 0x%08x 0x%08x\n", 
			a->reg, a->value_low, a->value_high);
	}
}
#endif /* IOAPIC */