#include <allocator.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>

static Block *FIRST_BLOCK = NULL;
static Block *LAST_BLOCK = NULL;

u64 align(u64 size) {
  return (size + (sizeof(Block *) - 1)) & ~(sizeof(Block *) - 1);
}

void printAllocator(void) {
  printf("=========================\n");
  printf("Start: %p End: %p\n", (void *) FIRST_BLOCK, (void *) LAST_BLOCK);
  printf("=========================\n");

  Block *block = FIRST_BLOCK;

  u32 i = 0;
  while (block != NULL) {
    printf(
        "Block #%d - Start: %p End: %p\n",
        i,
        (void *) block,
        (void *) ((char *) block + sizeof(Block) + block->size)
    );
    printf("\tSize: %lu\n", block->size);
    printf("\tIs Free: %s\n", block->isFree == TRUE ? "true" : "false");
    printf("\tNext: %p\n", (void *) block->next);
    printf("\tData: %p\n", (void *) block->data);

    block = block->next;
    i++;
  }
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
  Block *block = FIRST_BLOCK;

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

  if (FIRST_BLOCK == NULL) {
    FIRST_BLOCK = block;
  }

  if (LAST_BLOCK != NULL) {
    LAST_BLOCK->next = block;
  }

  LAST_BLOCK = block;

  return block->data;
}

void deallocate(void *ptr) {
  Block *header = getHeader(ptr);

  if (header->isFree) {
    return;
  }

  header->isFree = TRUE;
}
