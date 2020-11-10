#pragma once
#include "Typedefs.h"

struct MemorySegmentHeader {
	uint_64 MemoryLength;
	MemorySegmentHeader* NextSegment;
	MemorySegmentHeader* PreviousSegment;
	MemorySegmentHeader* NextFreeSegment;
	MemorySegmentHeader* PreviousFreeSegment;
	bool Free;
};

extern void InitializeHeap(uint_64 headpAddress, uint_64 heapLength);

extern void* malloc(uint_64 size);