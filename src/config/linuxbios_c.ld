/*
 *	Memory map:
 *
 *	_RAMBASE		
 *				: data segment
 *				: bss segment
 *				: heap
 *				: stack
 */
/*
 * Bootstrap code for the STPC Consumer
 * Copyright (c) 1999 by Net Insight AB. All Rights Reserved.
 *
 * $Id: linuxbios_c.ld,v 1.2 2002/11/10 06:30:18 aip Exp $
 *
 */

/*
 *	Written by Johan Rydberg, based on work by Daniel Kahlin.
 *      Rewritten by Eric Biederman
 */
/*
 *	We use ELF as output format. So that we can
 *	debug the code in some form. 
 */
INCLUDE ldoptions

ENTRY(_start)

SECTIONS
{
	. = _RAMBASE;
	/*
	 * First we place the code and read only data (typically const declared).
	 * This get placed in rom.
	 */
	.text : {
		_text = .;
		*(.text);
		*(.text.*);
		. = ALIGN(16);
		_etext = .;
	}
	.rodata : {
		_rodata = .;
		. = ALIGN(4);
		streams = . ;
		*(.rodata.streams)
		estreams = .;
		. = ALIGN(4);
		pci_drivers = . ;
		*(.rodata.pci_drivers)
		epci_drivers = . ;
		*(.rodata)
		*(.rodata.*)
		/*
		 * kevinh/Ispiri - Added an align, because the objcopy tool
		 * incorrectly converts sections that are not long word aligned.
		 * This breaksthe linuxbios.strip target.
		 */
		 . = ALIGN(4);

		_erodata = .;
	}	
	/*
	 * After the code we place initialized data (typically initialized
	 * global variables). This gets copied into ram by startup code.
	 * __data_start and __data_end shows where in ram this should be placed,
	 * whereas __data_loadstart and __data_loadend shows where in rom to
	 * copy from.
	 */
	.data : {
		_data = .;
		*(.data)
		_edata = .;
	}
	/*
	 * bss does not contain data, it is just a space that should be zero
	 * initialized on startup. (typically uninitialized global variables)
	 * crt0.S fills between _bss and _ebss with zeroes.
	 */
	_bss = .;
	.bss . : {
		*(.bss)
		*(.sbss)
		*(COMMON)
	}
	_ebss = .;
	_end = .;
	_stack = .;
	.stack . : {
		/* Reserve a stack for each possible cpu, +1 extra */
		. = ((MAX_CPUS * STACK_SIZE) + STACK_SIZE) ; 
	}
	_estack = .;
	_heap = .;
	.heap . : {
		/* Reserve 256K for the heap */
		. = HEAP_SIZE ;
		. = ALIGN(4);
	}
	_eheap = .;
	/* The ram segment
 	 * This is all address of the memory resident copy of linuxBIOS.
	 */
	_ram_seg = _text;
	_eram_seg = _eheap;
	/DISCARD/ : {
		*(.comment)
		*(.note)
	}
}
