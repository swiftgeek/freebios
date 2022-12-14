/*
 * raminit.inc: Setting registers to their recommended values for vt8633
 *
 *
 * Copyright 2002 Cwlinux Limited
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
 */

#define loop200 $0x5000
#define loop100 $0x2500

raminit:
	intel_chip_post_macro(0x35)

	CS_WRITE($0x75, $0x08)

	/* since we only support epia-m at the moment, only ddr is supported */
	/* setup cpu */
	CS_WRITE($0x50, $0xc8)
	CS_WRITE($0x51, $0xde)
	CS_WRITE($0x52, $0xcf)
	CS_WRITE($0x53, $0x88)
	CS_WRITE($0x55, $0x07)

	/* DRAM MA Map Type */
	/*	CS_WRITE($0x58, $0xc0)*/
 //#define GETCHIP
#undef GETCHIP
#ifndef GETCHIP
 	CS_WRITE($0x58, $0x71) // was 60 was 0x71 (DA) 20030722
#else
  CS_WRITE($0x58, $0x40) // For GET memory
#endif


	/* DRAM bank 0 - 3 size = 512M */
#ifndef GETCHIP
  	CS_WRITE($0x5a, $0x08)
#else
	 CS_WRITE($0x5a, $0x04) // For GET memory
#endif

	CS_WRITE($0x5b, $0x08)
	CS_WRITE($0x5c, $0x08)
	CS_WRITE($0x5d, $0x08)
	
	/* set DRAM Timing for all banks */
	CS_WRITE($0x64, $0xe6)

	/* set DRAM type to DDR */
	CS_WRITE($0x60, $0x02)

	/* DRAM Arbitration Timer */
	CS_WRITE($0x65, $0x32)
	CS_WRITE($0x66, $0x01)
#ifndef GETCHIP
 	CS_WRITE($0x68, $0x59) // was 0xf0 was 0x59 (DA) 20030722
#else
	CS_WRITE($0x68, $0x55) // GET
#endif

	/* DRAM Frequency */
	CS_WRITE($0x54, $0xe0)
#ifndef GETCHIP
  	CS_WRITE($0x69, $0x2d)
#else
	CS_WRITE($0x69, $0x25) // GET
#endif

	/* Enable CKE */
	CS_WRITE($0x6b, $0x10)

	/* Disable DRAM refresh */
	CS_WRITE($0x6a, $0x00)

	/* Set heavy drive */
#ifndef GETCHIP
  	CS_WRITE($0x6d, $0x44)
#else
	CS_WRITE($0x6d, $0x55) // GET
	CS_WRITE($0x6c, $0x84) // GET
#endif

 	xorl	%esi,%esi
ritop:
	/* NOP Command Enable */
	CS_WRITE($0x6b, $0x01)
	/* read a double word from any address of the dimm */
 	movl 0x1f000(%esi), %eax
	DELAY(loop200)

	/* All bank Precharge Command Enable */
	CS_WRITE($0x6b, $0x02)
 	movl 0x1f100(%esi), %eax

	/* MSR Enable */
	CS_WRITE($0x6b, $0x03)
	/* read 0x2000h */
 	movl 0x2000(%esi), %eax
//	movl $0x2000,%esi
//	movl (%esi), %eax
//	movl $0x4002000, %ecx
//	movl (%esi), %eax


	/* read 0x800h */
 	movl 0x800(%esi), %eax
//	movl $0x800,%esi
//	movl (%esi), %eax
//	movl $0x4000800, %esi
//	movl (%esi), %eax

	/* All banks Precharge Command Enable */
	CS_WRITE($0x6b, $0x02)
 	movl 0x1f200(%esi), %eax

	/* CBR Cycle Enable */
	CS_WRITE($0x6b, $0x04)
	/* Read 8 times */
 	movl 0x1f300(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f400(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f500(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f600(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f700(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f800(%esi), %eax
  	DELAY(loop100)
 	movl 0x1f900(%esi), %eax
  	DELAY(loop100)
 	movl 0x1fa00(%esi), %eax
  	DELAY(loop100)

	/* MSR Enable */
	CS_WRITE($0x6b, $0x03)
	/* 0x150 if CAS Latency 2 or 0x350 CAS Latency 2.5 */
 	movl 0x350(%esi), %ecx
//	movl (%ecx), %eax
//	movl $0x4000350, %ecx
//	movl (%ecx), %eax

	/* Normal SDRAM Mode */
	CS_WRITE($0x6b, $0x58)

#ifdef GETCHIP
	addl	$0x40*0x100000,%esi
	cmpl	$0x80*0x100000,%esi
	jne	ritop
#endif
	/* Set the refreash rate */
	CS_WRITE($0x6a, $0x43)
	CS_WRITE($0x67, $0x22)

	/* pci */
	CS_WRITE($0x70, $0x82)
	CS_WRITE($0x73, $0x01)
	CS_WRITE($0x76, $0x50)

	CS_WRITE($0x71, $0xc8)

	/* graphics aperture base */
	CS_WRITE($0x13, $0xd0)

        CS_WRITE($0x56, $0x10)
        CS_WRITE($0x57, $0x10)

	intel_chip_post_macro(0x36)

