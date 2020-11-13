#include "IDT.h"
//interrupt handling time, yay

extern IDT64 _idt[256];
extern uint64 isr1;
extern "C" void LoadIDT();
void(*MainKeyboardHandler)(uint8 scanCode, uint8 chr);
void InitializeIDT()
{

_idt[1].zero = 0;
_idt[1].offset_low = (uint16)(((uint64)&isr1 & 0x000000000000ffff));
_idt[1].offset_mid = (uint16)(((uint64)&isr1 & 0x00000000ffff0000) >> 16);
_idt[1].offset_high = (uint32)(((uint64)&isr1 & 0xffffffff00000000) >> 32);
_idt[1].ist = 0;
_idt[1].selector = 0x08;
_idt[1].types_attr = 0x8e;

RemapPic();

outb(0x21, 0xfd);
outb(0xa1, 0xff);
LoadIDT();
}

extern "C" void isr1_handler()
{
uint8 scanCode = inb(0x60);
uint8 chr = 0;
if(scanCode < 0x3A)
{
	chr = KBSet1::ScanCodeLookupTable[scanCode];
}
if(MainKeyboardHandler != 0)
{
	MainKeyboardHandler(scanCode, chr);
}
outb(0x20, 0x20);
outb(0xa0, 0x20);
}
