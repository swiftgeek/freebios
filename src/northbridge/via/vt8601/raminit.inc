/*
This software and ancillary information (herein called SOFTWARE )
called LinuxBIOS          is made available under the terms described
here.  The SOFTWARE has been approved for release with associated
LA-CC Number 00-34   .  Unless otherwise indicated, this SOFTWARE has
been authored by an employee or employees of the University of
California, operator of the Los Alamos National Laboratory under
Contract No. W-7405-ENG-36 with the U.S. Department of Energy.  The
U.S. Government has rights to use, reproduce, and distribute this
SOFTWARE.  The public may copy, distribute, prepare derivative works
and publicly display this SOFTWARE without charge, provided that this
Notice and any statement of authorship are reproduced on all copies.
Neither the Government nor the University makes any warranty, express 
or implied, or assumes any liability or responsibility for the use of
this SOFTWARE.  If SOFTWARE is modified to produce derivative works,
such modified SOFTWARE should be clearly marked, so as not to confuse
it with the version available from LANL.
 */
/* Copyright 2000, Ron Minnich, Advanced Computing Lab, LANL
 * rminnich@lanl.gov
 */
/*
 * 11/26/02 - kevinh@ispiri.com - The existing comments implied that
 * this didn't work yet.  Therefore, I've updated it so that it works
 * correctly - at least on my VIA epia motherboard.  64MB DIMM in slot 0.
 */

/* Added automatic detection of first equipped bank and its MA mapping type.
 * (Rest of configuration is done in C)
 * 5/19/03 by SONE Takeshi <ts1@tsn.or.jp>
 */

// Set to 1 if your DIMMs are PC133
// Note that I'm assuming CPU's FSB frequency is 133MHz. If your CPU runs
// at another bus speed, you might need to change some of register values.
#ifndef DIMM_PC133
#define DIMM_PC133 0
#endif

// Set to 1 if your DIMMs are CL=2
#ifndef DIMM_CL2
#define DIMM_CL2 0
#endif


/* Stable ~1 usec delay by hitting unused ISA port. */
#define UDELAY(x) movl $x,%ecx; 9: outb %al,$0x81; loop 9b

#define DIMMS_READ(x) \
        movl 0x00000000+x, %eax; \
        movl 0x10000000+x, %eax; \
        movl 0x20000000+x, %eax; \
        movl 0x30000000+x, %eax; \
        movl 0x40000000+x, %eax; \
        movl 0x50000000+x, %eax

#define DIMMS_WRITE(x) \
        movl %eax, 0x00000000+x; \
        movl %eax, 0x10000000+x; \
        movl %eax, 0x20000000+x; \
        movl %eax, 0x30000000+x; \
        movl %eax, 0x40000000+x; \
        movl %eax, 0x50000000+x

raminit:
	intel_chip_post_macro(0x35)

	// memory clk enable. We are not using ECC
	CS_WRITE($0x78, $0x01)
	// dram control, see the book. 
#if DIMM_PC133
	CS_WRITE($0x68, $0x52)
#else
        CS_WRITE($0x68, $0x42)
#endif
	// dram control, see the book. 
	CS_WRITE($0x6B, $0x0c)
	// Initial setting, 256MB in each bank, will be rewritten later.
	CS_WRITE($0x5A, $0x20)
	CS_WRITE($0x5B, $0x40)
	CS_WRITE($0x5C, $0x60)
	CS_WRITE($0x5D, $0x80)
	CS_WRITE($0x5E, $0xA0)
	CS_WRITE($0x5F, $0xC0)
        // It seems we have to take care of these 2 registers as if 
        // they are bank 6 and 7.
        CS_WRITE($0x56, $0xC0)
        CS_WRITE($0x57, $0xC0)

	// SDRAM in all banks
	CS_WRITE($0x60, $0x3F)
	// DRAM timing. I'm suspicious of this
	// This is for all banks, 64 is 0,1.  65 is 2,3. 66 is 4,5.
	// ras precharge 4T, RAS pulse 5T
	// cas2 is 0xd6, cas3 is 0xe6
	// we're also backing off write pulse width to 2T, so result is 0xee
#if DIMM_CL2
	CS_WRITE($0x64, $0xd4)
	CS_WRITE($0x65, $0xd4)
	CS_WRITE($0x66, $0xd4)
#else // CL=3
	CS_WRITE($0x64, $0xe4)
	CS_WRITE($0x65, $0xe4)
	CS_WRITE($0x66, $0xe4)
#endif

	// dram frequency select.
	// enable 4K pages for 64M dram. 
#if DIMM_PC133
	CS_WRITE($0x69, $0x3c)
#else
        CS_WRITE($0x69, $0xac)
#endif
	// refresh counter, disabled.
	CS_WRITE($0x6A, $0x00)
	// clkenable configuration. kevinh FIXME - add precharge
	CS_WRITE($0x6C, $0x00)
	// dram read latch delay of 1 ns, MD drive 8 mA,
	// high drive strength on MA[2:	13], we#, cas#, ras#
	// As per Cindy Lee, set to 0x37, not 0x57
	CS_WRITE($0x6D, $0x7f)

        /* Initialize all banks at once */

