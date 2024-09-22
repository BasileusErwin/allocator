#include <allocator.h>

int main(void) {
  void *ptr = allocate(8);

  void *ptr2 = allocate(33);

  void *ptr3 = allocate(1);

  printDebug();

  return 0;
}
