#include <allocator.h>

int main(void) {
  void *ptr = allocate(8);

  deallocate(ptr);

  void *ptr2 = allocate(33);

  void *ptr3 = allocate(1);

  printAllocator();

  return 0;
}
