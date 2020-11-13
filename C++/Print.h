#pragma once
#include "IO.h"
#include "typedefs.h"
#include "TextColor.h"
#define VGA_MEMORY (unsigned char*)0xb8000
#define VGA_WIDTH 80

extern uint16 CursorPosition;

void ClearScreen(uint64 ClearColor = BACKGROUND_BLACK | FOREGROUND_GREEN);
void SetCursorPosition(uint16 position);
uint16 CordPosTrans(uint16 x, uint16 y);
void PrintString(const char* str, uint8 color = BACKGROUND_BLACK | FOREGROUND_GREEN);
void PrintChar(char chr, uint8 color = BACKGROUND_BLACK | FOREGROUND_GREEN);
const char* FloatToString(float value, uint8 decimalPlaces);

const char* HexToString(uint8 value);
const char* HexToString(uint16 value);
const char* HexToString(uint32 value);
const char* HexToString(uint64 value);
const char* HexToString(int8 value);
const char* HexToString(int16 value);
const char* HexToString(int32 value);
const char* HexToString(int64 value);

const char* IntegerToString(uint8 value);
const char* IntegerToString(uint16 value);
const char* IntegerToString(uint32 value);
const char* IntegerToString(uint64 value);
const char* IntegerToString(int8 value);
const char* IntegerToString(int16 value);
const char* IntegerToString(int32 value);
const char* IntegerToString(int64 value);
