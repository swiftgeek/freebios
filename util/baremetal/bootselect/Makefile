
ARCH = i386

CC = gcc

CFLAGS = -I ../include -I ../include/$(ARCH) -O2 -DZKERNEL_START=0xfff00000

DEPS =  ../lib/_main.o bootselect.o rom_fill_inbuf.o chooser.o   ../lib/baremetal.a

bootselect.elf: $(DEPS)
	ld -defsym HEAPSIZE=0x8000 -T elfImage.lds $(DEPS)  -o bootselect.elf

clean:
	rm bootselect.elf *.o
