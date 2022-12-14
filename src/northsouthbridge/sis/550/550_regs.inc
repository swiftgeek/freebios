/*
 * 550_regs.inc:	Register Recommended Setting for SiS 550 [ABE][01]
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
 *	1. SiS 550 Specification
 *	2. SiS 550A1 Register Recommended Setting
 *	   Rev 0.97, Jan 7, 2000
 *
 * $Id: 550_regs.inc,v 1.4 2002/01/28 09:29:11 ollie Exp $
 */

northbridge_init_table:
#		Reg.	Value
	/* generic PCI configuration space */
	.byte	0x04,	0x07	# Turn on Bus Master,
	.byte	0x05,	0x00	# Memory and I/O Space
	.byte	0x06,	0x00	# clear PCI status
	.byte	0x07,	0x00	# 	
	.byte	0x0D,	0x20	# Master Latency Timer = 32 PCI CLCK

        .byte   0x13,   0xe0    

	/* SiS 550 specific registers. See SiS 550 Registers Recommended Setting */
	
	/* Host Control Interface */
	.byte	0x50,	0xfe	#
	.byte	0x51,	0x08	#

	/* DRAM Control */
	.byte	0x52,	0xC5	#	
	.byte	0x53,	0xc0	#

	.byte	0x54,	0x08	# 
	.byte	0x55,	0x01	# 
	.byte	0x56,	0x00	# 
	.byte	0x57,	0x00	# 

	/* Pre-driver Slew Rate/Current Driving Control */
	.byte	0x58,	0x00	#
	.byte	0x59,	0x55	#
	.byte	0x5A,	0x55	#
	.byte	0x5B,	0x00	#

	.byte	0x65,	0x00	# Use DIMM 0 for SMA

	/* PCI Interface */
	.byte	0x80,	0x01	#
	.byte	0x81,	0xd1	#
	.byte	0x82,	0xce	#
	.byte	0x83,	0x1b	#

	.byte	0x8E,	0xC1	#
	.byte	0x8F,	0x46	#
		
	.byte	0x84,	0x60	#
	.byte	0x85,	0x00	#
	.byte	0x86,	0x03	#
//	.byte	0x87,	0x00	#
	.byte	0x88,	0x00	#
	.byte	0x89,	0x08	#

	.byte	0x8a,	0x00	#
	.byte	0x8b,	0x00	#

	/* AGP GART Base Address */
	.byte	0x90,	0x00
	.byte	0x91,	0x00
	.byte	0x92,	0x00
	.byte	0x93,	0x00

	/* Graphic Window Size */
	.byte	0x94,	0x40	# Graphic Window Size == 64MB
	.byte	0x97,	0x01	# Page Table Cache Enable
	.byte	0x98,	0x00	#

	/* DRAM Priority Timer Control Register */
	.byte	0xA0,	0x00
	.byte	0xA1,	0x00
	.byte	0xA2,	0x03
	.byte	0xA3,	0x01
northbridge_init_table_end: