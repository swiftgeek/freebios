#include <logbuf_subr.h>

#define LOGBUF_SIZE  1024

// KEEP THIS GLOBAL. 
// I need the address so I can watch it with the ARIUM hardware. RGM.
char logbuf[LOGBUF_SIZE];
int logbuf_offset = 0;

void logbuf_tx_byte(unsigned char byte)
{
	logbuf[logbuf_offset] = byte;
	logbuf_offset = (logbuf_offset +1) % LOGBUF_SIZE;
}
