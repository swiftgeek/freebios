#include <sdram.h>
#include <printk.h>
#include <arch/cache_ram.h>
#include <pci.h>
#include <smbus.h>
#include <bitops.h>

#define I440GX_BUS 0
#define I440GX_DEVFN ((0x00 << 3) + 0)

#define USE_ECC 0

#define CAS_LATENCY 3

	/* CAS latency 2 */
#if (CAS_LATENCY == 2)
#define CAS_NB 0x17
	/* 
	 * 7 == 0111
	 * 1 == 0001
	 */
#define CAS_MODE 0x2a
	/*
	 * a == 1010
	 * 2 == 0010
	 */
#endif

	/* CAS latency 3 */
#if (CAS_LATENCY == 3) 
#define CAS_NB 0x13
	/*
	 * 3 == 0011
	 * 1 == 0001
	 */
#define CAS_MODE 0x3a
	/*
	 * a == 1010
	 * 3 == 0011
	 */
#endif

#ifndef CAS_NB
#error "Nothing defined" 
#endif


/* Default values for config registers */
	
static void set_nbxcfg(void)
{
	/* NBXCFG 0x50 - 0x53 */
	/* f == 1111
	 * 0 == 0000
	 * 0 == 0000
	 * 0 == 0000
	 * 0 == 0000
	 * 1 == 0001
	 * 8 == 1000
	 * c == 1100
	 * SDRAM Row without ECC:
	 * row 0 == 1 No ECC
	 * row 1 == 1 No ECC
	 * row 2 == 1 No ECC
	 * row 3 == 1 No ECC
	 * row 4 == 1 No ECC
	 * row 5 == 1 No ECC
	 * row 6 == 1 No ECC
	 * row 7 == 1 No ECC
	 * Host Bus Fast Data Ready Enable == 0 Disabled
	 * IDSEL_REDIRECT == 0 (430TX compatibility disable?)
	 * WSC# Hanshake Disable == 0 enable (Use External IOAPIC)
	 * Host/DRAM Frequence == 00 100Mhz
	 * AGP to PCI Access Enable == 0 Disable
	 * PCI Agent to Aperture Access Disable == 0 Enable (Ignored)
	 * Aperture Access Global Enable == 0 Disable
	 * DRAM Data Integrity Mode == 11 (Error Checking/Correction)
	 * ECC Diagnostic Mode Enable == 0 Not Enabled
	 * MDA present == 0 Not Present
	 * USWC Write Post During During I/O Bridge Access Enable == 1 Enabled
	 * In Order Queue Depth (IQD) (RO) == ?? 
	 */
	pcibios_write_config_dword(I440GX_BUS, I440GX_DEVFN, 0x50, 0xff00000c);
}

static void set_dramc(void)
{
	/* 0 == 0000
	 * 8 == 1000
	 * Not registered SDRAM
	 * refresh disabled
	 */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x57, 0x8);
}

static void set_pam(void)
{
	/* PAM - Programmable Attribute Map Registers */
	/* Ideally we want to enable all of these as DRAM and teach
	 * linux it is o.k. to use them...
	 */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x59, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x5a, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x5b, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x5d, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x5e, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x5f, 0x00);
}

static void set_drb(void)
{
	/* DRB - DRAM Row Boundary Registers */
	/* Conservative setting 8MB of ram on first DIMM... */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x60, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x61, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x62, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x63, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x64, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x65, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x66, 0x01);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x67, 0x01);
}

