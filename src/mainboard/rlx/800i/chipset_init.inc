/************************************
* FILE: src/northbridge/micron/21PAD/chipset_init.inc
* NAME: Suravee Suthikulpanit
* suravee@lanl.gov
* 5/2002
* 
* This is the RLX 800i initialization for:
*	- Micron 21PAD Fn 0,1
*	- Acer M1535 
*************************************/
#define PM_DEVFN  CONFIG_ADDR(0, 0, 0) 
.type chipsetinit_start, @function 
jmp chipsetinit_start

/* table of settings for initial registers */
/* format is register #, and value, OR value */
#if 0
// Original Table from the book
register_table:
        .byte 0x04, 0x00, 0x00
        .byte 0x05, 0x00, 0x00
        .byte 0x07, 0x70, 0x70
        .byte 0x0c, 0x04, 0x04
        .byte 0x0d, 0x40, 0x40
        .byte 0x40, 0x07, 0x07
        .byte 0x41, 0x00, 0x00
        .byte 0x42, 0x00, 0x00
        .byte 0x43, 0x00, 0x00
        .byte 0x4c, 0x03, 0x03
        .byte 0x4d, 0x00, 0x00
        .byte 0x4e, 0x40, 0x40
        .byte 0x50, 0x94, 0x94
        .byte 0x52, 0x01, 0x01
        .byte 0x53, 0x01, 0x01
        .byte 0x5c, 0x00, 0x00
        .byte 0x5d, 0x00, 0x00
        .byte 0x5e, 0x00, 0x00
        .byte 0x5f, 0x00, 0x00
        .byte 0x60, 0x00, 0x00
        .byte 0x61, 0x00, 0x00
        .byte 0x62, 0x00, 0x00
        .byte 0x63, 0x00, 0x00
        .byte 0x64, 0x00, 0x00
        .byte 0x65, 0x00, 0x00
        .byte 0x66, 0x00, 0x00
        .byte 0x67, 0x00, 0x00
        .byte 0x68, 0x00, 0x00
        .byte 0x69, 0x00, 0x00
        .byte 0x6a, 0x00, 0x00
        .byte 0x6b, 0x00, 0x00
        .byte 0x6c, 0x00, 0x00
        .byte 0x6d, 0x00, 0x00
        .byte 0x6e, 0x00, 0x00
        .byte 0x6f, 0x00, 0x00
        .byte 0x70, 0xb8, 0xb8
        .byte 0x71, 0x8f, 0x8f
        .byte 0x72, 0x3f, 0x3f
        .byte 0x73, 0x79, 0x79
        .byte 0x74, 0x00, 0x00
        .byte 0x75, 0x00, 0x00
        .byte 0x76, 0x00, 0x00
        .byte 0x77, 0x00, 0x00
        .byte 0x78, 0x00, 0x00
        .byte 0x79, 0x00, 0x00
        .byte 0x7a, 0x00, 0x00
        .byte 0x7b, 0x00, 0x00
        .byte 0x8c, 0xf4, 0xf4
        .byte 0x8d, 0x82, 0x82
        .byte 0x8e, 0x9c, 0x9c
        .byte 0x8f, 0xc0, 0xc0
        .byte 0x90, 0x00, 0x00
        .byte 0x91, 0x00, 0x00
        .byte 0x92, 0x00, 0x00
        .byte 0x93, 0x00, 0x00
        .byte 0x94, 0x00, 0x00
        .byte 0xa0, 0x00, 0x00
        .byte 0xa1, 0x00, 0x00
        .byte 0xa2, 0x00, 0x00
        .byte 0xc0, 0x00, 0x00
        .byte 0xc1, 0x00, 0x00
        .byte 0xc2, 0x00, 0x00
        .byte 0xc3, 0xc2, 0xc2
        .byte 0xc8, 0x47, 0x47
        .byte 0xc9, 0xfb, 0xfb
        .byte 0xca, 0x00, 0x00
        .byte 0xcb, 0x00, 0x00
        .byte 0xd6, 0x00, 0x00
        .byte 0xd7, 0x00, 0x00
        .byte 0xe0, 0x7f, 0x7f
        .byte 0xe2, 0x00, 0x00
        .byte 0xf0, 0x30, 0x30
        .byte 0xf1, 0x00, 0x00
        .byte 0xf2, 0x00, 0x00

        .byte 0x0 /* end of table */
