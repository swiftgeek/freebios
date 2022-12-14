/*
 * raminit.inc:	Setting registers to their recommended values for SiS 730.
 *		Since we have inited the DRAM in IPL it is not neceressary
 *		to do "raminit" here any more.
 *
 *
 * Copyright 2000 Silicon Integrated Systems Corporation
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 * Reference:
 *	1. SiS 730S Data Sheet, Rev. 1.0, Oct. 31, 2000
 *	2. SiS 730S Register Recommended Setting
 *	   Rev 1.0, Oct. 4, 2000
 *
 * $Id: raminit.inc,v 1.4 2002/05/27 02:15:09 ollie Exp $
 */

#define PCI_COMMAND_PORT	0xcf8
#define PCI_DATA_PORT		0xcfc

#define NORTH_BRIDGE_BASE_ADDR	0x80000000
#define LPC_BRIDGE_BASE_ADDR	0x80000800

register_setting_start:
	movl	$northbridge_init_table, %esi
	movl	$(northbridge_init_table_end - northbridge_init_table), %ecx
	shrl	$0x01, %ecx
	
init_northbridge:
	lodsw	(%esi), %ax			# load the register address/value to %ax
	xchgb	%al, %ah			# exchange address/values for write_common

write_northbridge_register:			
	/* Input: AH - register number. AL - register value. */
	movl	$NORTH_BRIDGE_BASE_ADDR, %edx

	movl	%eax, %ebx			# Save %eax to %ebx.

	movzbl	%bh, %eax			# add register address to
	addl	%edx, %eax			# PCI base address

	movw	$PCI_COMMAND_PORT, %dx
	outl	%eax, %dx

	movw	$PCI_DATA_PORT, %dx
	andb	$0x03, %al
	addb	%al, %dl
	movb	%bl, %al
	outb	%al, %dx
	loopnz	init_northbridge

#ifdef DISABLE_INTERNAL_DEVICES
	movw	$0x7c0e, %ax			# Writting undocumented LPC register
write_lpc_register:
	/* Input: AH - register number. AL - register value. */
	movl	$LPC_BRIDGE_BASE_ADDR, %edx
	movl	%eax, %ebx			# Save %eax to %ebx.

	movzbl	%bh, %eax			# add register address to
	addl	%edx, %eax			# PCI base address

	movw	$PCI_COMMAND_PORT, %dx
	outl	%eax, %dx

	movw	$PCI_DATA_PORT, %dx
	andb	$0x03, %al
	addb	%al, %dl
	movb	%bl, %al
	outb	%al, %dx
#endif /* DISABLE_INTERNAL_DEVICES */

	jmp	register_setting_end

#include "730s_regs.inc"

register_setting_end:
