#pragma once
#include "typedefs.h"
#include "Print.h"

struct MemoryMapEntry
{
uint64 BaseAddress;
uint64 RegionLength;
uint32 RegionType;
uint32 ExtendedAttributes;
};

extern uint8 MemoryRegionCount;
extern uint8 UsableMemoryRegionCount;

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint16 position);

MemoryMapEntry** GetUsableMemoryRegions();