#else

// HOST-PCI Bridge Controler
// Modified table 
register_table:
        .byte 0x04, 0x00, 0x00
        .byte 0x05, 0x00, 0x00
        .byte 0x07, 0x70, 0x70
        .byte 0x0c, 0x04, 0x04
        .byte 0x0d, 0x40, 0x40
        .byte 0x40, 0x07, 0x07
        .byte 0x41, 0x00, 0x00
        .byte 0x42, 0x00, 0x00
        .byte 0x43, 0x00, 0x00
        .byte 0x4c, 0x03, 0x03
        .byte 0x4d, 0x00, 0x00
        .byte 0x4e, 0x40, 0x40
        .byte 0x50, 0x94, 0x94
        .byte 0x52, 0x01, 0x01
        .byte 0x53, 0x01, 0x01
	// PCI0 bus device control
        .byte 0x54, 0x00, 0x00
        .byte 0x55, 0x00, 0x00
        .byte 0x56, 0x10, 0x10
        .byte 0x57, 0x01, 0x01

        .byte 0x5c, 0x00, 0x00
        .byte 0x5d, 0x00, 0x00
        .byte 0x5e, 0x00, 0x00
        .byte 0x5f, 0x00, 0x00
        .byte 0x60, 0x00, 0x00
        .byte 0x61, 0x00, 0x00
        .byte 0x62, 0x00, 0x00
        .byte 0x63, 0x00, 0x00
	// Host-PCI I/O Range
        .byte 0x64, 0x00, 0x00
        .byte 0x65, 0x00, 0x00
        .byte 0x66, 0xff, 0xff
        .byte 0x67, 0x0f, 0x0f
        .byte 0x68, 0x00, 0x00
        .byte 0x69, 0x00, 0x00
        .byte 0x6a, 0xff, 0xff
        .byte 0x6b, 0x0f, 0x0f

        .byte 0x6c, 0x00, 0x00
        .byte 0x6d, 0x00, 0x00
        .byte 0x6e, 0x00, 0x00
        .byte 0x6f, 0x00, 0x00
        .byte 0x70, 0xb8, 0xb8
        .byte 0x71, 0x8f, 0x8f
        .byte 0x72, 0x3f, 0x3f
        .byte 0x73, 0x79, 0x79
        .byte 0x74, 0x00, 0x00
        .byte 0x75, 0x00, 0x00
        .byte 0x76, 0x00, 0x00
        .byte 0x77, 0x00, 0x00
        .byte 0x78, 0x00, 0x00
        .byte 0x79, 0x00, 0x00
        .byte 0x7a, 0x00, 0x00
        .byte 0x7b, 0x00, 0x00
        .byte 0x8c, 0xf4, 0xf4
        .byte 0x8d, 0x82, 0x82
        .byte 0x8e, 0x9c, 0x9c
        .byte 0x8f, 0xc0, 0xc0
        .byte 0x90, 0x00, 0x00
        .byte 0x91, 0x00, 0x00
        .byte 0x92, 0x00, 0x00
        .byte 0x93, 0x00, 0x00
        .byte 0x94, 0x00, 0x00
	// Switch control
        .byte 0xa0, 0x5b, 0x5b
        .byte 0xa1, 0x36, 0x36
        .byte 0xa2, 0x04, 0x04
	// PCI Arbiter Control
        .byte 0xc0, 0x00, 0x00
        .byte 0xc1, 0x00, 0x00
        .byte 0xc2, 0x02, 0x02
        .byte 0xc3, 0x42, 0x42

        .byte 0xc8, 0x47, 0x47
        .byte 0xc9, 0xfb, 0xfb
        .byte 0xca, 0x00, 0x00
        .byte 0xcb, 0x00, 0x00
        .byte 0xd6, 0x00, 0x00
        .byte 0xd7, 0x00, 0x00
        .byte 0xe0, 0x7f, 0x7f
        .byte 0xe2, 0x00, 0x00
	// PCI Master Control
        .byte 0xf0, 0xfc, 0xfc
        .byte 0xf1, 0x02, 0x02
        .byte 0xf2, 0x00, 0x00

        .byte 0x0 /* end of table */
