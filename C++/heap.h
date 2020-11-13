#pragma once
#include "typedefs.h"
#include "memory.h"

struct MemorySegmentHeader {
	uint64 MemoryLength;
	MemorySegmentHeader* NextSegment;
	MemorySegmentHeader* PreviousSegment;
	MemorySegmentHeader* NextFreeSegment;
	MemorySegmentHeader* PreviousFreeSegment;
	bool Free;
};

struct AlignedMemorySegmentHeader {
	uint64 MemorySegmentHeaderAddress : 63;
	bool IsAligned : 1;
};

extern MemorySegmentHeader* FirstFreeMemorySegment;

void InitializeHeap(uint64 heapAddress, uint64 heapLength);

void* calloc(uint64 size);

void* realloc(void* address, uint64 newSize);

void* malloc(uint64 size);

void* aligned_alloc(uint64 alignment, uint64 size);

void free(void* address);
