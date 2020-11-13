#include "Print.h"

//stuff related to Printing onto the screen

uint16 CursorPosition;

void ClearScreen(uint64 ClearColor)
{
uint64 value = 0;
value += ClearColor << 8;
value += ClearColor << 24;
value += ClearColor << 40;
value += ClearColor << 56;
for(uint64* i = (uint64*)VGA_MEMORY; i < (uint64*)(VGA_MEMORY + 4000); i++)
{
*i = value;
}
}

void SetCursorPosition(uint16 position)
{
outb(0x3D4, 0x0F);
outb(0x3D5, (uint16)(position & 0xFF));
outb(0x3D4, 0x0E);
outb(0x3D5, (uint16)((position >> 8) & 0xFF));

CursorPosition = position;
}

uint16 CordPosTrans(uint16 x, uint16 y)
{
return y * VGA_WIDTH + x;
}

void PrintString(const char* str, uint8 color)
{
uint8* charPtr = (uint8*)str;
uint16 index = CursorPosition;
while(*charPtr != 0)
{

switch(*charPtr)
{
	case 10:
		index += VGA_WIDTH;
		break;
	case 13:
		index -= index % VGA_WIDTH;
		break;
	default:
		*(VGA_MEMORY + index * 2) = *charPtr;
		*(VGA_MEMORY + index * 2 + 1) = color;
		index++;
}

charPtr++;
}
SetCursorPosition(index);
}

void PrintChar(char chr, uint8 color)
{
*(VGA_MEMORY + CursorPosition * 2) = chr;
*(VGA_MEMORY + CursorPosition * 2 + 1) = color;
SetCursorPosition(CursorPosition + 1);
}

char hexToStringOutput[128];
template<typename T>
const char* HexToString(T value)
{
    T* valPtr = &value;
    uint8* ptr;
    uint8 temp;
    uint8 size = (sizeof(T)) * 2 - 1;
    uint8 i;
    for(i = 0; i < size; i++)
    {
    ptr = ((uint8*)valPtr + i);
    temp = ((*ptr & 0xF0) >> 4);
    hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    temp = ((*ptr & 0x0F));
    hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
    }
    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}

const char* HexToString(uint8 value) { return HexToString<uint8>(value); }
const char* HexToString(uint16 value) { return HexToString<uint16>(value); }
const char* HexToString(uint32 value) { return HexToString<uint32>(value); }
const char* HexToString(uint64 value) { return HexToString<uint64>(value); }
const char* HexToString(int8 value) { return HexToString<int8>(value); }
const char* HexToString(int16 value) { return HexToString<int16>(value); }
const char* HexToString(int32 value) { return HexToString<int32>(value); }
const char* HexToString(int64 value) { return HexToString<int64>(value); }

char integerToStringOutput[128];
template<typename T>
const char* IntegerToString(T value)
{
uint8 isNigga = 0;

if(value < 0)
{
isNigga = 1;
value *= -1;
integerToStringOutput[0] = '-';
}

uint8 size = 0;
uint64 sizeTester = (uint64)value;
while(sizeTester / 10 > 0)
{
sizeTester /= 10;
size++;
}

uint8 index = 0;
uint64 newValue = (uint64)value;
while(newValue / 10 > 0)
{
uint8 remainder = newValue % 10;
newValue /= 10;
integerToStringOutput[isNigga + size - index] = remainder + 48;
index++;
}
uint8 remainder = newValue % 10;
integerToStringOutput[isNigga + size - index] = remainder + 48;
integerToStringOutput[isNigga + size + 1] = 0;
return integerToStringOutput;
}

const char* IntegerToString(uint8 value) { return IntegerToString<uint8>(value); }
const char* IntegerToString(uint16 value) { return IntegerToString<uint16>(value); }
const char* IntegerToString(uint32 value) { return IntegerToString<uint32>(value); }
const char* IntegerToString(uint64 value) { return IntegerToString<uint64>(value); }
const char* IntegerToString(int8 value) { return IntegerToString<int8>(value); }
const char* IntegerToString(int16 value) { return IntegerToString<int16>(value); }
const char* IntegerToString(int32 value) { return IntegerToString<int32>(value); }
const char* IntegerToString(int64 value) { return IntegerToString<int64>(value); }

char floatToStringOutput[128];
const char* FloatToString(float value, uint8 decimalPlaces)
{
char* intPtr = (char*)IntegerToString((int)value);
char* floatPtr = floatToStringOutput;

if(value < 0)
{
value *= -1;
}

while(*intPtr != 0)
{
*floatPtr = *intPtr;
intPtr++;
floatPtr++;
}
*floatPtr = '.';
floatPtr++;

float newValue = value - (int)value;
for(uint8 i = 0; i < decimalPlaces; i++)
{
newValue *= 10;
*floatPtr = (int)newValue + 48;
newValue -= (int)newValue;
floatPtr++;
}

*floatPtr = 0;

return floatToStringOutput;
}