#endif

// Original Table from the book 
// Memory Controler Table
register_table1:
        .byte 0x0c, 0xff, 0xff
        .byte 0x0d, 0x40, 0x40

        .byte 0x2f, 0x40, 0x10	// Subsytem Vendor ID
        .byte 0x2e, 0x40, 0x42  // !!! Try this
        .byte 0x2d, 0x40, 0x10
        .byte 0x2c, 0x40, 0x42

        .byte 0x40, 0x00, 0x00

        .byte 0x41, 0x01, 0x01	// !!!!! Design specific

        .byte 0x42, 0x00, 0x00
        .byte 0x43, 0x00, 0x00
        .byte 0x44, 0x00, 0x02
        .byte 0x48, 0x00, 0x00
        .byte 0x8c, 0x00, 0x08	// ECC Control
        .byte 0x8d, 0x00, 0x89	// Symmetric Select and Config

        .byte 0x8e, 0x10, 0x10 	// !!!!! 780d
        .byte 0x8f, 0x04, 0x04
	
        .byte 0x92, 0x02, 0x02	// Error Status/Command
        .byte 0xa0, 0x00, 0x00
        .byte 0xa1, 0x43, 0x43
        .byte 0xa2, 0x3f, 0x3f
        .byte 0xa3, 0x92, 0x92

        .byte 0xc8, 0x94, 0x94 	// !!!!! NOT SURE
        .byte 0xc9, 0x49, 0x49
        .byte 0xca, 0x35, 0x35
        .byte 0xcb, 0x6d, 0x6d
	
        .byte 0xe0, 0x80, 0x80
        .byte 0xf0, 0x00, 0x00
        .byte 0xf1, 0x00, 0x00
        .byte 0xf2, 0x00, 0x00
        .byte 0xf3, 0x00, 0x00
        .byte 0xf4, 0x00, 0x00
        .byte 0xf5, 0x00, 0x00
        .byte 0xf6, 0x00, 0x00
        .byte 0xf7, 0x00, 0x00
        .byte 0xf8, 0x00, 0x00
        .byte 0xf9, 0x00, 0x00
        .byte 0xfa, 0x00, 0x00
        .byte 0xfb, 0x00, 0x00
        .byte 0xfc, 0x00, 0x00
        .byte 0xfd, 0x00, 0x00
        .byte 0xfe, 0x00, 0x00
        .byte 0xff, 0x00, 0x00
	
	.byte 0x0 /* end of table */

#if 0
// Original Table from the book
m1535_table:
	.byte 0x61, 0xd0, 0x00		// Set Keyboard Cntrl to be internal

	.byte 0x41, 0x23, 0x23
	.byte 0x42, 0x08, 0x08
	.byte 0x43, 0x85, 0x85
	.byte 0x47, 0x07, 0x07
	.byte 0x58, 0x5c, 0x5c
	.byte 0x72, 0x0b, 0x0b
	.byte 0x77, 0x36, 0x36
	
        .byte 0x0 // end of m1535_table

m7101_table:
	.byte 0xda, 0x40, 0x40
	.byte 0xe0, 0x00, 0x00
	.byte 0xe1, 0x40, 0x40
	.byte 0xe2, 0x00, 0x00		// SMB base addr (low)
	.byte 0xe3, 0x50, 0x50		// SMB base addr (high)
	.byte 0x80, 0x06, 0x06
	.byte 0x83, 0x02, 0x02
	.byte 0xd1, 0x06, 0x06
	.byte 0xf0, 0x01, 0x01
	.byte 0xf2, 0x20, 0x20

	.byte 0x0 // end of m7101_table 

#endif

// Ron's  table
m1535_table:
        .byte 0x58, 0x00, 0x4c  // enable IDE controller
        .byte 0x44, 0x00, 0x1d  // set edge mode, primary channel IRQ 14
                                // for IDE 1
      
	.byte 0x47, 0xff, 0x40  // enable flash rom r/w
        .byte 0x41, 0x00, 0x0d  // enable superIO recovery
        .byte 0x0 // end of m1535_table

