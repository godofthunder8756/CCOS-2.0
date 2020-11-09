#include "TextPrint.cpp"
#include "IDT.cpp"

bool LeftShiftPressed = false;
bool RightShiftPressed = false;
uint_8 LastScanCode;
void StandardKeyboardHandler(uint_8 scanCode, uint_8 chr) {
	if (chr != 0) {
		switch (LeftShiftPressed | RightShiftPressed) {
		case true:
			PrintChar(chr - 32);
			break;
		case false:
			PrintChar(chr);
			break;
		}

	}
	else {
		switch (scanCode) {
		case 0x8E: //Backspace
			SetCursorPosition(CursorPosition - 1);
			PrintChar(' ');
			SetCursorPosition(CursorPosition - 1);
			break;
		case 0x2A: //Left Shift
			LeftShiftPressed = true;
			break;
		case 0xAA: //Left Shift Released
			LeftShiftPressed = false;
			break;
		case 0x36: //Right Shift
			LeftShiftPressed = true;
			break;
		case 0xB6: //Right Shift Released
			LeftShiftPressed = false;
			break;
		case 0x9C: //Enter
			PrintString("\n\r");
			break;
		}
	}
}

void KeyboardHandler0xE0(uint_8 scanCode) {
	switch (scanCode)
	{
	case 0x50:
		SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;
	default:
		break;
	}
}
void KeyboardHandler(uint_8 scanCode, uint_8 chr) {
	
	switch (LastScanCode){
	case 0xE0:
		KeyboardHandler0xE0(scanCode);
			break;
	default:
		StandardKeyboardHandler(scanCode, chr);
	}
	LastScanCode = scanCode;
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