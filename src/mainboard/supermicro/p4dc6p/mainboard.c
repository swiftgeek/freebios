#include <arch/io.h>
#include <part/mainboard.h>
#include <printk.h>
#include <pci.h>
#include <pci_ids.h>
#include <southbridge/intel/82801.h>
#include <arch/smp/mpspec.h>
#include <pc80/isa_dma.h>
#include <cpu/i786/multiplier.h>
#include <cpu/i786/thermal_monitoring.h>
#include <cpu/p6/msr.h>
#include <superio/w83627hf.h>
#include <superio/generic.h>
#include <subr.h>
#include <smbus.h>
#include <ramtest.h>
#include <northbridge/intel/82860/rdram.h>
#include <pc80/mc146818rtc.h>


#define SMBUS_MEM_DEVICE_0 (0xa << 3)
extern int rdram_chips; /* number of ram chips on the rimms */


unsigned long initial_apicid[MAX_CPUS] =
{
	0, 6, 1, 7
};

#ifndef CPU_CLOCK_MULTIPLIER
#define CPU_CLOCK_MULTIPLIER XEON_X17
#endif

#define MAINBOARD_POWER_ON 1
#define MAINBOARD_POWER_OFF 2

#ifndef MAINBOARD_POWER_ON_AFTER_POWER_FAIL
#define MAINBOARD_POWER_ON_AFTER_POWER_FAIL MAINBOARD_POWER_ON
#endif

static void set_power_on_after_power_fail(int setting)
{
	switch(setting) {
	case MAINBOARD_POWER_ON:
	default:
		ich2_power_after_power_fail(1);
		w83627hf_power_after_power_fail(POWER_ON);
		break;
	case MAINBOARD_POWER_OFF:
		ich2_power_after_power_fail(0);
		w83627hf_power_after_power_fail(POWER_OFF);
		break;

	}
}

static void set_thermal_monitoring(int thermal_monitoring)
{
	int tm_high,tm_low;
	
	rdmsr(MISC_ENABLE,tm_low,tm_high);
	if(thermal_monitoring != THERMAL_MONITORING_OFF) {
		tm_low |= THERMAL_MONITORING_SET;
	}
	else {
		tm_low &= ~THERMAL_MONITORING_SET;
	}
	wrmsr(MISC_ENABLE,tm_low,tm_high);
	return;
}

void mainboard_fixup(void)
{
	int cpu_clock_multiplier;
	int power_on_after_power_fail;
	int thermal_monitoring;

	w83627hf_power_led(LED_ON);
	ich2_enable_ioapic();
	ich2_enable_serial_irqs();
	ich2_enable_ide(1,1);
	ich2_rtc_init();
	ich2_lpc_route_dma(0xff);
	isa_dma_init();

	cpu_clock_multiplier = CPU_CLOCK_MULTIPLIER;
	if(get_option(&cpu_clock_multiplier, "CPU_clock_speed"))
		cpu_clock_multiplier = CPU_CLOCK_MULTIPLIER;
	ich2_set_cpu_multiplier(cpu_clock_multiplier);

	power_on_after_power_fail = MAINBOARD_POWER_ON_AFTER_POWER_FAIL;
	if(get_option(&power_on_after_power_fail, "power_on_after_power_fail"))
		power_on_after_power_fail = MAINBOARD_POWER_ON_AFTER_POWER_FAIL;
	set_power_on_after_power_fail(power_on_after_power_fail);

	thermal_monitoring = THERMAL_MONITORING_OFF;
	if(get_option(&thermal_monitoring, "thermal_monitoring"))
		thermal_monitoring = THERMAL_MONITORING_OFF;
	set_thermal_monitoring(thermal_monitoring);

	return;
}

void hard_reset(void)
{
	ich2_hard_reset();
}

static void select_rdram_i2c(void)
{
        unsigned char byte;
        w83627hf_enter_pnp(SIO_BASE);
        byte = pnp_read_config(SIO_BASE, 0x2b);
        byte |= 0x30;
        pnp_write_config(SIO_BASE, byte, 0x2b);
        pnp_set_logical_device(SIO_BASE, GPIO_PORT2_DEVICE);
        pnp_set_enable(SIO_BASE, 1);
        byte = pnp_read_config(SIO_BASE, 0xf0);
        byte &= ~(1 << 3);
        pnp_write_config(SIO_BASE, byte, 0xf0);
        w83627hf_exit_pnp(SIO_BASE);
}

void cache_ram_start(void)
{
        int error;

        error = 0;
        /* displayinit MUST PRECEDE ALL PRINTK! */

#if 1
        displayinit();
#endif
        printk_info("Finding PCI configuration type.\n");
        pci_set_method();
        printk_info("Setting up smbus controller\n");
        smbus_setup();
        ich2_rtc_init();
        printk_info("Selecting rdram i2c bus\n");
        select_rdram_i2c();

#if 1
	display_smbus_spd();
#endif

        init_memory();

#if 0
        {
                unsigned long addr;
                for(addr =  0; addr < 0x20000000; addr += 0x02000000) {
                        ram_fill(addr, addr + 0x400);
                }
                /* Do some dummy writes to flush a write cache, in the
                 * processor.
                 */
                ram_fill(0xc0000000, 0xc0000400);
                for(addr =  0; addr < 0x20000000; addr += 0x02000000) {
                        ram_verify(addr, addr + 0x400, 1);
                }
        }
#endif
#if 0
        error |= ramcheck(0x00000000, 0x00080000, 20);
        error |= ramcheck(0x02000000, 0x02080000, 20);
        error |= ramcheck(0x04000000, 0x04080000, 20);
        error |= ramcheck(0x06000000, 0x06080000, 20);
        error |= ramcheck(0x08000000, 0x08080000, 20);
        error |= ramcheck(0x0a000000, 0x0a080000, 20);
        error |= ramcheck(0x0c000000, 0x0c080000, 20);

        error |= ramcheck(0x0e000000, 0x0e080000, 20);
        error |= ramcheck(0x10000000, 0x10080000, 20);
        error |= ramcheck(0x12000000, 0x12080000, 20);
        error |= ramcheck(0x14000000, 0x14080000, 20);
        error |= ramcheck(0x16000000, 0x16080000, 20);
        error |= ramcheck(0x18000000, 0x18080000, 20);
        error |= ramcheck(0x1a000000, 0x1a080000, 20);
        error |= ramcheck(0x1c000000, 0x1c080000, 20);
        error |= ramcheck(0x1e000000, 0x1e080000, 20);
#endif
#if 0
        error |= ramcheck(0x00000000, 0x00080000, 20);
#endif
#if 0
	display_rdram_regs(rdram_chips );
#endif
#if 0
	display_mch_regs();
#endif
        if (error) {
                printk_err("Something isn't working!!!\n");
                while(1);
        } else {
                printk_info("Leaving cacheram...\n");
        }

}






