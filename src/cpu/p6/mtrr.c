/*
 * intel_mtrr.c: setting MTRR to decent values for cache initialization on P6
 *
 * Derived from intel_set_mtrr in intel_subr.c and mtrr.c in linux kernel
 *
 * Copyright 2000 Silicon Integrated System Corporation
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
 * Reference: Intel Architecture Software Developer's Manual, Volume 3: System Programming
 *
 * $Id: mtrr.c,v 1.1 2000/10/17 13:14:21 rminnich Exp $
 */

#include <cpu/p6/msr.h>
#include <cpu/p6/mtrr.h>

#define arraysize(x)   (sizeof(x)/sizeof((x)[0]))

static unsigned int mtrr_msr[] = {
	MTRRfix64K_00000_MSR, MTRRfix16K_80000_MSR, MTRRfix16K_A0000_MSR,
	MTRRfix4K_C0000_MSR, MTRRfix4K_C8000_MSR, MTRRfix4K_D0000_MSR, MTRRfix4K_D8000_MSR,
	MTRRfix4K_E0000_MSR, MTRRfix4K_E8000_MSR, MTRRfix4K_F0000_MSR, MTRRfix4K_F8000_MSR,
};

static unsigned char fixed_mtrr_values[][4] = {
	/* MTRRfix64K_00000_MSR, defines memory range from 0KB to 512 KB, each byte cover 64KB area */
	{MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK},
	{MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK},

	/* MTRRfix16K_80000_MSR, defines memory range from 512KB to 640KB, each byte cover 16KB area */
	{MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK},
	{MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK, MTRR_TYPE_WRBACK},

	/* MTRRfix16K_A0000_MSR, defines memory range from A0000 to C0000, each byte cover 16KB area */
	{MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB},
	{MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB, MTRR_TYPE_WRCOMB},

	/* MTRRfix4K_C0000_MSR, defines memory range from C0000 to C8000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_C8000_MSR, defines memory range from C8000 to D0000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_D0000_MSR, defines memory range from D0000 to D8000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_D8000_MSR, defines memory range from D8000 to E0000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_E0000_MSR, defines memory range from E0000 to E8000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_E8000_MSR, defines memory range from E8000 to F0000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_F0000_MSR, defines memory range from F0000 to F8000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},

	/* MTRRfix4K_F8000_MSR, defines memory range from F8000 to 100000, each byte cover 4KB area */
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
	{MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH, MTRR_TYPE_WRTHROUGH},
};

void
intel_enable_fixed_mtrr()
{
	unsigned long low, high;

	rdmsr(MTRRdefType_MSR, low, high);
	low |= 0xc00;
	wrmsr(MTRRdefType_MSR, low, high);
}

void
intel_enable_var_mtrr()
{
	unsigned long low, high;

	rdmsr(MTRRdefType_MSR, low, high);
	low |= 0x800;
	wrmsr(MTRRdefType_MSR, low, high);
}

/* setting fixed mtrr, you can do some experiments with different memory type 
   defined in the table "fixed_mtrr_values" */ 
void intel_set_fixed_mtrr()
{
	unsigned int i;
	unsigned long low, high;

	for (i = 0; i < arraysize(mtrr_msr); i++) {
		low = *(unsigned long *) fixed_mtrr_values[i*2];
		high = *(unsigned long *) fixed_mtrr_values[i*2+1];
		wrmsr(mtrr_msr[i], low, high);
	}

}

/* setting variable mtrr, comes from linux kernel source */
void intel_set_var_mtrr(unsigned int reg, unsigned long base, unsigned long size, unsigned char type)
{


	if (reg >= 8)
		return;

	if (size == 0) {
		/* The invalid bit is kept in the mask, so we simply clear the
		   relevant mask register to disable a range. */
		wrmsr (MTRRphysMask_MSR (reg), 0, 0);
	} else {
		wrmsr (MTRRphysBase_MSR (reg), base | type, 0);
		wrmsr (MTRRphysMask_MSR (reg), ~(size - 1) | 0x800, 0);
	}
}

/* some secret MSR registers make 5x performance boost,
   hardcoded for 128MB SDRAM on Celeron and PII */
void intel_l2_cache_on()
{
	unsigned long low, high;

        low = 0x134052b;
        high = 0x00;
        wrmsr(0x11e, low, high);	
}

/* setting up variable and fixed mtrr
   ToDo: 1. still need to find out how to set size and alignment correctly
         2. should we invalid cache by INVLD or WBINVD ?? */
#ifdef INTEL_PPRO_MTRR
#ifdef ENABLE_FIXED_AND_VARIABLE_MTRRS
void intel_set_mtrr(unsigned long rambase, unsigned long ramsizeK)
{
#ifdef SIS630
	/* hardcoded for 128MB SDRAM, 4 MB SMA */
	intel_set_var_mtrr(0, 0, 128 * 1024 * 1024, MTRR_TYPE_WRBACK);
	intel_set_var_mtrr(1, 124 * 1024 * 1024, 4 * 1024 * 1024, MTRR_TYPE_UNCACHABLE);
#else
	printk("Setting variable MTRR 0 to %dK\n", ramsizeK);
	intel_set_var_mtrr(0, 0, ramsizeK * 1024, MTRR_TYPE_WRBACK);
#endif
	intel_set_fixed_mtrr();

	/* enable fixed MTRR */
	intel_enable_fixed_mtrr();
	intel_enable_var_mtrr();

	//intel_l2_cache_on();
}
#else /* ENABLE_FIXED_AND_VARIABLE_MTRRS */
void intel_set_mtrr(unsigned long rambase, unsigned long ramsizeK)
{
	intel_set_var_mtrr(0, 0, ramsizeK * 1024, MTRR_TYPE_WRBACK);
	intel_enable_var_mtrr();
//	intel_set_fixed_mtrr();
}
#endif /* ENABLE_FIXED_AND_VARIABLE_MTRRS */
#endif /* INTEL_PPRO_MTRR */
