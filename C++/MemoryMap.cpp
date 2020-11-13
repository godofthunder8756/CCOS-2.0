#include "MemoryMap.h"

uint8 UsableMemoryRegionCount;
MemoryMapEntry* UsableMemoryRegions[10];

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint16 position)
{
SetCursorPosition(position);
PrintString("Memory Base: "); PrintString(IntegerToString(memoryMap->BaseAddress));
SetCursorPosition(position + 80);
PrintString("Region Length: "); PrintString(IntegerToString(memoryMap->RegionLength));
SetCursorPosition(position + 160);
PrintString("Memory Type: "); PrintString(IntegerToString(memoryMap->RegionType));
SetCursorPosition(position + 240);
PrintString("Memory Attributes: "); PrintString(HexToString(memoryMap->ExtendedAttributes));
SetCursorPosition(position + 400);
}

bool MemoryRegionsGot = false;

MemoryMapEntry** GetUsableMemoryRegions()
{
if(MemoryRegionsGot)
{
return UsableMemoryRegions;
}
uint8 UsableRegionIndex;
for(uint8 i = 0; i < MemoryRegionCount; i++)
{
MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
memMap += i;
if(memMap->RegionType == 1)
{
UsableMemoryRegions[UsableRegionIndex] = memMap;
UsableRegionIndex++;
}
}
UsableMemoryRegionCount = UsableRegionIndex;
MemoryRegionsGot = true;
return UsableMemoryRegions;
}