static void set_fdhc(void)
{
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x68, 0x00);
}
static void set_mbsc(void)
{
	/* MBSC - Memory Buffer Strength Control */
	/* 00c00003e820
	 * [47:44] 0 == 0000
	 * [43:40] 0 == 0000
	 * [39:36] c == 1100
	 * [35:32] 0 == 0000
	 * [31:28] 0 == 0000
	 * [27:24] 0 == 0000
	 * [23:20] 0 == 0000
	 * [19:16] 3 == 0011
	 * [15:12] e == 1110
	 * [11: 8] 8 == 1000
	 * [ 7: 4] 2 == 0010
	 * [ 3: 0] 0 == 0000
	 * MAA[14:0]#, WEA#, SRASA#, SCASA# Buffer Strengths  ==  3x
	 * MAB[14,13,10,12:11,9:0]#, WEB#, SRASB#, SCASB# Buffer Strengths == 3x
	 * MD[63:0]# Buffer Strength Control 2 == 3x
	 * MD[63:0]# Buffer Strength Control 1 == 3x
	 * MECC[7:0] Buffer Strength Control 2 == 3x
	 * MECC[7:0] Buffer Strength Control 1 == 3x
	 * CSB7# Buffer Strength == 3x	
	 * CSA7# Buffer Strength == 3x
	 * CSB6# Buffer Strength == 3x
	 * CSA6# Buffer Strength == 3x
	 * CSA5#/CSB5# Buffer Strength == 2x
	 * CSA4#/CSB4# Buffer Strength == 2x
	 * CSA3#/CSB3# Buffer Strength == 2x
	 * CSA2#/CSB2# Buffer Strength == 2x
	 * CSA1#/CSB1# Buffer Strength == 2x
	 * CSA0#/CSB0# Buffer Strength == 2x
	 * DQMA5 Buffer Strength == 2x
	 * DQMA1 Buffer Strength == 3x
	 * DQMB5 Buffer Strength == 2x
	 * DQMB1 Buffer Strength == 2x
	 * DQMA[7:6,4:2,0] Buffer Strength == 3x
	 * GCKE Buffer Strength == 1x
	 * FENA Buffer Strength == 3x
	 */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x69, 0xB3);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x6a, 0xee);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x6b, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x6c, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x6d, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x6e, 0x03);
}

static void set_smram(void)
{
	/* 0x72 SMRAM */
	/* 1 == 0001
	 * a == 1010
	 * SMM Compatible base segment == 010 (Hardcoded value)
	 */
}

static void set_esramc(void)
{
	/* 0x73 ESMRAMC */
}

static void set_rps(void)
{
	/* RPS - Row Page Size Register */
	/* 0x0055
	 * [15:12] 0 == 0000
	 * [11: 8] 0 == 0000
	 * [ 7: 4] 5 == 0101
	 * [ 3: 0] 5 == 0101
	 * DRB[0] == 4KB
	 * DRB[1] == 4KB
	 * DRB[2] == 4KB
	 * DRB[3] == 4KB
	 * DRB[4] == 2KB
	 * DRB[5] == 2KB
	 * DRB[6] == 2KB
	 * DRB[7] == 2KB
	 */
	pcibios_write_config_word(I440GX_BUS, I440GX_DEVFN, 0x74, 0x5555);
}

static void set_sdramc(void)
{
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, CAS_NB);
}

static void set_pgpol(void)
{
	/* PGPOL - Paging Policy Register */
	/* 0xff07
	 * [15:12] f == 1111
	 * [11: 8] f == 1111
	 * [ 7: 4] 0 == 0000
	 * [ 3: 0] 7 == 0111
	 * row0 == 4banks
	 * row1 == 4banks
	 * row2 == 4banks
	 * row3 == 4banks
	 * row4 == 4banks
	 * row5 == 4banks
	 * row6 == 4banks
	 * row7 == 4banks
	 * Dram Idle Timer (DIT) == 32 clocks
	 */
	pcibios_write_config_word(I440GX_BUS, I440GX_DEVFN, 0x78, 0xff07);
}

static void set_mbfs(void)
{
	/* MBFS - Memory Buffer Frequencey Select Register */
	/* 0xffff7f					     
	 * [23:20] f == 1111				     
	 * [19:16] f == 1111				     
	 * [15:12] f == 1111				     
	 * [11: 8] f == 1111				     
	 * [ 7: 4] 7 == 0111				     
	 * [ 3: 0] f == 1111				     
	 * MAA[14:0], WEA#, SRASA#, SCASA# == 100Mhz Buffers Enabled
	 * MAB[14,13,10,12:11,9:0], WEB#, SRASB#, SCASB# == 100Mhz Buffers Enabled
	 * MD[63:0] Control 2 == 100 Mhz Buffer Enable
	 * MD[63:0] Control 1 == 100 Mhz B
	 * MECC[7:0] Control 2 == 100 Mhz B
	 *
	 */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xca, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xcb, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xcc, 0x7f);
}

