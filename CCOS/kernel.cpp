#include "TextPrint.h"
#include "IDT.h"

#include "Keyboard.h"
#include "MemoryMap.h"
#include "Heap.h"
#include "Memory.h"

extern const char Logo[];
extern const char Info[];


extern "C" void _start() {
	SetCursorPosition(PositionFromCoords(0, 0));
	InitializeIDT();
	MainKeyBoardHandler = KeyboardHandler;
	
	PrintString(Logo);
	PrintString("\n\r");
	PrintString(Info);
	PrintString("\n\r");
	

	MemoryMapEntry** UsableMemoryMaps = GetUsableMemoryRegions();


	InitializeHeap(0x100000, 0x100000);
	
	

	return;
}