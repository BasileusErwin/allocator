#define ALLOCATOR_TEST_AUXILIARY_FUNCTIONS

#include <check.h>
#include "../src/includes/allocator.h"
#include "deallocate.h"

START_TEST(test_deallocate) {
  void *ptr = allocate(12);

  ck_assert(ptr != NULL);

  Block *block = getBlock(ptr);

  ck_assert(block->isFree == FALSE);

  deallocate(ptr);

  block = getBlock(ptr);

  ck_assert(block->isFree == TRUE);
}
END_TEST

START_TEST(test_deallocate_with_freed_block) {
  void *ptr = allocate(12);
  Block *block = getBlock(ptr);
  block->isFree = TRUE;

  deallocate(ptr);

  block = getBlock(ptr);

  ck_assert(block->isFree == TRUE);
}
END_TEST

Suite *deallocate_suite(void) {
  Suite *s = suite_create("Deallocate");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_deallocate);
  tcase_add_test(tc_core, test_deallocate_with_freed_block);
  suite_add_tcase(s, tc_core);

  return s;
}
