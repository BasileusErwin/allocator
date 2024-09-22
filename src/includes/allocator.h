#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "types.h"

typedef enum SearchMode {
  FIRST_FIT,
  NEXT_FIT,
  BEST_FIT,
} SearchMode;

typedef struct Block {
  u64 size;
  boolean isFree;
  struct Block *next;
  u64 data[];
} Block;

typedef struct Allocator {
  Block *head;
  Block *tail;
  Block *searchStart;
  SearchMode searchMode;
} Allocator;

void printDebug(void);

void *allocate(u64 size);
void *reallocate(void *address, u64 size);
void *callocate(u64 size, u64 count);
void deallocate(void *address);
void resetAllocator(void);
void initAllocator(SearchMode searchMode);

#endif
