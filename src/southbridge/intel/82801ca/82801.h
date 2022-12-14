#define PCI_DMA_CFG	0x90
#define SERIRQ_CNTL	0x64
#define GEN_CNTL	0xd0
#define GEN_STS		0xd4
#define RTC_CONF	0xd8
#define GEN_PMCON_3	0xa4

#define PCICMD     	0x04
#define PMBASE     	0x40
#define ACPI_CNTL  	0x44
#define BIOS_CNTL  	0x4E
#define GPIO_BASE  	0x58
#define GPIO_CNTL  	0x5C
#define PIRQA_ROUT 	0x60
#define PIRQE_ROUT 	0x68
#define COM_DEC    	0xE0
#define LPC_EN     	0xE6
#define FUNC_DIS   	0xF2

/* 1e f0 244e */

#define CMD        	0x04
#define SBUS_NUM   	0x19
#define SUB_BUS_NUM	0x1A
#define SMLT       	0x1B
#define IOBASE     	0x1C
#define IOLIM      	0x1D
#define MEMBASE    	0x20
#define MEMLIM     	0x22
#define CNF        	0x50
#define MTT        	0x70
#define PCI_MAST_STS	0x82

#define RTC_BUS 0
#define RTC_DEVFN ((0x1f << 3) + 0)
#define RTC_FAILED	(1 <<2)


#define SMBUS_BUS 0
#define SMBUS_DEVFN  ((0x1f << 3) + 3)
#define SMBUS_IO_BASE 0x1000

#define SMBHSTSTAT 0x0
#define SMBHSTCTL  0x2
#define SMBHSTCMD  0x3
#define SMBXMITADD 0x4
#define SMBHSTDAT0 0x5
#define SMBHSTDAT1 0x6
#define SMBBLKDAT  0x7
#define SMBTRNSADD 0x9
#define SMBSLVDATA 0xa
#define SMLINK_PIN_CTL 0xe
#define SMBUS_PIN_CTL  0xf 

/* Between 1-10 seconds, We should never timeout normally 
 * Longer than this is just painful when a timeout condition occurs.
 */
#define SMBUS_TIMEOUT (100*1000)
