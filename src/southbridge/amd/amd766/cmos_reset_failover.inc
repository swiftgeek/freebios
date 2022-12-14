/* The algorithm is as follows:
 *
 * Step 1:  Test for cpu reset
 *     That is, did I just boot or is this a later boot since power on.
 *     The result of this test in %al
 *     %al == 1 -- We are rebooting
 *     %al == 0 -- This is the initial boot
 *
 * Step 2:  Cpu filter
 *     On an initial boot if we are not the bootstrap CPU go to
 *     sleep.
 *
 * Step 3:  Test for CMOS validity.
 *      On an initial boot if the CMOS checksum or the CMOS error
 *      condition is signaled clear the CMOS ram.
 *
 * Step 4:  Test for which copy of linuxbios to boot.
 *     We use 2 bits of CMOS ram.
 *     Bit 0: Initial boot direction
 *            0 - Boot the failsafe image.
 *            1 - Boot the other image.
 *     Bit 1: Reboot direction
 *            0 - Boot the failsafe image.
 *            1 - Boot the other image.
 *
 *     On initial boot we read bit0, and write it to bit1, and clear
 *     bit0.  
 *
 *     On a reboot the bits are not touched.
 *     
 *     Then the appropriate image is jumped to.
 *
 *    
 */
#include <pc80/mc146818rtc.h>
#include <part/fallback_boot.h>


	testb	%al, %al
	jz	__failover_boot

__failover_reset:
	movb	$RTC_BOOT_BYTE, %al
	outb	%al, $0x70
	inb	$0x71, %al
	testb	$(1<<1), %al
	jnz	__normal_image
	jmp	__cpu_reset

__failover_boot:
