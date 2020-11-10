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
uint_8 UsableMemoryRegionsCount;


MemoryMapEntry* UsableMemoryRegions[10];


void PrintMemoryMap(MemoryMapEntry* memoryMap, uint_16 position) {
	SetCursorPosition(position);

	PrintString("Memory Base: "); PrintString(IntegerToString(memoryMap->BaseAddress));
	SetCursorPosition(position + 80);
	PrintString("Region Length: "); PrintString(IntegerToString(memoryMap->RegionLength));
	SetCursorPosition(position + 160);
	PrintString("Memory Type: "); PrintString(IntegerToString(memoryMap->RegionType));
	SetCursorPosition(position + 240);
	PrintString("Memory Attributes: "); PrintString(IntegerToString(memoryMap->ExtendedAttributes));
	SetCursorPosition(position + 400);

}

bool MemoryRegionsGot = false;

MemoryMapEntry** GetUsableMemoryRegions() {
	
	if (MemoryRegionsGot) {
		return UsableMemoryRegions;
	}

	uint_8 UsableRegionIndex;
	for (uint_8 i = 0; i < MemoryRegionCount; i++) {
		MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
		memMap += i;
		if (memMap->RegionType == 1) {
			UsableMemoryRegions[UsableRegionIndex] = memMap;
			UsableRegionIndex++;
		}
	}
	UsableMemoryRegionsCount = UsableRegionIndex;
	
	MemoryRegionsGot = true;
	return UsableMemoryRegions;
}