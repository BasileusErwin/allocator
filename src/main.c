#include <allocator.h>

int main(void) {
  void *ptr = allocate(8);

  deallocate(ptr);

  void *ptr2 = allocate(33);

  void *ptr3 = allocate(16);
  allocate(16);
  allocate(32);
  allocate(15);
  allocate(34);

  deallocate(ptr3);

  allocate(6);

  printDebug();

  return 0;
}
