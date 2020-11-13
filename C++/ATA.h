#pragma once
#include "typedefs.h"
#include "IO.h"
#include "Heap.h"
#include "Print.h"

struct ATA
{
    uint16 dataPort;
    uint16 errorPort;
    uint16 sectorCountPort;
    uint16 lbaLowPort;
    uint16 lbaMidPort;
    uint16 lbaHighPort;
    uint16 devicePort;
    uint16 commandPort;
    uint16 controlPort;
    uint16 bytePerSector;
    bool master;
};

ATA* InitializeATA(uint16 portBase, bool master);
void ATA_Identify(ATA* ata);
void ATA_Read(ATA* ata, uint32 sector, uint8* data, uint16 count);
void ATA_Write(ATA* ata, uint32 sector, uint8* data, uint16 count);
void ATA_Flush(ATA* ata);