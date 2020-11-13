#pragma once
#include "typedefs.h"
#include "KBScanCodeSet1.h"
#include "Print.h"
#include "IO.h"

struct IDT64
{
uint16 offset_low;
uint16 selector;
uint8 ist;
uint8 types_attr;
uint16 offset_mid;
uint32 offset_high;
uint32 zero;
};

extern void(*MainKeyboardHandler)(uint8 scanCode, uint8 chr);

void InitializeIDT();
