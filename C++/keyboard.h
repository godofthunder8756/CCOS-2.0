#pragma once
#include "typedefs.h"
#include "Print.h"
#include "IDT.h"
#include "IO.h"
#include "heap.h"
#include "shell.h"

extern bool LeftShiftHeld;
extern bool RightShiftHeld;
extern bool capslock;
extern uint8 LastScancode;

void StandardKeyboardHandler(uint8 scanCode, uint8 chr);

void KeyboardHandler0xE0(uint8 scanCode);

void KeyboardHandler(uint8 scanCode, uint8 chr);

void flush_stdin(void);

char getc(void);

int getline(char* dest, uint64 size);
