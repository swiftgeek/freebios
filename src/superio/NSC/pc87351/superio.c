/*
   This is the superio config file for the National Semiconductor
   pc87351 superio chip
*/

#include <pci.h>
#include <cpu/p5/io.h>
#include <serial_subr.h>
#include <printk.h>

// just define these here. We may never need them anywhere else
#define FLOPPY_DEVICE	   0
#define PARALLEL_DEVICE	   1
#define COM1_DEVICE	   3
#define COM2_DEVICE	   2
#define SYSTEM_WAKEUP_CONTROL 4
#define KBC_DEVICE	   6	
#define MOUSE_DEVICE	   5
#define GPIO_DEVICE	   7
#define FAN_SPEED_DEVICE   8

#define FLOPPY_DEFAULT_IOBASE	0x3f0
#define FLOPPY_DEFAULT_IRQ	6
#define FLOPPY_DEFAULT_DRQ	2
#define PARALLEL_DEFAULT_IOBASE	0x378
#define PARALLEL_DEFAULT_IRQ	7
#define PARALLEL_DEFAULT_DRQ	4 /* No dma */
#define COM1_DEFAULT_IOBASE	0x3f8
#define COM1_DEFAULT_IRQ	4
#define COM1_DEFAULT_BAUD	115200
#define COM2_DEFAULT_IOBASE	0x2f8
#define COM2_DEFAULT_IRQ	3
#define COM2_DEFAULT_BAUD	115200
#define KBC_DEFAULT_IOBASE0	0x60
#define KBC_DEFAULT_IOBASE1	0x64
#define KBC_DEFAULT_IRQ0	0x1
#define MOUSE_DEFAULT_IRQ0      0x0c

// funny how all these chips are "pnp compatible", and they're all different. 
#define PNP_BASE_ADDR 0x2e

static void setup_devices(struct superio *sio);

struct superio_control superio_NSC_pc87351_control = {
        pre_pci_init:   (void *) 0,
        init:           setup_devices, 
        finishup:       (void *) 0,
        defaultport:    PNP_BASE_ADDR,
        name:           "National Semiconductor pc87351"
};

void
enter_pnp(struct superio *sio)
{
       // The 87351 dosen't seem to need this
	// unlock it  
/*	outb(0x87, sio->port);
	outb(0x87, sio->port);
*/
}

void
exit_pnp(struct superio *sio)
{
       // The 87351 dosen't seem to need this

	/* all done. */
	// select configure control
/*
	outb(0xaa, sio->port);
*/
}

static void write_config(struct superio *sio, 
	unsigned char value, unsigned char reg)
{
	outb(reg, sio->port);
	outb(value, sio->port +1);
}

static unsigned char read_config(struct superio *sio, unsigned char reg)
{
	outb(reg, sio->port);
	return inb(sio->port +1);
}
static void set_logical_device(struct superio *sio, int device)
{
	write_config(sio, device, 0x07);
}

static void set_irq0(struct superio *sio, unsigned irq)
{
	write_config(sio, irq, 0x70);
}

static void set_irq1(struct superio *sio, unsigned irq)
{
	write_config(sio, irq, 0x72);
}

static void set_drq(struct superio *sio, unsigned drq)
{
	write_config(sio, drq & 0xff, 0x74);
}

static void set_iobase0(struct superio *sio, unsigned iobase)
{
	write_config(sio, (iobase >> 8) & 0xff, 0x60);
	write_config(sio, iobase & 0xff, 0x61);
}

static void set_iobase1(struct superio *sio, unsigned iobase)
{
	write_config(sio, (iobase >> 8) & 0xff, 0x62);
	write_config(sio, iobase & 0xff, 0x63);
}


static void set_enable(struct superio *sio, int enable)
{
	write_config(sio, enable?0x1:0x0, 0x30);
#if 1
	if (enable) {
		printk_debug("enabled superio device: %d\n", 
			read_config(sio, 0x07));
	}
#endif
}

static void set_mux_pins(struct superio *sio, unsigned char val)
{
   write_config(sio,val,0x22);
}

static void set_conf3(struct superio *sio, unsigned char val)
{
   write_config(sio,val,0x23);
}

static void setup_parallel(struct superio *sio)
{
	/* Remember the default resources */
	unsigned iobase = PARALLEL_DEFAULT_IOBASE;
	unsigned irq = PARALLEL_DEFAULT_IRQ;
	unsigned drq = PARALLEL_DEFAULT_DRQ;
	/* Select the device */
	set_logical_device(sio, PARALLEL_DEVICE);
	/* Disable it while initializing */
	set_enable(sio, 0);
	if (sio->lpt) {
		set_iobase0(sio, iobase);
		set_irq0(sio, irq);
		set_drq(sio, drq);
		set_enable(sio, 1);
	}
}

// test a non-fifo uart init. Stupid chip.
/* Line Control Settings */
#ifndef TTYS0_LCS
/* Set 8bit, 1 stop bit, no parity */
#define TTYS0_LCS       0x3
#endif

#define UART_LCS        TTYS0_LCS

/* Data */
#define UART_RBR 0x00
#define UART_TBR 0x00


        
/* Control */
#define UART_IER 0x01
#define UART_IIR 0x02
#define UART_FCR 0x02
#define UART_LCR 0x03
#define UART_MCR 0x04
#define UART_DLL 0x00
#define UART_DLM 0x01

/* Status */
#define UART_LSR 0x05
#define UART_MSR 0x06
#define UART_SCR 0x07

