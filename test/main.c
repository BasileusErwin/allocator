#define ALLOCATOR_TEST_AUXILIARY_FUNCTIONS

#include <allocator.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "alingment.h"
#include "allocate.h"
#include "deallocate.h"
#include "assignment.h"

static Allocator allocator = {NULL, NULL};

int main(void) {
  int number_failed = 0;
  Suite *s = NULL;
  SRunner *sr = NULL;
  resetAllocator();

  s = alingment_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  resetAllocator();

  s = allocated_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  resetAllocator();

  s = deallocate_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  resetAllocator();

  s = assignment_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