static void set_dwtc(void)
{
	/* DWTC - DRAM Write Thermal Throttle Control */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe0, 0xb4);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe1, 0xbe);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe2, 0xff);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe3, 0xd7);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe4, 0x97);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe5, 0x3e);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe6, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe7, 0x80);
}

static void set_drtc(void)
{
	/* DRTC - DRAM Read Thermal Throttle Control */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe8, 0x2c);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xe9, 0xd3);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xea, 0xf7);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xeb, 0xcf);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xec, 0x9d);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xed, 0x3e);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xee, 0x00);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xef, 0x00);
}

static void set_pmcr(void)
{
	/* PMCR -- BIOS sets 0x90 into it. 
	 * 0x10 is REQUIRED.
	 * we have never used it. So why did this ever work?
	 */
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x7a, 0x90);
	
}
void sdram_set_registers(void)
{
	set_nbxcfg();
	set_dramc();
	set_pam();
	set_drb();
	set_fdhc();
	set_mbsc();
	set_smram();
	set_esramc();
	set_rps();
	set_sdramc();
	set_pgpol();
	set_mbfs();
	set_dwtc();
	set_drtc();
	set_pmcr();
}


static void spd_set_drb(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the
	 *              DRB registers which holds the ending memory address assigned
	 *              to each DIMM.
	 */
	unsigned end_of_memory;
	unsigned device;
	unsigned drb_reg;
	
	end_of_memory = 0; /* in multiples of 8MiB */
	device = SMBUS_MEM_DEVICE_START;
	drb_reg = 0x60;
	while (device <= SMBUS_MEM_DEVICE_END) {
		unsigned side1_bits, side2_bits;
		unsigned char byte, byte2;
		int status;

		side1_bits = side2_bits = -1;

		/* rows */
		status = smbus_read_byte(device, 3, &byte);
		if (status != 0) goto set_drb_reg;
		side1_bits += byte & 0xf;

		/* columns */
		status = smbus_read_byte(device, 4, &byte);
		side1_bits += byte & 0xf;

		/* banks */
		status = smbus_read_byte(device, 17, &byte);
		side1_bits += log2(byte);

		/* Get the moduel data width and convert it to a power of two */
		/* low byte */
		status = smbus_read_byte(device, 6, &byte); 
		/* high byte */
		status = smbus_read_byte(device, 7, &byte2);
		side1_bits += log2((((unsigned long)byte2 << 8)| byte));
		
		/* now I have the ram size in bits as a power of two (less 1) */
		/* Make it mulitples of 8MB */
		side1_bits -= 25;

		/* side two */

		/* number of physical banks */
		status = smbus_read_byte(device, 5, &byte);
		if (byte <= 1) goto set_drb_reg;

		/* for now only handle the symmetrical case */
		side2_bits = side1_bits;

	set_drb_reg:
		/* Compute the end address for the DRB register */
		/* Only process dimms < 2GB (2^8 * 8MB) */
		if (side1_bits < 8) {
			end_of_memory += (1 << side1_bits);
		}
		printk_debug("end_of_memory: %08x\n", end_of_memory);
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, drb_reg, end_of_memory);

		if (side2_bits < 8 ) {
			end_of_memory += (1 << side2_bits);
		}
		printk_debug("end_of_memory: %08x\n", end_of_memory);
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, drb_reg +1, end_of_memory);

		drb_reg += 2;
		device += SMBUS_MEM_DEVICE_INC;
	}
}

