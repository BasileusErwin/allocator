#include <debug.h>
#include <stdio.h>

string allocatorToString(Allocator *allocator) {
  string result = malloc(sizeof(char) * 100);

  sprintf(
      result,
      "Allocator: head: %p, tail: %p",
      (void *) allocator->tail,
      (void *) allocator->head
  );

  return result;
}

void printAllocator(Allocator *allocator) {
  string allocatorString = allocatorToString(allocator);
  u32 allocatorStringLength = strlen(allocatorString);

  // Print the allocator string with a border
  // Repite el border horizontalmente hasta que cubra el largo del string
  printf("┌");
  for (u32 i = 0; i < allocatorStringLength + 2; i++) {
    printf("─");
  }
  printf("┐\n");

  printf("│ %s │\n", allocatorString);
  printf("└");
  for (u32 i = 0; i < allocatorStringLength + 2; i++) {
    printf("─");
  }
  printf("┘\n");

  Block *block = allocator->head;

  u32 i = 0;
  while (block != NULL) {
    printf(
        "Block #%d - Size: %lu bytes - Start: %p End: %p\n",
        i,
        block->size,
        (void *) block,
        (void *) ((char *) block + sizeof(Block) + block->size)
    );
    printf("\tIs Free: %s\n", block->isFree == TRUE ? "true" : "false");
    printf("\tNext: %p\n", (void *) block->next);
    printf("\tData: %p\n", (void *) block->data);

    block = block->next;
    i++;
    printf("\n");
  }

  free(allocatorString);
}
