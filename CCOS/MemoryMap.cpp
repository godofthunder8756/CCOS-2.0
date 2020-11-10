#pragma once
#include "Typedefs.cpp"
#include "TextPrint.cpp"

struct MemoryMapEntry {
	uint_64 BaseAddress;
	uint_64 RegionLength;
	uint_32 RegionType;
	uint_32 ExtendedAttributes;
};

extern uint_8 MemoryRegionCount;

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint_16 position) {
	SetCursorPosition(position);

	PrintString("Memory Base: "); PrintString(IntegerToString(memoryMap->BaseAddress));
	SetCursorPosition(position + 80);
	PrintString("Region Length: "); PrintString(IntegerToString(memoryMap->RegionLength));
	SetCursorPosition(position + 160);
	PrintString("Memory Type: "); PrintString(IntegerToString(memoryMap->RegionType));
	SetCursorPosition(position + 240);
	PrintString("Memory Attributes: "); PrintString(IntegerToString(memoryMap->ExtendedAttributes));
	SetCursorPosition(position + 320);

}