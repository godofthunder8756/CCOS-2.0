#include "IDT.h"

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void LoadIDT();
void (*MainKeyBoardHandler)(uint_8 scanCode, uint_8 chr);

void InitializeIDT(){

_idt[1].zero = 0;
_idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000ffff));
_idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0x000000000ffff0000) >> 16);
_idt[1].offset_high = (uint_64)(((uint_64)&isr1 & 0xffffffff88888888) >> 32);
_idt[1].ist = 0;
_idt[1].selector = 0x08;
_idt[1].types_attr = 0x8e;

RemapPic();

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}


extern "C" void isr1_handler() {
	uint_8 scanCode = inb(0x60);
	uint_8 chr=0;

	if (scanCode < 0x3A) {
		chr = KBSet1::ScanCodeLookupTable[scanCode];
	}
	if (MainKeyBoardHandler != 0) {
		MainKeyBoardHandler(scanCode, chr);
	}
	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}