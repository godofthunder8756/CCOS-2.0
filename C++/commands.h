#pragma once
#include "Print.h"
#include "typedefs.h"

extern char ver[];
extern char help[];
extern char ls[];
extern char install[];
extern char license[];
extern char repository[];
extern char test[];
extern char PrintMemoryDump[]; 

void verFunc();

void helpFunc();

bool echo(char* commandboi);

void lsFunc();

void installFunc();

void licenseFunc();

void repositoryFunc();

void testFunc();

void PrintMemoryDumpFunc(uint64 address, uint8 rows); 