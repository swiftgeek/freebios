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


/** Start code to put an i386 or later processor into 32-bit 
 * protected mode. 
 */

/* .section ".rom.text" */
#include <arch/rom_segs.h>
.code16
.globl	EXT(_start)
.type EXT(_start), @function

EXT(_start): 
	cli

/* thanks to kmliu@sis.tw.com for this TBL fix ... */
/**/
/* IMMEDIATELY invalidate the translation lookaside buffer before executing*/
/* any further code.  Even though paging is disabled we could still get*/
/*false address translations due to the TLB if we didn't invalidate it.*/
/**/
	xorl	%eax, %eax
	movl	%eax, %cr3    /* Invalidate TLB*/

	/* invalidate the cache */
	invd 

	/* Note: gas handles memory addresses in 16 bit code very poorly.
	 * In particular it doesn't appear to have a directive allowing you
	 * associate a section or even an absolute offset with a segment register.
	 *
	 * This means that anything except cs:ip relative offsets are
	 * a real pain in 16 bit mode.  And explains why it is almost
	 * imposible to get gas to do lgdt correctly.
	 *
	 * One way to work around this is to have the linker do the
	 * math instead of the assembler.  This solves the very
	 * pratical problem of being able to write code that can
	 * be relocated.
	 *
	 * An lgdt call before we have memory enabled cannot be 
	 * position independent, as we cannot execute a call
	 * instruction to get our current instruction pointer.
	 * So while this code is relocateable it isn't arbitrarily
	 * relocatable.
	 *
	 * The criteria for relocation have been relaxed to their 
	 * utmost, so that we can use the same code for both
	 * our initial entry point and startup of the second cpu.
	 * The code assumes when executing at _start that:
	 * (((cs & 0xfff) == 0) and (ip == _start & 0xffff))
	 * or
	 * ((cs == anything) and (ip == 0)).
	 *
	 * The restrictions in reset16.inc mean that _start initially
	 * must be loaded at or above 0xffff0000 or below 0x100000.
	 *
	 * The linker scripts computs gdtptr16_offset by simply returning
	 * the low 16 bits.  This means that the intial segment used
	 * when start is called must be 64K aligned.  This should not
	 * restrict the address as the ip address can be anything.
	 */

	movw	%cs, %ax
	shlw	$4, %ax
	movw	$EXT(gdtptr16_offset), %bx
	subw	%ax, %bx
	data32  lgdt %cs:(%bx)

	movl	%cr0, %eax
	andl	$0x7FFAFFD1, %eax /* PG,AM,WP,NE,TS,EM,MP = 0 */
	orl	$0x60000001, %eax /* CD, NW, PE = 1 */
	movl	%eax, %cr0

	/* Now that we are in protected mode jump to a 32 bit code segment. */
	data32	ljmp	$ROM_CODE_SEG, $__protected_start

/** The gdt has a 4 Gb code segment at 0x10, and a 4 GB data segment
 * at 0x18; these are Linux-compatible. 
 */

.align	4
.globl EXT(gdtptr16)
EXT(gdtptr16):
	.word	gdt_end - gdt -1 /* compute the table limit */
	.long	gdt		 /* we know the offset */

.globl EXT(_estart)
EXT(_estart):
	.code32

