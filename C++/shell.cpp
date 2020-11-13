#include "shell.h"

void StartShell()
{
	while (true)
	{
		PrintString("\n\rroot@DESKTOP# ");
		char* command = (char*)malloc(99999);
		getline(command, 9999);
		PrintString("\n\r");
		if (strcmp(command, ver))
			verFunc();
		else if (strcmp(command, help))
			helpFunc();
		else if (strcmp(command, ls))
			lsFunc();
		else if (strcmp(command, install))
			installFunc();
		else if (strcmp(command, license))
			licenseFunc();
		else if (strcmp(command, repository))
			repositoryFunc();
		else if (strcmp(command, test))
			testFunc();
		else if (strcmp(command, "dispmem"))
			PrintMemoryDumpFunc(0x7C00, 10);
		else
		{
			bool echoThingy = echo(command);
			if(echoThingy) { }
			else {
				PrintChar('\'');
				PrintString(command);
				PrintString("' is not recognized as a command or an executable source. Idiot.\n");
			}
		}
	}
	return;
}