inline void uart_init_nofifo(unsigned base_port, unsigned divisor)
{       
        /* disable interrupts */
        outb(0x0, base_port + UART_IER); 
#if 0
        /* enable fifo's */
        outb(0x01, base_port + UART_FCR);
#else
        outb(0x06, base_port + UART_FCR);
#endif
        /* Set Baud Rate Divisor to 12 ==> 115200 Baud */
        outb(0x80 | UART_LCS, base_port + UART_LCR);
        outb(divisor & 0xFF,   base_port + UART_DLL);
        outb((divisor >> 8) & 0xFF,    base_port + UART_DLM);
        outb(UART_LCS, base_port + UART_LCR);
}


static void setup_com(struct superio *sio,
	struct com_ports *com, int device)
{
	// set baud, default to 115200 if not set.
	int divisor = 115200/(com->baud ? com->baud : 1);
	printk_debug("%s com device: %02x\n", 
			com->enable? "Enabling" : "Disabling", device);
	/* Select the device */
	set_logical_device(sio, device);
	/* Disable it while it is initialized */
	set_enable(sio, 0);

	if (com->enable) {
		printk_debug("  iobase = 0x%04x  irq=%d\n",
				com->base, com->irq);
		set_iobase0(sio, com->base);
		set_irq0(sio, com->irq);
		/* We are initialized so enable the device */
		set_enable(sio, 1);
		/* Now initialize the com port */
		uart_init(com->base, divisor);
	}
}

static void setup_floppy(struct superio *sio)
{
	/* Remember the default resources */
	unsigned iobase = FLOPPY_DEFAULT_IOBASE;
	unsigned irq = FLOPPY_DEFAULT_IRQ;
	unsigned drq = FLOPPY_DEFAULT_DRQ;
	/* Select the device */
	set_logical_device(sio, FLOPPY_DEVICE);
	/* Disable it while initializing */
	set_enable(sio, 0);
	if (sio->floppy) {
		set_iobase0(sio, iobase);
		set_irq0(sio, irq);
		set_drq(sio, drq);
		set_enable(sio, 1);
	}
}


#if NO_KEYBOARD==0

void pc_keyboard_init();

static void setup_keyboard(struct superio *sio)
{
	/* Remember the default resources */
	unsigned iobase0 = KBC_DEFAULT_IOBASE0;
	unsigned iobase1 = KBC_DEFAULT_IOBASE1;
	unsigned irq0 = KBC_DEFAULT_IRQ0;
	/* Select the device */
	set_logical_device(sio, KBC_DEVICE);
	/* Disable it while initializing */
	set_enable(sio, 0);
	if (sio->keyboard) {
		set_iobase0(sio, iobase0);
		set_iobase1(sio, iobase1);
		set_irq0(sio, irq0);
		set_enable(sio, 1);
		/* Initialize the keyboard */
		pc_keyboard_init();
	}
}
#endif

#if ENABLE_MOUSE==1
static void setup_mouse(struct superio *sio)
{
	/* Remember the default resources */
	unsigned irq0 = MOUSE_DEFAULT_IRQ0;
	/* Select the device */
	set_logical_device(sio, MOUSE_DEVICE);
	/* Disable it while initializing */
	set_enable(sio, 0);
	if (sio->mouse) {
		set_irq0(sio, irq0);
		set_enable(sio, 1);
	}
}
#endif

static void setup_devices(struct superio *sio)
{
	if (sio->port == 0) {
		sio->port = sio->super->defaultport;
	}
	if (sio->com1.base == 0)	sio->com1.base = COM1_DEFAULT_IOBASE;
	if (sio->com1.irq == 0) 	sio->com1.irq = COM1_DEFAULT_IRQ;
	if (sio->com1.baud == 0)	sio->com1.baud = COM1_DEFAULT_BAUD;
	if (sio->com2.base == 0) 	sio->com2.base = COM2_DEFAULT_IOBASE;
	if (sio->com2.irq == 0) 	sio->com2.irq = COM2_DEFAULT_IRQ;
	if (sio->com2.baud == 0)	sio->com2.baud = COM2_DEFAULT_BAUD;

	enter_pnp(sio);

	/* setup pins to be IRQ1, 3-7 and 12. 
	   Default is to enable PCICLK and SERIRQ and GPIO.
	   Bits7-1 = Default;
	   Bit0 = 0;  Default = 1;
        */ 
	set_mux_pins(sio,0xa0);
	
	/* setup more pin mux options */
	set_conf3(sio,0x01);
		
	/* enable/disable floppy */
	setup_floppy(sio);

	/* enable or disable parallel */
	setup_parallel(sio);

	/* enable/disable com1 */
	setup_com(sio, &sio->com1,  COM1_DEVICE);

	/* enable/disable com2 */
	setup_com(sio, &sio->com2,  COM2_DEVICE);

#if ENABLE_MOUSE==1
	 setup_mouse(sio);
#endif

#if NO_KEYBOARD==0
	/* enable/disable keyboard */
	setup_keyboard(sio);
#endif


/*	//  gpio_port2
	set_logical_device(sio, GPIO_PORT2_DEVICE);
	set_enable(sio, sio->gpio2);

	//  gpio_port3
	set_logical_device(sio, GPIO_PORT3_DEVICE);
	set_enable(sio, sio->gpio3);
*/

	exit_pnp(sio);
}


#ifndef USE_NEW_SUPERIO_INTERFACE

// this must die soon. 
void
final_superio_fixup()
{
/*
	static struct superio temp = { &superio_NSC_pc87351_control, 
				       .com1={1}, .floppy=1};	
	finishup(&temp); 

    enable_com(PNP_COM1_DEVICE);
    enable_com(PNP_COM2_DEVICE);

    exit_pnp();
*/
}
#endif
