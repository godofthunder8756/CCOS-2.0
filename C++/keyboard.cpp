#include "keyboard.h"

bool LeftShiftHeld = false;
bool RightShiftHeld = false;
bool capslock = false;
uint8 LastScancode;

char keyboard_input = 0;
uint8 scancode_input = 0;
bool written = false;

void StandardKeyboardHandler(uint8 scanCode, uint8 chr)
{
	keyboard_input = chr;
	scancode_input = scanCode;
if(chr != 0)
{
switch(LeftShiftHeld | RightShiftHeld | capslock)
{
case true:
	PrintChar(chr - 32);
	break;
case false:
	PrintChar(chr);
	break;
}
}
else
{
switch(scanCode)
{
case 0x8E:
	SetCursorPosition(CursorPosition - 1);
	PrintChar(' ');
	SetCursorPosition(CursorPosition - 1);
	break;
case 0x2A:
	LeftShiftHeld = true;
	break;
case 0xAA:
	LeftShiftHeld = false;
	break;
case 0x36:
	RightShiftHeld = true;
	break;
case 0xB6:
	RightShiftHeld = false;
	break;
	/*
case 0x9C:
	PrintString("\n\r");
	break;
	*/
case 0x3A:
	if(capslock == false)
	capslock = true;
	else
	capslock = false;
	break;
}
}
written = true;
return;
}

void KeyboardHandler0xE0(uint8 scanCode)
{
switch(scanCode)
{
	case 0x50:
		SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;
	case 0x47:
		ClearScreen();
		SetCursorPosition(CordPosTrans(0, 0));
		PrintString("CCOS 2.0.1a - type 'help' for help\n\rCopyright (c) 2020 Aidan Ahern (MIT)\n\n\r");
		PrintString("root@DESKTOP# ");
		break;
	default:
		break;
}
}


void KeyboardHandler(uint8 scanCode, uint8 chr)
{
switch(LastScancode)
{
case 0xE0:
	KeyboardHandler0xE0(scanCode);
	break;
default:
	StandardKeyboardHandler(scanCode, chr);
}

LastScancode = scanCode;
}

char getc(void)
{

	char ch;

	while (!written) { ; }

	ch = keyboard_input;
	if (!ch)
	{
		if (scancode_input == 0x1C)
			ch = '\n';
		else if (scancode_input == 0x0E)
		{
			ch = '\b';
		}
		else
		{
			flush_stdin();
			return getc();
		}
	}

	written = false;

	return ch;

}

void flush_stdin(void)
{

	written = false;

	return;
}

int getline(char* dest, uint64 size)
{

	flush_stdin();

	for (int64 i = 0; i < size; i++)
	{
		uint8 ch = getc();

		if (ch == '\n')
		{
			dest[i] = 0;

			return 1;
		}
		else if (ch == '\b') {

			ch = 0;
			i -= 2;

			if (i < 0)
				i = 0;
		}
		else
			dest[i] = ch;
	}

	return 0;
}