static void spd_set_dramc(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the
	 *              DRAMC register, which records if ram is registerd or not,
	 *              and controls the refresh rate.
	 *              The refresh rate is not set here, as memory refresh
	 *              cannot be enbaled until after memory is initialized.
	 *		see spd_enable_refresh.
	 */
	/* auto detect if ram is registered or not. */
	/* The DRAMC register also contorls the refresh rate but we can't
         * set that here because we must leave refresh disabled.
	 * see:	spd_enable_refresh
	 */
	/* Find the first dimm and assume the rest are the same */
	/* FIXME Check for illegal/unsupported ram configurations and abort */
	unsigned device;
	int status;
	unsigned char byte;
	unsigned dramc;
	status = -1;
	device = SMBUS_MEM_DEVICE_START;
	while ((status != 0) && (device <= SMBUS_MEM_DEVICE_END)) {
		status = smbus_read_byte(device, 21, &byte);
		device += SMBUS_MEM_DEVICE_INC;
	}
	if (status != 0) {
		/* We couldn't find anything we must have no memory */
		sdram_no_memory();
	}
	dramc = 0x8;
	if ((byte & 0x12) != 0) {
		/* this is a registered part. 
		 * observation: for register parts, BIOS zeros (!) 
		 * registers CA-CC. This has an undocumented meaning.
		 */
		/* But it does make sense the oppisite of registered
		 * sdram is buffered and 0xca - 0xcc control the buffers.
		 * Clearing them aparently disables them.
		 */
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xca, 0);
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xcb, 0);
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0xcc, 0);
		dramc = 0x10;
	}
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x57, dramc);
}

static void spd_enable_refresh(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the
	 *              refresh rate in the DRAMC register.
	 *		see spd_set_dramc for the other values.
	 * FIXME:	Check for illegal/unsupported ram configurations and abort
	 */
	static const unsigned char refresh_rates[] = {
		0x01, /* Normal        15.625 us -> 15.6 us */
		0x05, /* Reduced(.25X) 3.9 us    -> 7.8 us */
		0x05, /* Reduced(.5X)  7.8 us    -> 7.8 us */
		0x02, /* Extended(2x)  31.3 us   -> 31.2 us */
		0x03, /* Extended(4x)  62.5 us   -> 62.4 us */
		0x04, /* Extended(8x)  125 us    -> 124.8 us */
	};
	/* Find the first dimm and assume the rest are the same */
	int status;
	unsigned char byte;
	unsigned device;
	unsigned refresh_rate;
	byte = 0;
	status = -1;
	device = SMBUS_MEM_DEVICE_START;
	while ((status != 0) && (device <= SMBUS_MEM_DEVICE_END)) {
		status = smbus_read_byte(device, 12, &byte);
		device += SMBUS_MEM_DEVICE_INC;
	}
	if (status != 0) {
		/* We couldn't find anything we must have no memory */
		sdram_no_memory();
	}
	byte &= 0x7f;
	/* Default refresh rate be conservative */
	refresh_rate = 5; 
	/* see if the ram refresh is a supported one */
	if (byte < 6) {
		refresh_rate = refresh_rates[byte];
	}
	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x57, &byte);
	byte &= 0xf8;
	byte |= refresh_rate;
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x57, byte);
}

static void spd_set_sdramc(void)
{
	return;
}

