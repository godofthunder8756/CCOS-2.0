#include "TextPrint.cpp"
#include "IDT.cpp"

#include "Keyboard.cpp"
#include "MemoryMap.cpp"

extern const char Logo[];
extern const char Info[];


extern "C" void _start() {
	SetCursorPosition(PositionFromCoords(0, 0));
	InitializeIDT();
	MainKeyBoardHandler = KeyboardHandler;
	/*
	PrintString(Logo);
	PrintString("\n\r");
	PrintString(Info);
	PrintString("\n\r");
	*/

	MemoryMapEntry** UsableMemoryMaps = GetUsableMemoryRegions();

	for (uint_8 i = 0; i < UsableMemoryRegionsCount; i++) {
		MemoryMapEntry* memMap = UsableMemoryMaps[i];
		PrintMemoryMap(memMap, CursorPosition);
	}

	return;
}