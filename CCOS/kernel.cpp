#include "TextPrint.cpp"
#include "IDT.cpp"

void KeyboardHandler(uint_8 scanCode, uint_8 chr) {
	if (chr != 0) {
		PrintChar(chr);
	}
	else {
		switch (scanCode) {
		case 0x8E: //Backspace
				SetCursorPosition(CursorPosition - 1);
				PrintChar(' ');
				SetCursorPosition(CursorPosition - 1);
				break;
		}
	}
}

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
	return;
}