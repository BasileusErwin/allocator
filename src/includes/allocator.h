#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "types.h"

typedef struct Block {
  u64 size;
  boolean isFree;
  struct Block *next;
  u64 data[];
} Block;

void printAllocator(void);

void *allocate(u64 size);
void *reallocate(void *address, u64 size);
void *callocate(u64 size, u64 count);
void deallocate(void *address);

#endif
