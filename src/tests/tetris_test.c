#include "test.h"

START_TEST(test_initialize_game) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);  // Устанавливаем начальные значения

  // Проверяем, что массивы не NULL и инициализированы нулями
  ck_assert_ptr_nonnull(game.field);
  ck_assert_ptr_nonnull(game.next);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(game.field[i][j], 0);
    }
  }
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      ck_assert_int_eq(game.next[i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_select_and_place_figure) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);  // Устанавливаем начальные значения игры

  int figure_index = select_next_figure(&game);  // Выбираем следующую фигуру
  add_next_figure(&game);  // Добавляем фигуру на игровое поле

  // Убеждаемся, что индекс фигуры находится в пределах допустимого диапазона
  ck_assert_int_ge(figure_index, 0);
  ck_assert_int_lt(figure_index, NUM_FIGURES);

  // Проверяем, что фигура была размещена на поле
  int placed = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (game.field[i][j] == 1) {
        placed = 1;
        break;
      }
    }
    if (placed) break;
  }
  ck_assert_int_eq(
      placed,
      1);  // Подтверждаем, что хотя бы один блок фигуры размещён на поле
}
END_TEST

START_TEST(test_game_over) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  // Manually set the field to simulate a full top row
  for (int j = 0; j < FIELD_WIDTH; j++) {
    game.field[0][j] = 2;  // Assuming 2 represents a fixed block
  }

  int gameover = check_gameover(&game);
  ck_assert_int_eq(gameover, 1);
}
END_TEST

START_TEST(test_score_update) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);

  // Simulate a full line at the bottom
  for (int j = 0; j < FIELD_WIDTH; j++) {
    game.field[FIELD_HEIGHT - 1][j] = 1;
  }

  check_and_remove_full_lines(&game);
  ck_assert_int_gt(game.score, 0);  // Ensure score is incremented
}
END_TEST

START_TEST(test_initialization) {
  GameInfo_t game;
  initialize_game(&game);
  ck_assert_ptr_nonnull(game.field);
  ck_assert_ptr_nonnull(game.next);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(game.field[i][j], 0);  // Should be initialized to 0
    }
  }
}
END_TEST

START_TEST(test_figure_rotation) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);

  // Явное задание фигуры, которая изменяется при повороте, например фигура "I"
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    memcpy(game.next[i], figures[1][i], FIGURE_WIDTH * sizeof(int));
  }
  add_next_figure(&game);  // Добавляем фигуру на поле

  // Сохраняем состояние игрового поля до поворота
  int **before_rotation = (int **)calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    before_rotation[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
    for (int j = 0; j < FIELD_WIDTH; j++) {
      before_rotation[i][j] = game.field[i][j];
    }
  }

  // Выполняем поворот фигуры
  rotate_figure(&game);

  // Проверяем, изменилось ли поле после поворота
  int changed = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (before_rotation[i][j] != game.field[i][j]) {
        changed = 1;
        break;
      }
    }
    if (changed) break;
  }
  ck_assert_int_eq(changed, 1);  // Ожидаем, что поле изменилось после поворота

  // Освобождаем ресурсы
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(before_rotation[i]);
  }
  free(before_rotation);
}
END_TEST

START_TEST(test_free_2d_array) {
  int **array = NULL;
  allocate_2d_array(&array, 2, 2);
  ck_assert_ptr_nonnull(array);
  free_2d_array(&array, 2);
  ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_allocate_2d_array_failure) {
  int **array = NULL;
  // Имитация неудачного выделения памяти
  ck_assert_int_eq(allocate_2d_array(&array, 0, 0), 1);
  ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_can_move_left) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  select_next_figure(&game);
  add_next_figure(&game);

  // Поместим фигуру в левый край, чтобы проверить, можно ли двигаться влево
  while (can_move_left(&game)) {
    update_figure_position(&game, -1, 0);
  }

  // Должен вернуть false, когда фигура достигла левого края
  ck_assert_int_eq(can_move_left(&game), 0);
}
END_TEST