m7101_table:

	.byte 0xe2, 0x00, 0x00		// SMB base addr (low)
	.byte 0xe3, 0x50, 0x50		// SMB base addr (high)
	.byte 0x80, 0x3e, 0x3e		// 
	.byte 0xd1, 0x46, 0x46		// SMB IO space enable
	.byte 0xf0, 0x01, 0x01		// SMB Host config
	.byte 0xb8, 0x40, 0x40		// GPOs
        .byte 0x0 // end of m7101_table

//--------------------------------------
chipsetinit_start:
	// RESET CONTROL
	// - This reset the host controller
	//   and memory interface
	// Fn 0 offset D4 : set to 0xe0 and back to 0x0
	
	xorl %eax, %eax
	xorl %edx, %edx
        movl $0x0000c000, %eax       // Northbridge is dev 18 << 3 + 0 = 0xC0
	movb 0xe0, %dl
	PCI_WRITE_CONFIG_BYTE
	movb 0x00, %dl
	PCI_WRITE_CONFIG_BYTE
		

        /* standard x86 loop on table until done code */
        /* assumes that: devfn is 0 (safe on anything we've seen) */
        /* which means addresses are a byte */
        /* address is first, then data */
        /* NOTE: read returns result in %al */
        /* WRITE expects write value in %dl, address in %al */
        // BEGIN NORTHBRIDGE INIT
        movl    $register_table, %esi
1:
        xorl    %edx, %edx      // clear edx
        //xorl    %eax, %eax      // clear eax
        movl    $0x0000c000, %eax       // Northbridge is dev 18 << 3 + 0 = 0xC0
        movb    (%esi), %cl /* save the address (register #) in %cl */
        movb    %cl,    %al
        testb   %al, %al        // 0 means end of chipset init
        jz      done_chipset_init
        PCI_READ_CONFIG_BYTE
        movb    %al, %dl
        inc     %esi
        andb    (%esi), %dl
        inc %esi
        orb     (%esi), %dl
        mov     %cl, %al
        PCI_WRITE_CONFIG_BYTE
        inc %esi
        jmp 1b

done_chipset_init:

northbridge_fn1_start:
        movl    $register_table1, %esi
1:
        xorl    %edx, %edx      // clear edx
        movl    $0x0000c100, %eax       // Northbridge is dev 18 << 3 + 1 = 0xC1
        movb    (%esi), %cl /* save the address (register #) in %cl */
        movb    %cl,    %al
        testb   %al, %al        // 0 means end of chipset init
        jz      done_northbridge_fn1
        PCI_READ_CONFIG_BYTE
        movb    %al, %dl
        inc     %esi
        andb    (%esi), %dl
        inc %esi
        orb     (%esi), %dl
        mov     %cl, %al
        PCI_WRITE_CONFIG_BYTE
        inc %esi
        jmp 1b
done_northbridge_fn1:

m1535_init:
        movl    $m1535_table, %esi
1:
        xorl    %edx, %edx
        movl    $0x00003800, %eax       // southbridge is dev 7 << 3 = 0x38
        movb    (%esi), %cl 		/* save the address in %cl */
        movb    %cl,    %al
        testb   %al, %al
        jz      done_m1535_init
        PCI_READ_CONFIG_BYTE
        movb    %al, %dl
        inc     %esi
        andb    (%esi), %dl
        inc %esi
        orb     (%esi), %dl
        mov     %cl, %al
        PCI_WRITE_CONFIG_BYTE
        inc %esi
        jmp 1b
done_m1535_init:

m7101_init:
        movl    $m7101_table, %esi
1:
        xorl    %edx, %edx
        //movl    $0x00003000, %eax       // southbridge is dev 6 << 3 = 0x30
        movl    $0x00008800, %eax       // southbridge is dev 11 << 3 = 0x88
        movb    (%esi), %cl 		/* save the address in %cl */
        movb    %cl,    %al
        testb   %al, %al
        jz      done_m7101_init
        PCI_READ_CONFIG_BYTE
        movb    %al, %dl
        inc     %esi
        andb    (%esi), %dl
        inc %esi
        orb     (%esi), %dl
        mov     %cl, %al
        PCI_WRITE_CONFIG_BYTE
        inc %esi
        jmp 1b
done_m7101_init:

