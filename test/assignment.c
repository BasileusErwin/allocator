#include <stdio.h>
#define ALLOCATOR_TEST_AUXILIARY_FUNCTIONS

#include "assignment.h"
#include <allocator.h>
#include <check.h>

inline u64 alingment(u64 size) { return ALIGN(sizeof(Block) + size); }

// #region First Fit

START_TEST(unit_test_first_fit) {
  resetAllocator();
  void *ptr = allocate(16);
  allocate(16);
  allocate(8);
  allocate(32);

  Block *block = getBlock(ptr);
  void *address = block;

  ck_assert(block->isFree == FALSE);

  deallocate(ptr);

  ck_assert(block->isFree == TRUE);

  block = firstFit(alingment(8));

  ck_assert(block->isFree == FALSE);
  ck_assert(block == address);
}
END_TEST

START_TEST(unit_test_first_fit_2) {
  resetAllocator();
  void *ptr = allocate(32);
  allocate(32);
  allocate(32);

  Block *block = getBlock(ptr);
  void *address = block;

  ck_assert(block->isFree == FALSE);

  deallocate(ptr);

  ck_assert(block->isFree == TRUE);

  block = firstFit(alingment(16));

  ck_assert(block->isFree == FALSE);
  ck_assert(block == address);
}
END_TEST

START_TEST(test_first_fit) {
  initAllocator(FIRST_FIT);
  void *ptr = allocate(16);

  allocate(32);
  allocate(32);

  Block *block = getBlock(ptr);
  void *address = block;

  ck_assert(block->isFree == FALSE);

  deallocate(ptr);

  ck_assert(block->isFree == TRUE);

  ptr = allocate(8);

  block = getBlock(ptr);

  ck_assert(block->isFree == FALSE);
  ck_assert(block == address);
}
END_TEST

// #endregion First Fit

// #region Next Fit

START_TEST(test_next_fit) {
  initAllocator(NEXT_FIT);
  allocate(8);
  allocate(8);
  allocate(8);

  void *o1 = allocate(16);
  void *o2 = allocate(16);

  deallocate(o1);
  deallocate(o2);

  void *ptr = allocate(16);

  Block *block = getBlock(ptr);

  ck_assert(getSearchStart() == block);
}
END_TEST

// #endregion Next Fit

// #region Best Fit

START_TEST(test_best_fit) {
  initAllocator(BEST_FIT);
  allocate(64);
  void *z1 = allocate(16);
  allocate(16);
  void *z2 = allocate(16);

  deallocate(z2);
  deallocate(z1);

  void *z3 = allocate(16);

  printDebug();
  printf("Z3: %p\n", getBlock(z3));
  printf("Z2: %p\n", getBlock(z2));

  ck_assert(getBlock(z3) == getBlock(z2));

  z3 = allocate(16);

  ck_assert(getBlock(z3) == getBlock(z1));
}
END_TEST

// #endregion Best Fit

Suite *assignment_suite(void) {
  Suite *s = suite_create("Assignment");

  TCase *tc_first_fit = tcase_create("First Fit");
  initAllocator(FIRST_FIT);
  tcase_add_test(tc_first_fit, unit_test_first_fit);
  tcase_add_test(tc_first_fit, test_first_fit);
  tcase_add_test(tc_first_fit, unit_test_first_fit_2);

  initAllocator(NEXT_FIT);
  TCase *tc_next_fit = tcase_create("Next Fit");
  tcase_add_test(tc_next_fit, test_next_fit);

  initAllocator(BEST_FIT);
  TCase *tc_best_fit = tcase_create("Best Fit");
  tcase_add_test(tc_best_fit, test_best_fit);

  suite_add_tcase(s, tc_first_fit);
  suite_add_tcase(s, tc_next_fit);
  suite_add_tcase(s, tc_best_fit);

  return s;
}