START_TEST(test_can_move_down) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  select_next_figure(&game);
  add_next_figure(&game);

  // Должен вернуть true, пока фигура не достигнет низа поля
  while (can_move_down(&game)) {
    update_figure_position(&game, 0, 1);
  }

  // Проверка на достижение нижней границы
  ck_assert_int_eq(can_move_down(&game), 0);
}
END_TEST

START_TEST(test_handle_down_action) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  select_next_figure(&game);
  add_next_figure(&game);

  // Активация быстрого падения фигуры
  handle_down_action(&game, true);

  // Проверка, достигла ли фигура дна
  ck_assert_int_eq(can_move_down(&game), 0);
}
END_TEST

START_TEST(test_fix_figure) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  select_next_figure(&game);
  add_next_figure(&game);

  // Сначала фигура добавляется на поле
  fix_figure(&game);

  // Проверяем, что каждая часть фигуры теперь имеет статус 2 (зафиксирована)
  FigurePosition_t *figure = current_figure_position();
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(game.field[figure->y[i]][figure->x[i]], 2);
  }

  // Проверяем удаление полных линий, если таковые имеются
  check_and_remove_full_lines(&game);
  int line_full = 1;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    if (game.field[FIELD_HEIGHT - 1][i] != 2) {
      line_full = 0;
      break;
    }
  }
  ck_assert_int_eq(line_full, 0);
}
END_TEST

START_TEST(test_can_move_right) {
  GameInfo_t game;
  initialize_game(&game);
  initialize_game_start(&game);
  select_next_figure(&game);
  add_next_figure(&game);

  // Двигаем фигуру вправо до конца
  while (can_move_right(&game)) {
    update_figure_position(&game, 1, 0);
  }

  // Должны достигнуть крайнего правого положения
  ck_assert_int_eq(can_move_right(&game), 0);
}
END_TEST

START_TEST(test_get_score_and_level) {
  GameInfo_t *game = game_info();
  initialize_game(game);
  initialize_game_start(game);
  ck_assert_int_eq(getScore(), 0);
  ck_assert_int_eq(getLevel(), 1);
}
END_TEST

START_TEST(test_user_input_basic) {
  GameInfo_t *game = game_info();
  initialize_game(game);
  initialize_game_start(game);
  select_next_figure(game);  // Очистка игрового состояния
  add_next_figure(game);
  select_next_figure(game);
  // Вызываем userInput с разными параметрами, не проверяя изменения, а только
  // корректность выполнения
  userInput(Down, true);
  userInput(Left, true);
  userInput(Right, true);
  if (!can_move_down(game)) fix_figure(game);
  // В тесте ниже нет проверок assert, потому что мы проверяем лишь отсутствие
  // ошибок при вызове Это не идеальный тест, он лишь демонстрирует вызов
  // функции без сбоев
}
END_TEST

Suite *suite_tetris_test(void) {
  Suite *s = suite_create("\033[45m-=tetris_test=-\033[0m");
  TCase *tc = tcase_create("case_tetris");

  tcase_add_test(tc, test_initialize_game);
  tcase_add_test(tc, test_select_and_place_figure);
  tcase_add_test(tc, test_game_over);
  tcase_add_test(tc, test_score_update);
  tcase_add_test(tc, test_initialization);
  tcase_add_test(tc, test_figure_rotation);
  tcase_add_test(tc, test_free_2d_array);
  tcase_add_test(tc, test_allocate_2d_array_failure);
  tcase_add_test(tc, test_can_move_left);
  tcase_add_test(tc, test_can_move_down);
  tcase_add_test(tc, test_handle_down_action);
  tcase_add_test(tc, test_fix_figure);
  tcase_add_test(tc, test_can_move_right);
  tcase_add_test(tc, test_get_score_and_level);
  tcase_add_test(tc, test_user_input_basic);
  suite_add_tcase(s, tc);
  return s;
}