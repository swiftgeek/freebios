#include <arch/io.h>
#include <printk.h>

#define RTC_PORT(x)	(0x70 + (x))

#define CMOS_READ(addr) ({ \
outb_p((addr),RTC_PORT(0)); \
inb_p(RTC_PORT(1)); \
})

#define CMOS_WRITE(val, addr) ({ \
outb_p((addr),RTC_PORT(0)); \
outb_p((val),RTC_PORT(1)); \
})

/* control registers - Moto names
 */
#define RTC_REG_A		10
#define RTC_REG_B		11
#define RTC_REG_C		12
#define RTC_REG_D		13


/**********************************************************************
 * register details
 **********************************************************************/
#define RTC_FREQ_SELECT	RTC_REG_A

/* update-in-progress  - set to "1" 244 microsecs before RTC goes off the bus,
 * reset after update (may take 1.984ms @ 32768Hz RefClock) is complete,
 * totalling to a max high interval of 2.228 ms.
 */
# define RTC_UIP		0x80
# define RTC_DIV_CTL		0x70
   /* divider control: refclock values 4.194 / 1.049 MHz / 32.768 kHz */
#  define RTC_REF_CLCK_4MHZ	0x00
#  define RTC_REF_CLCK_1MHZ	0x10
#  define RTC_REF_CLCK_32KHZ	0x20
   /* 2 values for divider stage reset, others for "testing purposes only" */
#  define RTC_DIV_RESET1	0x60
#  define RTC_DIV_RESET2	0x70
  /* Periodic intr. / Square wave rate select. 0=none, 1=32.8kHz,... 15=2Hz */
# define RTC_RATE_SELECT 	0x0F
#  define RTC_RATE_NONE		0x00
#  define RTC_RATE_32786HZ	0x01
#  define RTC_RATE_16384HZ	0x02
#  define RTC_RATE_8192HZ	0x03
#  define RTC_RATE_4096HZ	0x04
#  define RTC_RATE_2048HZ	0x05
#  define RTC_RATE_1024HZ	0x06
#  define RTC_RATE_512HZ	0x07
#  define RTC_RATE_256HZ	0x08
#  define RTC_RATE_128HZ	0x09
#  define RTC_RATE_64HZ		0x0a
#  define RTC_RATE_32HZ		0x0b
#  define RTC_RATE_16HZ		0x0c
#  define RTC_RATE_8HZ		0x0d
#  define RTC_RATE_4HZ		0x0e
#  define RTC_RATE_2HZ		0x0f

/**********************************************************************/
#define RTC_CONTROL	RTC_REG_B
# define RTC_SET 0x80		/* disable updates for clock setting */
# define RTC_PIE 0x40		/* periodic interrupt enable */
# define RTC_AIE 0x20		/* alarm interrupt enable */
# define RTC_UIE 0x10		/* update-finished interrupt enable */
# define RTC_SQWE 0x08		/* enable square-wave output */
# define RTC_DM_BINARY 0x04	/* all time/date values are BCD if clear */
# define RTC_24H 0x02		/* 24 hour mode - else hours bit 7 means pm */
# define RTC_DST_EN 0x01	/* auto switch DST - works f. USA only */

/**********************************************************************/
#define RTC_INTR_FLAGS	RTC_REG_C
/* caution - cleared by read */
# define RTC_IRQF 0x80		/* any of the following 3 is active */
# define RTC_PF 0x40
# define RTC_AF 0x20
# define RTC_UF 0x10

/**********************************************************************/
#define RTC_VALID	RTC_REG_D
# define RTC_VRT 0x80		/* valid RAM and time */
/**********************************************************************/


/* On PCs, the checksum is built only over bytes 16..45 */
#define PC_CKS_RANGE_START	16
#define PC_CKS_RANGE_END	45
#define PC_CKS_LOC		46

static int rtc_checksum_valid(void)
{
	int i;
	unsigned sum, old_sum;
	sum = 0;
	for(i = PC_CKS_RANGE_START; i <= PC_CKS_RANGE_END; i++) {
		sum += CMOS_READ(i);
	}
	sum &= 0xffff;
	old_sum = (CMOS_READ(PC_CKS_LOC) << 8) | CMOS_READ(PC_CKS_LOC+1);
	return sum == old_sum;
}

static void rtc_set_checksum(void)
{
	int i;
	unsigned sum;
	sum = 0;
	for(i = PC_CKS_RANGE_START; i <= PC_CKS_RANGE_END; i++) {
		sum += CMOS_READ(i);
	}
	sum &= 0xffff;
	CMOS_WRITE(((sum >> 8) & 0xff), PC_CKS_LOC);
	CMOS_WRITE(((sum >> 0) & 0xff), PC_CKS_LOC+1);
}

#define RTC_CONTROL_DEFAULT (RTC_24H)
#define RTC_FREQ_SELECT_DEFAULT (RTC_REF_CLCK_32KHZ | RTC_RATE_1024HZ)

#if 0 /* alpha setup */
#undef RTC_CONTROL_DEFAULT
#undef RTC_FREQ_SELECT_DEFAULT
#define RTC_CONTROL_DEFAULT (RTC_SQWE | RTC_24H)
#define RTC_FREQ_SELECT_DEFAULT (RTC_REF_CLCK_32KHZ | RTC_RATE_1024HZ)
#endif
void rtc_init(void)
{
	unsigned char x;
	int cmos_valid;
	/* See if there has been a CMOS power problem. */
	x = CMOS_READ(RTC_VALID);
	cmos_valid = !(x & RTC_VRT);

	/* See if there is a CMOS checksum error */
	cmos_valid = rtc_checksum_valid();

	if (!cmos_valid) {
		int i;
		printk_warning("RTC power problem, zeroing cmos\n");
		for(i = 0x0; i < 128; i++) {
			CMOS_WRITE(0, i);
		}
		
		/* Now setup a default date of Sat 1 January 2000 */
		CMOS_WRITE(0, 0x00); /* seconds */
		CMOS_WRITE(0, 0x02); /* minutes */
		CMOS_WRITE(1, 0x04); /* hours */
		CMOS_WRITE(7, 0x06); /* day of week */
		CMOS_WRITE(1, 0x07); /* day of month */
		CMOS_WRITE(1, 0x08); /* month */
		CMOS_WRITE(0, 0x09); /* year */
	}
	/* Setup the real time clock */
	CMOS_WRITE(RTC_CONTROL_DEFAULT, RTC_CONTROL);
	/* Setup the frequency it operates at */
	CMOS_WRITE(RTC_FREQ_SELECT_DEFAULT, RTC_FREQ_SELECT);
	/* Make certain we have a valid checksum */
	rtc_set_checksum();
	/* Clear any pending interrupts */
	(void) CMOS_READ(RTC_INTR_FLAGS);
}