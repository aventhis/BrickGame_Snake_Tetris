#include "test.h"

void run_tests(fail *fails) {
  Suite *list_cases[] = {suite_tetris_test(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, fails);
  }
}

void run_testcase(Suite *testcase, fail *fails) {
  int failed = 0;
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  fails->fails += failed;
  srunner_free(sr);
  if (!failed) {
    printf("========= \033[32mPASSED\033[0m =========\n");
  } else {
    printf("========= \033[31mFAILED: %d\033[0m =========\n", failed);
  }
}

int main(void) {
  fail fails;
  fails.fails = 0;
  run_tests(&fails);
  printf("\n\n");
  if (!fails.fails) {
    printf("============ \033[32mALL PASSED\033[0m ============\n");
  } else {
    printf("============ \033[31mALL FAILED: %d\033[0m ============\n",
           fails.fails);
  }
  return 0;
}
