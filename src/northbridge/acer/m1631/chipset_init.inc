/* SPD ram init */
#define PM_DEVFN  CONFIG_ADDR(0, 0, 0)
jmp chipsetinit_start
/* table of settings for initial registers */
/* format is register #, and value, OR value */
register_table: 
	.byte 0x45, 0xff, 0x14
	.byte 0x49, 0xff, 0x60
	.byte 0x50, 0xf7, 0x00
	.byte 0x52, 0xff, 0x01
	.byte 0x57, 0xff, 0x08
	.byte 0x58, 0x00, 0x40
	.byte 0x59, 0x00, 0x40
	.byte 0x61, 0x00, 0x00
	.byte 0x62, 0x00, 0x80
	.byte 0x63, 0x00, 0x08
	.byte 0x67, 0xff, 0x08
	.byte 0x6c, 0xfc, 0x00
	.byte 0x70, 0xfc, 0x00
	.byte 0x74, 0xfc, 0x00
	.byte 0x6d, 0xd7, 0x00 /* probably wrong OR value?*/
	.byte 0x71, 0xd7, 0x00 /* probably wrong OR value?*/
	.byte 0x75, 0xd7, 0x00 /* probably wrong OR value?*/
	.byte 0x6f, 0xff, 0x40
	.byte 0x73, 0xff, 0x40
	.byte 0x77, 0xff, 0x40
	.byte 0x7c, 0x00, 0x11 /* MCLK = 66 MHZ */
	.byte 0x7d, 0x00, 0xc4 /* MCLK = 66 MHZ */
	.byte 0x7e, 0x03, 0x28
	.byte 0x7f, 0xef, 0x24
	.byte 0x80, 0xf9, 0x01
	.byte 0x81, 0xb3, 0x00
	.byte 0x82, 0xff, 0x10
	.byte 0x84, 0xfe, 0x00
	.byte 0x87, 0xff, 0x00
	.byte 0x88, 0xff, 0x08
	.byte 0x8e, 0xff, 0x08
	.byte 0x93, 0xff, 0x07
	.byte 0xa0, 0x00, 0x30
	.byte 0xa1, 0x00, 0x40
	.byte 0xbc, 0x03, 0x00 /* 0 non-local video memory for now. */
	.byte 0xbd, 0xfe, 0x00 /* 0 non-local video memory for now. */
	.byte 0xc5, 0x08, 0x00 /* hardware register, set to 0 for pci skew */
	.byte 0xc8, 0x8e, 0x02
	.byte 0xc9, 0xd7, 0x07
	.byte 0xd0, 0xff, 0x00
	.byte 0xd4, 0xfd, 0x00 /* OR WITH 1 in NORTHBRIDGE_FINAL_FIXUP */
	.byte 0xd5, 0xf4, 0x10
	.byte 0xd8, 0x0f, 0x00
	.byte 0xd9, 0xff, 0x03
	.byte 0xdc, 0x00, 0x10
	.byte 0xde, 0xff, 0x04
	.byte 0xf9, 0xff, 0x4
	.byte 0xf0, 0x00, 0x50
	.byte 0xf1, 0x00, 0x04
	.byte 0xf2, 0x00, 0x09
	.byte 0xf3, 0x00, 0x1f
	.byte 0xf4, 0xff, 0x05
	.byte 0xf5, 0x00, 0x02
	.byte 0xf9, 0x00, 0x00
	.byte 0xfd, 0x00, 0x03
	.byte 0xfe, 0xff, 0x08
	.byte 0xff, 0x00, 0x03
	.byte 0x60,~0x20, 0x20
	.byte 0x02,~0xff, 0x21
	.byte 0x60,~0x20, 0x00
	.byte 0xfb,~0xff, 0x31
	.byte 0x0 /* end of table */
chipsetinit_start:

	mov	$0x3f0, %edx
	movb	$0x51, 	%al
	outb	%al, 	%dx
	movb	$0x23, 	%al
	outb	%al, 	%dx
	movb	$0x2e, 	%al
	out	%al, %dx
	movb	$2, 	%al
	inc	%edx
	outb	%al,	%dx
	movb	$0xbb,	%al
	dec	%dl
	outb	%al, 	%dx
	/* standard x86 loop on table until done code */
	/* assumes that: devfn is 0 (safe on anything we've seen) */
	/* which means addresses are a byte */
	/* address is first, then data */
	/* NOTE: read returns result in %al */
	/* WRITE expects write value in %dl, address in %al */
	movl	$register_table, %esi
1: 
	xorl	%edx, %edx
	xorl	%eax, %eax
	movb	(%esi), %cl /* save the address in %cl */
	movb	%cl, 	%al
	testb 	%al, %al
	jz	done_chipset_init
	PCI_READ_CONFIG_BYTE
	movb	%al, %dl
	inc	%esi
	andb	(%esi), %dl
	inc %esi
	orb	(%esi), %dl
	mov	%cl, %al
	PCI_WRITE_CONFIG_BYTE
	inc %esi
	jmp 1b

done_chipset_init: