/* getpir.c : This software is released under GPL
   For Linuxbios use only
   Aug 26 2001 , Nikolai Vladychevski, <niko@isl.net.mx>
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "pci.h"
#include "pirq_routing.h"
#include  "types.h"
#include  "kmalloc.h"


#define PIRQ_SIGNATURE  (('$' << 0) + ('P' << 8) + ('I' << 16) + ('R' << 24))
#define PIRQ_VERS 0x0100

struct irq_info se_arr[50];
struct irq_routing_table rt;
unsigned short ts;


int calc_checksum() {
	long sum=0,i,j;
	u8 *addr,sum2=0,data;
    
	addr= (u8 *) &rt;
	for (i=0;i<sizeof(struct irq_routing_table);i++) sum2 += addr[i];
	for (i=0;i<ts;i++) {
		addr= (u8 *) &se_arr[i];
		for (j=0;j<sizeof(struct irq_info);j++) sum2+=addr[j];
	}
	return(sum2);
}	

main ()
{
	FILE *fmem, *fpir;
	size_t rcount=0;
	unsigned long b,p,pir=PIRQ_SIGNATURE;
	unsigned long count;
	int i,valid=1,print=0;
	char cksum=0;
	unsigned char *ptr;

	if (getuid()) { perror("Run me as root, I need access to /dev/mem"); exit(1);}
	printf("Opening memory...\n");
	fmem=fopen("/dev/mem","r"); 
	do {
		rcount=fread(&b,1,4,fmem);
		if (rcount>0) {
			if (b==pir) {
				valid=1;
				printf("Found PCI IRQ Routing table signature at %x bytes from top of the memory\nValidating../\n",count);
				rt.signature=PIRQ_SIGNATURE;
				ptr=(char*) &rt;
				ptr=ptr+4;   // signature was read, advance 4 bytes
				rcount=fread(ptr,1,sizeof(struct irq_routing_table)-4,fmem);
				count=count+rcount;
				printf("Version is:%d Table size:%d\n",rt.version,rt.size);
				if (rt.version!=PIRQ_VERS) {printf("Invalid version\n");valid=0;}
				if (rt.size<32) {printf(" Invalid table size\n"); valid=0;}
				if (rt.size%16) {printf (" Invalid table size (not a multiple of 16)\n"); valid=0;}
				if (valid) {
					//	read slot entries
					ts=(rt.size-32)/16;
					printf("Reading %d slot entries...\n",ts);
					for (i=0;i<ts;i++) {
						rcount=fread(&se_arr[i],1,16,fmem);
						count=count+rcount;
					}
					print=1;
					break;
				}
			} else {
				count=count+rcount;
			}
		}
	} while (rcount>0);
	if (!calc_checksum()) printf("Checksum is ok!\n");
	printf("Closing memory\n");
	fclose(fmem);

	if (!print) {printf ("No table for you...\n");return(0);}

	printf("Creating irq_tables.c .....\n");
	fpir=fopen("irq_tables.c","w");
	if (!fpir) {printf("Failed creating file!\n");exit(2);}
 
	fprintf(fpir,"/* This file was generated by getpir.c, do not modify! \n   (but if you do, please run checkpir on it to verify)\n");
	fprintf(fpir,"   Contains the IRQ Routing Table dumped directly from your memory , wich BIOS sets up\n\n");
	fprintf(fpir,"   Documentation at : http://www.microsoft.com/hwdev/busbios/PCIIRQ.HTM\n*/\n\n");
	fprintf(fpir,"#include <arch/pirq_routing.h>\n\n");
	fprintf(fpir,"const struct irq_routing_table intel_irq_routing_table = {\n");
	fprintf(fpir,"\tPIRQ_SIGNATURE,  /* u32 signature */\n");
	fprintf(fpir,"\tPIRQ_VERSION,    /* u16 version   */\n");
	fprintf(fpir,"\t32+16*%d,	 /* there can be total %d devices on the bus */\n",ts,ts);
	fprintf(fpir,"\t0x%02x,		 /* Where the interrupt router lies (bus) */\n",rt.rtr_bus);
	fprintf(fpir,"\t(0x%02x<<3)|0x%01x,   /* Where the interrupt router lies (dev) */\n",rt.rtr_devfn>>3, rt.rtr_devfn&7);
	fprintf(fpir,"\t%#x,		 /* IRQs devoted exclusively to PCI usage */\n",rt.exclusive_irqs);
	fprintf(fpir,"\t%#x,		 /* Vendor */\n",rt.rtr_vendor);
	fprintf(fpir,"\t%#x,		 /* Device */\n",rt.rtr_device);
	fprintf(fpir,"\t%#x,		 /* Crap (miniport) */\n",rt.miniport_data);
	fprintf(fpir,"\t{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */\n");
	fprintf(fpir,"\t%#x,         /*  u8 checksum , this hase to set to some value that would give 0 after the sum of all bytes for this structure (including checksum) */\n",rt.checksum);
	fprintf(fpir,"\t{\n");
	fprintf(fpir,"\t\t/* bus,     dev|fn,   {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap},  slot, rfu */\n");
	for (i=0;i<ts;i++) {
		fprintf(fpir,"\t\t{0x%02x,(0x%02x<<3)|0x%01x, {{0x%02x, 0x%04x}, {0x%02x, 0x%04x}, {0x%02x, 0x%04x}, {0x%02x, 0x0%04x}}, 0x%x, 0x%x},\n",
			se_arr[i].bus, se_arr[i].devfn>>3, se_arr[i].devfn&7,
			se_arr[i].irq[0].link, se_arr[i].irq[0].bitmap, se_arr[i].irq[1].link,
			se_arr[i].irq[1].bitmap, se_arr[i].irq[2].link, se_arr[i].irq[2].bitmap,
			se_arr[i].irq[3].link, se_arr[i].irq[3].bitmap, se_arr[i].slot, 
			se_arr[i].rfu);
	} 
	fprintf(fpir,"\t}\n");
	fprintf(fpir,"};\n");
	fclose(fpir);
	printf("Done, you can move the file to the LinuxBios tree now.\n");
}