/* begin to initialize*/
	// I forget why we need this, but we do
	mov $0xa55a5aa5, %eax
        DIMMS_WRITE(0)
	
/* set NOP*/
	CS_WRITE($0x6C, $0x01)

/* wait 200us*/
	// You need to do the memory reference. That causes the nop cycle. 
        DIMMS_READ(0)
	UDELAY(400)

/* set precharge */
	CS_WRITE($0x6C, $0x02)

/* dummy reads*/
        DIMMS_READ(0)
	UDELAY(200)

/* set CBR*/
	CS_WRITE($0x6C, $0x04)
	
/* do 8 reads and wait >100us between each - from via*/
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)
        DIMMS_READ(0)
	UDELAY(200)

/* set MRS*/
	CS_WRITE($0x6c, $0x03)
#if DIMM_CL2
        DIMMS_READ(0x150)
#else // CL=3
        DIMMS_READ(0x1d0)
#endif
	UDELAY(200)

/* set to normal mode */
	CS_WRITE($0x6C, $0x08)
	movl $0x55aa55aa, %eax
        DIMMS_WRITE(0)
        DIMMS_READ(0)
	UDELAY(200)

	// Set the refresh rate. 
#if DIMM_PC133
	CS_WRITE($0x6A, $0x86)
#else
	CS_WRITE($0x6A, $0x65)
#endif
	// enable multi-page open
	CS_WRITE($0x6B, $0x0d)

        /* Begin auto-detection
         * Find the first bank with DIMM equipped. */

        /* Maximum possible memory in bank 0, none in other banks.
         * Starting from bank 0, we's fill 0 in these registers
         * until memory is found. */
	CS_WRITE($0x5A, $0xff)
	CS_WRITE($0x5B, $0xff)
	CS_WRITE($0x5C, $0xff)
	CS_WRITE($0x5D, $0xff)
	CS_WRITE($0x5E, $0xff)
	CS_WRITE($0x5F, $0xff)
	CS_WRITE($0x56, $0xff)
	CS_WRITE($0x57, $0xff)

        movl $0x5A, %ebx // first bank
1:
        /* Write different values to 0 and 8, then read from 0.
         * If values of address 0 match, we have something there. */
        movl $0x12345678, %eax
        movl %eax, 0
        movl $0x87654321, %edx
        movl %edx, 8
        movl 0, %edx
        cmpl %eax, %edx
        je 2f
        /* No memory in this bank. Tell it to the bridge. */
        movl %ebx, %eax
        xorl %edx, %edx
        PCI_WRITE_CONFIG_BYTE
        incl %ebx
        cmpl $0x60, %ebx
        jne 1b
        /* No memory at all! */
	CONSOLE_EMERG_TX_STRING($msg_nomem)
1:
        hlt
        jmp 1b
2:

        /* Detect MA mapping type of the first bank. */

        jmp raminit_ma
raminit_ma_reg_table:
        /* Values for MA type register to try */
        .word 0x0000, 0x8088, 0xe0ee
        .word 0xffff // end mark

raminit_ma:
        xorl %esi, %esi // highest address
        movl $raminit_ma_reg_table, %ebx
1:
        movw (%ebx), %cx
        cmpw $0xffff, %cx
        je raminit_ma_done
        movl $0x58, %eax
        PCI_WRITE_CONFIG_WORD

        xorl %eax, %eax
        movl %eax, (%eax)

        // Write to addresses with only one address bit on,
        // from 0x80000000 to 0x00000008 (lower 3 bits are ignored, assuming 
        // 64-bit bus).
        // Then what is read at address 0 is the value written to the lowest
        // address where it gets wrap-around. That address is either the size
        // of the bank, or a missing bit due to incorrect MA mapping.
        movl $0x80000000, %eax
2:
        movl %eax, (%eax)
        shrl $1, %eax
        cmpl $4, %eax
        jne 2b

        movl 0, %eax
        cmpl %eax, %esi
        jnc 3f

        // This is the current best MA mapping.
        // Save the address and its MA mapping value.
        movl %eax, %esi
        movl %ecx, %edi
3:
        incl %ebx
        incl %ebx
        jmp 1b


raminit_ma_done:
        // Set the best (hopefully correct) MA mapping type.
        movl $0x58, %eax
        movl %edi, %ecx
        PCI_WRITE_CONFIG_WORD

	CONSOLE_DEBUG_TX_STRING($msg_enabled)
	CONSOLE_DEBUG_TX_HEX32(%esi)
	CONSOLE_DEBUG_TX_STRING($msg_bytes)

        /*
         * We have the size of first bank in %esi, but throwing it away.
         * Sizing will again be done in C, because we'll configure the rest
         * of banks in there anyway.
         */

        //CALLSP(dumpnorth)

	intel_chip_post_macro(0x36)


        .section ".rom.data"
msg_nomem:
        .asciz "No memory\r\n"
msg_enabled:
        .asciz "Enabled first bank of RAM: 0x"
msg_bytes:
        .asciz " bytes\r\n"
        .previous
