/* 

   Intel FW82815EP northbridge related... 
   
   (c) 2001 HeeChul Yun (hcyun@etri.re.kr)

*/ 

#include <mem.h>
#include <part/sizeram.h>
#include <pci.h>
#include <printk.h>

#define REG_DRP 0x52
#define REG_DRP2 0x54

static int DRP_sizetbl[] = {
  0, 32, 32, 48,
  64, 64, 96, 128,
  128, 128, 128, 192,
  256, 256, 256, 512
};
  
struct mem_range *sizeram(void)
{
  static struct mem_range mem[3];
  unsigned long totalmem, curmem;
  unsigned char regval;

  struct pci_dev *pcidev;

  totalmem = 0; 

  pcidev = pci_find_slot(0, PCI_DEVFN(0,0));
  pci_read_config_byte(pcidev, REG_DRP, &regval);

  printk_info("DRP0 = 0x%x\n", regval);  
  curmem = DRP_sizetbl[regval & 0x0F];
  printk_info("DIMM0 - size = %ldM\n", curmem);
  totalmem += curmem; 
  
  curmem = DRP_sizetbl[(regval & 0xF0) >> 8 ];
  printk_info("DIMM1 - size = %ldM\n", curmem);
  totalmem += curmem; 
  
  pci_read_config_byte(pcidev, REG_DRP2, &regval);
  printk_info("DRP1 = 0x%x\n", regval);  
  curmem = DRP_sizetbl[regval & 0x0F];
  printk_info("DIMM2 - size = %ldM\n", curmem );
  totalmem += curmem; 

  mem[0].basek = 0;
  mem[0].sizek = 640;
  mem[1].basek = 1024;
  mem[1].sizek = totalmem*1024 - mem[1].basek;
  mem[2].basek = 0;
  mem[2].sizek = 0;
  return &mem;
}