static void spd_set_rps(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the row size 
	 *		on a given DIMM
	 * FIXME:	Check for illegal/unsupported ram configurations and abort
	 */
	/* The RPS register holds the size of a ``page'' of DRAM on each DIMM */
	unsigned page_sizes;
	unsigned index;
	unsigned device;
	unsigned char dramc;
	/* default all page sizes to 2KB */
	page_sizes = 0;
	index = 0;
	device = SMBUS_MEM_DEVICE_START;
	while (device <= SMBUS_MEM_DEVICE_END) { 
		int status;
		unsigned char byte;
		int page_size;

		status = smbus_read_byte(device, 3, &byte);
		if (status != 0) goto next;

		/* I now have the row page size as a power of 2 */
		page_size = byte & 0xf;
		/* make it in multiples of 2Kb */
		page_size -= 11;
		if (page_size <= 0) goto next;
		/* FIXME: do something with page sizes greather than 8KB!! */
		page_sizes |= (page_size << index);

		/* side two */
		status = smbus_read_byte(device, 5, &byte);
		if (byte <= 1) goto next;
		
		/* For now only handle the symmetrical case */
		page_sizes |= (page_size << (index +2));
		
	next:
		index += 4;
		device += SMBUS_MEM_DEVICE_INC;
	}

	/* next block is for Ron's attempt to get registered to work. */
	/* we have just verified that we have to have this code. It appears that
	 * the registered SDRAMs do indeed set the RPS wrong. sheesh.
	 */
	/* at this point, page_sizes holds the RPS for all ram. 
	 * we have verified that for registered DRAM the values are 
	 * 1/2 the size they should be. So we test for registered
	 * and then double the sizes if needed. 
	 */

	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x57, &dramc);
	if (dramc & 0x10) {
		/* registered */

		/* BIOS makes weird page size for registered! */
		/* what we have found is you need to set the EVEN banks to 
		 * twice the size. Fortunately there is a very easy way to 
		 * do this. First, read the WORD value of register 0x74. 
		 */
		page_sizes += 0x1111;
	}

	pcibios_write_config_word(I440GX_BUS, I440GX_DEVFN, 0x74, page_sizes);
}

static void spd_set_pgpol(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the number of banks
	 *		on a given DIMM
	 * FIXME:	Check for illegal/unsupported ram configurations and abort
	 */
	/* The PGPOL register stores the number of logical banks per DIMM,
	 * and number of clocks the DRAM controller waits in the idle
	 * state.
	 */
	unsigned device;
	unsigned bank_sizes;
	unsigned bank;
	unsigned reg;
	/* default all bank counts 2 */
	bank_sizes = 0;
	bank = 0;
	device = SMBUS_MEM_DEVICE_START;
	while (device <= SMBUS_MEM_DEVICE_END) { 
		int status;
		unsigned char byte;

		/* logical banks */
		status = smbus_read_byte(device, 17, &byte);
		if (status != 0) goto next;
		if (byte < 4) goto next;
		bank_sizes |= (1 << bank);
		
		/* side 2 */
		/* Number of physical banks */
		status = smbus_read_byte(device, 5, &byte);
		if (byte <= 1) goto next;
		/* for now only handle the symmetrical case */
		bank_sizes |= (1 << (bank +1));
	next:
		bank += 2;
		device += SMBUS_MEM_DEVICE_INC;
	}
	reg = bank_sizes << 8;
	reg |= 0x7; /* 32 clocks idle time */
	pcibios_write_config_word(I440GX_BUS, I440GX_DEVFN, 0x78, reg);
}

static void spd_set_nbxcfg(void)
{
	/*
	 * Effects:	Uses serial presence detect to set the
	 *              ECC support flags in the NBXCFG register
	 * FIXME:	Check for illegal/unsupported ram configurations and abort
	 */
	unsigned reg;
	unsigned index;
	unsigned device;

	/* Say all dimms have no ECC support */
	reg = 0xff;
	index = 0;
	
	device = SMBUS_MEM_DEVICE_START;
	while (device <= SMBUS_MEM_DEVICE_END) { 
		int status;
		unsigned char byte;

		status = smbus_read_byte(device, 11, &byte);
		if (status != 0) goto next;
#if !USE_ECC /* Disable ECC */
		byte = 0;
#endif
		/* 0 == None, 1 == Parity, 2 == ECC */
		if (byte != 2) goto next;
		reg ^= (1 << index);

		/* side two */
		/* number of physical banks */
		status = smbus_read_byte(device, 5, &byte);
		if (byte <= 1) goto next;
		/* There is only the symmetrical case */
		reg ^= (1 << (index +1));
	next:
		index += 2;
		device += SMBUS_MEM_DEVICE_INC;
	}
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x53, reg);
	/* Now see if reg is 0xff.  If it is we are done.  If not,
	 * we need to set 0x18 into regster 0x50.l
	 * we will do this in two steps, first or in 0x80 to 0x50.b,
	 * then or in 0x1 to 0x51.b
	 */
	printk_debug("spd_set_nbxcfg reg=0x%02x\n", reg);
	if (reg != 0xff) {
		unsigned char byte;
		pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x50, &byte);
		byte |= 0x80;
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x50, byte);
		pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x51, &byte);
		byte |= 1;
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x51, byte);
		/* try this.
		 * We should be setting bit 2 in register 76 and we're not
		 * technically we should see if CL=2 for the ram,
		 * but registered is so screwed up that it's kind of a lost 
		 * cause.
		 */
		pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, &byte);
		byte |= 4;
		pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, byte);
		printk_debug("spd_set_nbxcfg 0x76.b=0x%02x\n", byte);
	}
}

