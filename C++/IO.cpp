//stuff related to input/output
#include "IO.h"

void outb(uint16 port, uint8 val)
{
asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8 inb(uint16 port)
{
uint8 returnVal;
asm volatile("inb %1, %0" : "=a"(returnVal) : "Nd"(port));
return returnVal;
}

void outw(uint16 port, uint16 data) { // output data to the bus

	asm volatile ("outw %0, %1" : : "a"(data), "d"(port));

}

uint16 inw(uint16 port) { // read from the bus

	uint16 returnval;

	asm volatile ("inw %1, %0" :  "=a"(returnval) : "d" (port));

	return returnval;

}

void outl(uint16 port, uint32 data) { // output data to the bus

	asm volatile ("outl %0, %1" : : "a"(data), "d"(port));

}

uint32 inl(uint16 port) { // read from the bus

	uint32 returnval;

	asm volatile ("inl %1, %0" :  "=a"(returnval) : "d" (port));

	return returnval;

}

void RemapPic(void) {

	uint8 a1, a2;

	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 8);

	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);


	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);

	return;
}

