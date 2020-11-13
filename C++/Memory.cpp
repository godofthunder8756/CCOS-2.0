#include "memory.h"
#include "typedefs.h"

void memset(void* start, uint64 value, uint64 num) {

	if (num <= 8) {
		uint8* valPtr = (uint8*)&value;
		for (uint8* ptr = (uint8*)start; ptr < (uint8*)((uint64)start + num); ptr++) {
			*ptr = *valPtr;
			valPtr++;
		}

		return;
	}

	uint64 proceedingBytes = num % 8;
	uint64 newnum = num - proceedingBytes;

	for (uint64* ptr = (uint64*)start; ptr < (uint64*)((uint64)start + newnum); ptr++) {
		*ptr = value;
	}

	uint8* valPtr = (uint8*)&value;
	for (uint8* ptr = (uint8*)((uint64)start + newnum); ptr < (uint8*)((uint64)start + num); ptr++)
	{
		*ptr = *valPtr;
		valPtr++;
	}
}

void memcpy(void* destination, void* source, uint64 num) {
	if (num <= 8) {
		uint8* valPtr = (uint8*)source;
		for (uint8* ptr = (uint8*)destination; ptr < (uint8*)((uint64)destination + num); ptr++) {
			*ptr = *valPtr;
			valPtr++;
		}

		return;
	}

	uint64 proceedingBytes = num % 8;
	uint64 newnum = num - proceedingBytes;
	uint64* srcptr = (uint64*)source;

	for (uint64* destptr = (uint64*)destination; destptr < (uint64*)((uint64)destination + newnum); destptr++) {
		*destptr = *srcptr;
		srcptr++;
	}

	uint8* srcptr8 = (uint8*)((uint64)source + newnum);
	for (uint8* destptr8 = (uint8*)((uint64)destination + newnum); destptr8 < (uint8*)((uint64)destination + num); destptr8++)
	{
		*destptr8 = *srcptr8;
		srcptr8++;
	}

}
