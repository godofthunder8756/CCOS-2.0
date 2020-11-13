#pragma once

#include "typedefs.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

void outb(uint16, uint8);
uint8 inb(uint16);
void outw(uint16, uint16);
void outl(uint16, uint32);
uint16 inw(uint16);
uint32 inl(uint16);
void RemapPic(void);
