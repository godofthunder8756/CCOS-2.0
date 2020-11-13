//kernel, contains the "main" function (_start)
#include "Print.h"
#include "IDT.h"
#include "keyboard.h"
#include "MemoryMap.h"
#include "heap.h"
#include "shell.h"

extern const char Test[];
extern const char Logo[];

extern "C" void _start()
{

    ClearScreen();
    SetCursorPosition(CordPosTrans(0, 0));
    InitializeIDT();
    MainKeyboardHandler = KeyboardHandler;
    flush_stdin();
    InitializeHeap(0x100000, 0x100000);
    PrintString(Logo);
    PrintString("\n\r");

    

    PrintString(Test);
    PrintString("\r");
    int intyboi = 69420666;
    PrintString(IntegerToString(intyboi));
    PrintString(" - displaying an integer\n\r");
    float floatyboi = -420.69f;
    PrintString(FloatToString(floatyboi, 2));
    PrintString(" - displaying a float\n\r");
    PrintString("Number of memory regions: ");
    PrintString(IntegerToString(MemoryRegionCount));
    MemoryMapEntry** UsableMemoryMaps = GetUsableMemoryRegions();
    PrintString("\n\r");
    PrintString("Number of usable memory regions: ");
    PrintString(IntegerToString(UsableMemoryRegionCount));
    PrintString("\n\n\r");
    /*
    PrintString("Information about all usable memory regions: ");
    PrintString("\n\n\r");

    for(uint8 i = 0; i < UsableMemoryRegionCount; i++)
    {
    	MemoryMapEntry* memMap = UsableMemoryMaps[i];
    	PrintMemoryMap(memMap, CursorPosition);
    }
	*/
	uint64* TestAddress = (uint64*)malloc(0x08);
	*TestAddress = 1857387164759173;
	PrintString(IntegerToString(*TestAddress));
	PrintString(" - Allocating dynamic memory to a 64-bit int.\n\r");
	uint64* TestAddress2 = (uint64*)realloc(TestAddress, 0x08);
	PrintString(IntegerToString(*TestAddress2));
	PrintString(" - Reallocating dynamic memory to a 64-bit int.\n\r");
	uint64* TestAddress3 = (uint64*)calloc(0x08);
	PrintString(IntegerToString(*TestAddress3));
	PrintString(" - Clearing the allocated memory\n\n\r");
	PrintString("Press the \"home\" key on your keyboard to start the shell.\n\r");
    SetCursorPosition(CordPosTrans(0, 89));
    StartShell();
    return;
}