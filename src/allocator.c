#include <allocator.h>
#include <debug.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>

static Allocator allocator = {NULL, NULL};

void initAllocator(SearchMode searchMode) {
  allocator.head = NULL;
  allocator.tail = NULL;
  allocator.searchStart = NULL;
  allocator.searchMode = searchMode;
}

void resetAllocator(void) {
  if (allocator.head != NULL) {
    return;
  }

  // Rollback the brk pointer to the beginning of the heap
  if (brk(allocator.head) == -1) {
    panic("%s\n", "Out of memory");
  }

  allocator.head = NULL;
  allocator.tail = NULL;
  allocator.searchStart = NULL;
}

void printDebug(void) { printAllocator(&allocator); }

u64 align(u64 size) {
  return (size + (sizeof(Block *) - 1)) & ~(sizeof(Block *) - 1);
}

Block *getHeader(void *ptr) {
  if (ptr == NULL) {
    return NULL;
  }

  return ((Block *) ptr) - 1;
}

Block *requestBlock(size_t size) {
  Block *block = (Block *) sbrk(0);

  if (sbrk(size) == (void *) -1) {
    panic("%s\n", "Out of memory");
  }

  block->size = size;
  block->isFree = FALSE;
  block->next = NULL;

  return block;
}

Block *firstFit(size_t size) {
  Block *block = allocator.head;

  while (block != NULL) {
    if (block->isFree == TRUE && block->size >= size) {
      block->isFree = FALSE;
      allocator.searchStart = block;
      return block;
    }

    block = block->next;
  }

  return NULL;
}

Block *nextFit(u64 size) {
  Block *block = allocator.searchStart;

  while (block != NULL) {
    if (block->isFree == TRUE && block->size >= size) {
      block->isFree = FALSE;
      allocator.searchStart = block->next;
      return block;
    }

    block = block->next;
  }

  block = allocator.head;
  while (block != allocator.searchStart) {
    if (block->isFree == TRUE && block->size >= size) {
      block->isFree = FALSE;
      allocator.searchStart = block->next;
      return block;
    }

    block = block->next;
  }

  return NULL;
}

Block *bestFit(u64 size) {
  Block *block = allocator.searchStart;
  u64 bestSize = 0;

  while (block != NULL) {
    if (block->isFree == TRUE && block->size >= size &&
        (bestSize == 0 || block->size < bestSize)) {
      bestSize = block->size;
      allocator.searchStart = block;
    }

    if (block->isFree == TRUE && block->size == bestSize) {
      block = block->next;
    }

    block = block->next;
  }

  if (bestSize == 0) {
    return NULL;
  }

  block = allocator.searchStart;

  while (block != NULL) {
    if (block->isFree == TRUE && block->size >= size) {
      block->isFree = FALSE;
      allocator.searchStart = block->next;
      return block;
    }

    block = block->next;
  }

  return NULL;
}

Block *findFreeBlock(size_t size) {
  Block *block = nextFit(size);

  if (block != NULL) {
    return block;
  }

  return bestFit(size);
}

void *allocate(u64 size) {
  size_t total_size = sizeof(Block) + size;
  size = align(total_size);
  Block *block = findFreeBlock(size);

  if (block != NULL) {
    return block->data;
  }

  block = requestBlock(size);

  block->size = size;
  block->isFree = FALSE;
  block->next = NULL;

  if (allocator.head == NULL) {
    allocator.head = block;
  }

  if (allocator.tail != NULL) {
    allocator.tail->next = block;
  }

  allocator.tail = block;

  return block->data;
}

void deallocate(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  Block *header = getHeader(ptr);

  if (header == NULL || header->isFree == TRUE) {
    return;
  }

  header->isFree = TRUE;
}
