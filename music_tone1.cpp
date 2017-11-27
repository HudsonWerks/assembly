//#include <sys/io.h>
#include <io.h>
//#include <asm/io.h>
#include <stdio.h>
#include <time.h>

int main()
{
	unsigned char orgbits;
	unsigned char bits;

	//open port to be accessed
	ioperm(0x42, 2, 1);

	//send control info to control register
	outb(0xB6, 0x43);

	//For D3 note 1.1931Mhz/147HZ = 8116 = 1FB4
	outb(0xB4, 0x42);
	outb(0x1F, 0x42);

	//turn on speaker
	ioperm(0x61, 1, 1);
	orgbits = inb(0x61);
	printf("original bits:%d\n", orgbits);
	bits = orgbits | 3;
	printf("after |3, bits:%d\n", bits);

	// turn speaker on via PB0 and PB1 of port 61H
	outb(bits, 0x61);
	sleep(5);
	outb(orgbits, 0x61);
	sleep(2);

	//close IO ports
	ioperm(0x42, 2, 0);
	ioperm(0x61, 1, 0);
	printf("Program is finished:\n ");

	return 0;
}
