#ifndef TEST_H_
#define TEST_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../brick_game/tetris/game_logic.h"

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10

#define FIGURE_HEIGHT 4

typedef struct {
  int fails;
} fail;

void run_tests(fail *fails);
void run_testcase(Suite *testcase, fail *fails);

Suite *suite_tetris_test(void);

#endif
