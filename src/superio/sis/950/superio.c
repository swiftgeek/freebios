#ifndef lint
static char rcsid[] = "$Id: superio.c,v 1.5 2000/12/07 07:34:40 ollie Exp $";
#endif

// just define these here. We may never need them anywhere else
#define PNP_COM1_DEVICE 0x1
#define PNP_COM2_DEVICE 0x2

#include <subr.h>
#include <cpu/p5/io.h>

void
enter_pnp(void)
{
	// unlock it XXX make this a subr at some point 
	outb(0x87, 0x2e);
	outb(0x01, 0x2e);
	outb(0x55, 0x2e);
	outb(0x55, 0x2e);
}

void
exit_pnp(void)
{
	/* all done. */
	// select configure control
	outb(2, 0x2e);
	outb(2, 0x2f);
}

#ifdef MUST_ENABLE_FLOPPY
void
enable_floppy(void)
{
	/* now set the LDN to floppy LDN */
	outb(0x7, 0x2e);	/* pick reg. 7 */
	outb(0x0, 0x2f);	/* LDN 0 to reg. 7 */

	/* now select register 0x30, and set bit 1 in that register */
	outb(0x30, 0x2e);
	outb(0x1, 0x2f);
}
#endif /* MUST_ENABLE_FLOPPY */

void
enable_com(int com)
{
	unsigned char b;
	/* now set the LDN to com LDN */
	outb(0x7, 0x2e);	/* pick reg. 7 */
	outb(com, 0x2f);	/* LDN 1,2 to reg. 7 */

	/* now select register 0x30, and set bit 1 in that register */
	outb(0x30, 0x2e);
	outb(0x1, 0x2f);

	/* set CLKIN frequence to 24 MHZ */
	outb(0x24, 0x2e);
	b = inb(0x2f) | 0xfd;
	outb(0x24, 0x2e);
	outb(b, 0x2f);
}

#ifdef MUST_ENABLE_LPT
void
enable_lpt(void)
{
	/* now set the LDN to floppy LDN */
	outb(0x7, 0x2e);	/* pick reg. 7 */
	outb(0x3, 0x2f);	/* LDN 3 to reg. 7 */

	/* now select register 0x30, and set bit 1 in that register */
	outb(0x30, 0x2e);
	outb(0x1, 0x2f);
}
#endif /* MUST_ENABLE_LPT */

void
final_superio_fixup(void)
{
	enter_pnp();

#ifdef MUST_ENABLE_FLOPPY
	enable_floppy();
#endif /* MUST_ENABLE_LPT */

	enable_com(PNP_COM1_DEVICE);
	enable_com(PNP_COM2_DEVICE);

#ifdef MUST_ENABLE_LPT
	enable_lpt();
#endif /* MUST_ENABLE_LPT */

	exit_pnp();
}
