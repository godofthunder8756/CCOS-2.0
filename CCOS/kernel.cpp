#include "TextPrint.cpp"
#include "IDT.cpp"

#include "Keyboard.cpp"

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
	PrintString(IntegerToString(-123456789));
	return;
}