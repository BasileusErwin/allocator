#define ALLOCATOR_TEST_AUXILIARY_FUNCTIONS
#include <allocator.h>
#include <check.h>

START_TEST(test_allocate_alingment) {
  u64 value = ALIGN(8);

  ck_assert(value == 8);
}
END_TEST

START_TEST(test_allocate_alingment_6_bytes) {
  u64 value = ALIGN(6);

  ck_assert(value == 8);
}
END_TEST

START_TEST(test_allocate_alingment_with_block) {
  u64 blockSize = sizeof(Block);
  ck_assert(blockSize == 24);

  u64 value = ALIGN(blockSize + 8);

  ck_assert(value == 32);
}
END_TEST

START_TEST(test_allocate_alingment_with_block_2) {
  u64 blockSize = sizeof(Block);
  ck_assert(blockSize == 24);

  u64 value = ALIGN(blockSize + 8 + 8);

  ck_assert(value == 40);
}
END_TEST

Suite *alingment_suite(void) {
  Suite *s = suite_create("Alignment");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_allocate_alingment);
  tcase_add_test(tc_core, test_allocate_alingment_6_bytes);
  tcase_add_test(tc_core, test_allocate_alingment_with_block);
  tcase_add_test(tc_core, test_allocate_alingment_with_block_2);
  suite_add_tcase(s, tc_core);

  return s;
}
