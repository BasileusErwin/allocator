#include <allocator.h>
#include <debug.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>

static Allocator allocator = {NULL, NULL};

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
      return block;
    }

    block = block->next;
  }

  return NULL;
}

Block *findFreeBlock(size_t size) { return firstFit(size); }

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
  Block *header = getHeader(ptr);

  if (header->isFree) {
    return;
  }

  header->isFree = TRUE;
}