void sdram_set_spd_registers(void)
{
	spd_set_drb();
	spd_set_dramc();
	spd_set_rps();
	spd_set_sdramc();
	spd_set_pgpol();
	spd_set_nbxcfg();
}

void sdram_first_normal_reference(void)
{
	return;
}

void sdram_special_finishup(void)
{
	return;
}

static void set_ram_command(unsigned command)
{
	unsigned char byte;
	command &= 0x7;
	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, &byte);
	byte &= 0x1f;
	byte |= (command << 5);
	pcibios_write_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, byte);
	printk_debug("set_ram_command 0x76.b=%02x\n", byte);
}

#define RAM_COMMAND_NONE	0x0
#define RAM_COMMAND_NOOP	0x1
#define RAM_COMMAND_PRECHARGE	0x2
#define RAM_COMMAND_MRS		0x3
#define RAM_COMMAND_CBR		0x4

void sdram_set_command_none(void)
{
	set_ram_command(RAM_COMMAND_NONE);
}
void sdram_set_command_noop(void)
{
	set_ram_command(RAM_COMMAND_NOOP);
}
void sdram_set_command_precharge(void)
{
	set_ram_command(RAM_COMMAND_PRECHARGE);
}

static unsigned long dimm_base(int n)
{
	unsigned char byte;
	unsigned long result;
	if (n == 0) {
		return 0;
	}

	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x60 + (n - 1), &byte);
	result = byte;
	result <<= 23;
	return result;
}

static void dimms_read(unsigned long offset)
{
	int i;
	for(i = 0; i < 8; i++) {
		unsigned long dummy;
		unsigned long addr; 
		unsigned long next_base;

		next_base = dimm_base(i +1);
		addr =  dimm_base(i);
		if (addr == next_base) {
			continue;
		}
		addr += offset;
		printk_debug("Reading 0x%08x\n", addr);
		dummy = RAM(unsigned long, addr);
		printk_debug("Reading 0x%08x\n", addr ^ 0xddf8);
		dummy = RAM(unsigned long, addr ^ 0xdff8);
		printk_debug("Read 0x%08x 0x%08x\n", addr , addr ^ 0xddf8);
	}
}

void sdram_set_command_cbr(void)
{
	set_ram_command(RAM_COMMAND_CBR);
}

void sdram_assert_command(void)
{
	dimms_read(0x400);
}

void sdram_set_mode_register(void)
{
	unsigned char byte;
	unsigned cas_mode;
	set_ram_command(RAM_COMMAND_MRS);
	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x76, &byte);
	cas_mode = byte & 0x4;
	cas_mode ^= 4;
	cas_mode <<= 2;
	cas_mode |= 0x2a;
	cas_mode <<= 3;
	dimms_read(cas_mode);
}

void sdram_enable_refresh(void)
{
	spd_enable_refresh();
}


unsigned long sdram_get_ecc_size_bytes(void)
{
	unsigned char byte;
	unsigned long size;
	/* FIXME handle the no ram case. */
	/* Read the RAM SIZE */
	pcibios_read_config_byte(I440GX_BUS, I440GX_DEVFN, 0x67, &byte);
	/* Convert it to bytes */
	size = byte;
	size <<= 23;
#if !USE_ECC
	size = 0;
#endif
	return size;
}
