#ifndef ALLOCATOR_DEBUG_H
#define ALLOCATOR_DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allocator.h>
#include <types.h>

string allocatorToString(Allocator *allocator);
void printAllocator(Allocator *allocator);

#endif
