#include "commands.h"

char ver[] = "-v";
char help[] = "help";
char ls[] = "ls";
char install[] = "install";
char license[] = "-l";
char repository[] = "rep";
char test[] = "test";
void verFunc()
{
	PrintString("CCOS 2.0.1a\n\r");
	return;
}

void helpFunc()
{
	PrintString("PRESS THE HOME KEY TO CLEAR/RESET\n\r");
	PrintString("-v - displays the version\n\r");
	PrintString("help - shows avaible commands\n\r");
	PrintString("echo [value] - displays a value\n\r");
	PrintString("ls - displays the files\n\r");
	PrintString("install - installs the OS onto the hard drive\n\r");
	PrintString("-l - shows the license (clear before and after recommended)\n\r");
	PrintString("dispmem prints hex dump of memory\n\r");
	PrintString("rep - sends a link to the github repository\n\r");
	return;
}

bool echo(char* commandboi)
{
	if (commandboi[0] == 'e' && commandboi[1] == 'c' && commandboi[2] == 'h' && commandboi[3] == 'o' && commandboi[4] == ' ')
	{
		for(int i = 5; i < 160; i++)
			PrintChar(commandboi[i]);
		return true;
	}
	return false;
}

void lsFunc()
{
	PrintString("None, operating system not installed on the hard drive (coming soon)\n\r");
	return;
}

void installFunc()
{
	PrintString("COMING SOON\n\r");
	return;
}

void licenseFunc()
{
	PrintString("MIT License\n\rCopyright(c) 2020 Aidan Ahern\n\rPermission is hereby granted, free of charge, to any person obtaining a copy\n\rof this softwareand associated documentation files(the \"Software\"), to deal\n\rin the Software without restriction, including without limitation the rights\n\rto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n\rcopies of the Software, and to permit persons to whom the Software is\n\rfurnished to do so, subject to the following conditions : \n\rThe above copyright noticeand this permission notice shall be included in all\n\rcopies or substantial portions of the Software.\n\rTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\rIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \n\rFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\n\rAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\rLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \n\rOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\rSOFTWARE.\n\r");
	PrintString("Mammoth thanks to AptRock327#4655 on Discord for much of the CLI code! You rock man!\n\r");
	return;
}

void repositoryFunc()
{
	PrintString("the official github repository: github.com/godofthunder8756/CCOS-2.0\n\r");
	return;
}

void testFunc()
{
	PrintString("testing\n\r");
	return;
}

void PrintMemoryDumpFunc(uint64 address, uint8 rows)
{
	uint8* ptr = (uint8*)address;

	for (uint8 i = 0; i < rows; i++)
	{
		PrintString(HexToString((uint32)(uint64)ptr), FOREGROUND_LIGHTGREEN); PrintString("   ");
		for (uint8 n = 0; n < 16; n++)
		{
			PrintString(HexToString(*ptr)); PrintChar(' '); 
			ptr++; 
		}
		PrintString("\r\n");
	}
}
