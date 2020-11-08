#include "TextPrint.cpp"
#include "IDT.cpp"

extern const char Logo[];
extern const char Info[];


extern "C" void _start() {
	SetCursorPosition(PositionFromCoords(0, 0));
	InitializeIDT();

	PrintString(Logo);
	PrintString("\n\r");
	PrintString(Info);
	PrintString("\n\r");
	return;
}