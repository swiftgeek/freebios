#ifndef __PREBOOT_H
#define __PREBOOT_H

typedef struct pre_boot_param {
	char sig[8];
	unsigned long int free_ramtop;
	unsigned long int save;
	unsigned long int stack;
	unsigned long int stacksize;
	struct lb_memory *lbmem;
} __attribute__ ((packed)) pre_boot_param_t;


extern struct lb_memory *lbmem;
extern struct lb_memory *get_lbmem(void);

extern unsigned long int preboot_ramtop;
extern pre_boot_param_t *preboot_param;

extern int main();

#endif
