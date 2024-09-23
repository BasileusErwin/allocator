#define ALLOCATOR_TEST_AUXILIARY_FUNCTIONS

#include <stdio.h>
#include <allocator.h>
#include <check.h>
#include <stdlib.h>

static Allocator allocator = {NULL, NULL};

START_TEST(test_allocate_8_bytes) {
  void *ptr = allocate(8);

  ck_assert(ptr != NULL);
}
END_TEST

START_TEST(test_allocate_16_bytes) {
  void *ptr = allocate(16);
  ck_assert(ptr != NULL);
}
END_TEST

START_TEST(test_allocate_32_bytes) {
  void *ptr = allocate(32);
  ck_assert(ptr != NULL);
}
END_TEST

START_TEST(test_allocate_64_bytes) {
  void *ptr = allocate(64);
  ck_assert(ptr != NULL);
}
END_TEST

Suite *allocated_suite(void) {
  Suite *s = suite_create("Allocated");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_allocate_8_bytes);
  tcase_add_test(tc_core, test_allocate_16_bytes);
  tcase_add_test(tc_core, test_allocate_32_bytes);
  tcase_add_test(tc_core, test_allocate_64_bytes);
  suite_add_tcase(s, tc_core);

  return s;
}
