#include "Heap.h"

MemorySegmentHeader* FirstFreeMemorySegment;

void InitializeHeap(uint_64 headpAddress, uint_64 heapLength) {
	FirstFreeMemorySegment = (MemorySegmentHeader*)headpAddress;
	FirstFreeMemorySegment->MemoryLength = heapLength - (sizeof(MemorySegmentHeader));
	FirstFreeMemorySegment->NextSegment = 0;
	FirstFreeMemorySegment->PreviousSegment = 0;
	FirstFreeMemorySegment->NextFreeSegment = 0;
	FirstFreeMemorySegment->PreviousFreeSegment = 0;
	FirstFreeMemorySegment->Free = true;
}

void* malloc(uint_64 size) {
	uint_64 remainder = size % 8;
	size -= remainder;
	if (remainder != 0) size += 8;

	MemorySegmentHeader* currentMemorySegment = FirstFreeMemorySegment;

	while (true) {
		if (currentMemorySegment->MemoryLength >= size) {

			if (currentMemorySegment->MemoryLength > size + sizeof(MemorySegmentHeader)) {
				MemorySegmentHeader* newSegmentHeader = (MemorySegmentHeader*)((uint_64)currentMemorySegment + sizeof(MemorySegmentHeader) + size);

				newSegmentHeader->Free = true;
				newSegmentHeader->MemoryLength = ((uint_64)currentMemorySegment->MemoryLength) - sizeof(MemorySegmentHeader) + size;
				newSegmentHeader->NextFreeSegment = currentMemorySegment->NextFreeSegment;
				newSegmentHeader->NextSegment = currentMemorySegment->NextSegment;
				newSegmentHeader->PreviousSegment = currentMemorySegment;
				newSegmentHeader->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;

				currentMemorySegment->NextFreeSegment = newSegmentHeader;
				currentMemorySegment->NextSegment = newSegmentHeader;
				currentMemorySegment->MemoryLength = size;

			}
			if (currentMemorySegment == FirstFreeMemorySegment) {
				FirstFreeMemorySegment = currentMemorySegment->NextFreeSegment;
			}
			currentMemorySegment->Free = false;

			if (currentMemorySegment->PreviousFreeSegment != 0) currentMemorySegment->PreviousFreeSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
			if (currentMemorySegment->NextFreeSegment != 0) currentMemorySegment->NextFreeSegment->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;
			if (currentMemorySegment->PreviousSegment != 0) currentMemorySegment->PreviousSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
			if (currentMemorySegment->NextSegment != 0) currentMemorySegment->NextSegment->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;

			return currentMemorySegment + 1;
		}
		if (currentMemorySegment->NextFreeSegment == 0) {
			return 0; // No memory remaining
		}
		currentMemorySegment = currentMemorySegment->NextFreeSegment;
	}
	return 0;
}
