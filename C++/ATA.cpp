#include "ATA.h"

ATA* InitializeATA(uint16 portBase, bool master)
{
	ATA* ata = (ATA*)calloc(sizeof(ATA));

	ata->dataPort = portBase;
	ata->errorPort = portBase + 1;
	ata->sectorCountPort = portBase + 2;
	ata->lbaLowPort = portBase + 3;
	ata->lbaMidPort = portBase + 4;
	ata->lbaHighPort = portBase + 5;
	ata->devicePort = portBase + 6;
	ata->commandPort = portBase + 7;
	ata->controlPort = portBase + 0x206;
	ata->bytePerSector = 512;
	ata->master = master;

	return ata;
}

void ATA_Identify(ATA* ata)
{
	outb(ata->devicePort, ata->master ? 0xa0 : 0xb0);	
	outb(ata->controlPort, 0x00);

	outb(ata->devicePort, 0xa0);
	uint8 status = inb(ata->commandPort);

	if (status == 0xFF)	
		return;

	outb(ata->devicePort, ata->master ? 0xa0 : 0xb0);
	outb(ata->sectorCountPort, 0x00);
	outb(ata->lbaLowPort, 0x00);
	outb(ata->lbaMidPort, 0x00);
	outb(ata->lbaHighPort, 0x00);
	outb(ata->commandPort, 0xec);

	status = inb(ata->commandPort);
	if (status == 0x00)
	{
		PrintString("No drive found.");
		return;
	}

	while ((status & 0x80) == 0x80 && (status & 0x01) != 0x01)
		status = inb(ata->commandPort);

	if (status & 0x01)
	{
		PrintString("Error.", FOREGROUND_LIGHTRED);
		return;
	}

	for (uint16 i = 0; i < 256; i++)
	{
		uint16 data = inw(ata->dataPort);
	}
	PrintString("Success.", FOREGROUND_LIGHTGREEN);
}

void ATA_Read(ATA* ata, uint32 sector, uint8* data, uint16 count)
{
	if (sector & 0xf0000000)
		return;

	outb(ata->devicePort, (ata->master ? 0xe0 : 0xf0) | (sector & 0x0f00000) >> 24);
	outb(ata->errorPort, 0);
	outb(ata->sectorCountPort, 1);

	outb(ata->lbaLowPort, sector & 0x000000ff);
	outb(ata->lbaMidPort, (sector & 0x0000ff00) >> 8);
	outb(ata->lbaHighPort, (sector & 0x00ff0000) >> 16);
	outb(ata->commandPort, 0x20);

	uint8 status = inb(ata->commandPort);
	while ((status & 0x80) == 0x80 && (status & 0x01) != 0x01)
		status = inb(ata->commandPort);

	//PrintString("Reading from ATA...", FOREGROUND_LIGHTGREEN);
	//PrintString("\r\n");

	if (status & 0x01)
	{
		PrintString("Error.", FOREGROUND_LIGHTRED);
		return;
	}

	for (uint16 i = 0; i < count; i += 2)
	{
		uint16 rdata = inw(ata->dataPort);

		data[i] = rdata & 0x00ff;
		if (i + 1 < count)
			data[i + 1] = (rdata >> 8) & 0x00ff;
	}

	for (uint16 i = count + (count % 2); i < 512; i += 2)
	{
		inw(ata->dataPort);
	}
	//PrintString("Success.", FOREGROUND_LIGHTGREEN);
}

void ATA_Write(ATA* ata, uint32 sector, uint8* data, uint16 count)
{
	if (sector & 0xf0000000)
		return;

	if (count > 512)
		return;

	outb(ata->devicePort, (ata->master ? 0xe0 : 0xf0) | (sector & 0x0f00000) >> 24);
	outb(ata->errorPort, 0);
	outb(ata->sectorCountPort, 1);

	outb(ata->lbaLowPort, sector & 0x000000ff);
	outb(ata->lbaMidPort, (sector & 0x0000ff00) >> 8);
	outb(ata->lbaHighPort, (sector & 0x00ff0000) >> 16);
	outb(ata->commandPort, 0x30);

	//PrintString("Writing to ATA...", FOREGROUND_LIGHTBLUE);
	//PrintString("\r\n");

	for (uint16 i = 0; i < count; i += 2)
	{
		uint16 wdata = data[i];
		if (i + 1 < count)
			wdata |= ((uint16)data[i + 1]) << 8;

		outw(ata->dataPort, wdata);
	}

	for (uint16 i = count + (count % 2); i < 512; i += 2)
	{
		outw(ata->dataPort, 0x0000);
	}
	//PrintString("Success.", FOREGROUND_LIGHTGREEN);
}

void ATA_Flush(ATA* ata)
{
	outb(ata->devicePort, ata->master ? 0xe0 : 0xf0);
	outb(ata->commandPort, 0xe7);

	uint8 status = inb(ata->commandPort);
	while ((status & 0x80) == 0x80 && (status & 0x01) != 0x01)
		status = inb(ata->commandPort);

	if (status & 0x01)
	{
		PrintString("Error.", FOREGROUND_LIGHTRED);
		return;
	}
}