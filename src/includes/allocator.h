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

#define ALIGN(size) (size + (sizeof(Block *) - 1)) & ~(sizeof(Block *) - 1);

void printDebug(void);

void *allocate(u64 size);
void *reallocate(void *address, u64 size);
void *callocate(u64 size, u64 count);
void deallocate(void *address);
void resetAllocator(void);
void initAllocator(SearchMode searchMode);

#ifdef ALLOCATOR_TEST_AUXILIARY_FUNCTIONS
Block *getBlock(void *ptr);
Block *firstFit(u64 size);
Block *nextFit(u64 size);
Block *bestFit(u64 size);
Block *findFreeBlock(u64 size);
Block *getSearchStart(void);
#endif

#endif
