#include "game_logic.h"

/********************************************************************************
 * Основные структуры и переменные
 ********************************************************************************/

FigurePosition_t *current_figure_position() {
  static FigurePosition_t currentFigure = {0};
  return &currentFigure;
}

static int points_to_next_level;

int figures[NUM_FIGURES][FIGURE_HEIGHT][FIGURE_WIDTH] = {
    // O-Фигура
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // I-Фигура
    {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
    // T-Фигура
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // S-Фигура
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // Z-Фигура
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // J-Фигура
    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
    // L-Фигура
    {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

GameInfo_t *game_info() {
  static GameInfo_t game = {0};

  return &game;
}
/********************************************************************************
 * Инициализация игры и базовые операции
 ********************************************************************************/

void initialize_game(GameInfo_t *game) {
  game->field = NULL;
  game->next = NULL;

  if (allocate_2d_array(&game->field, FIELD_HEIGHT, FIELD_WIDTH) ||
      allocate_2d_array(&game->next, FIGURE_HEIGHT, FIGURE_WIDTH)) {
    fprintf(stderr, "Failed to allocate memory for the game.\n");
    exit(EXIT_FAILURE);
  }

  clear_game_board(game);  // Clear the game board
  clear_next_figure(game);
  game->high_score = load_high_score();
  game->score = 0;

  game->level = 1;
  game->speed = 1;
  game->pause = 0;
}

void initialize_game_start(GameInfo_t *game) {
  game->high_score = load_high_score();
  game->score = 0;

  game->level = 1;
  game->speed = 1;
  game->pause = 0;
  clear_game_board(game);
  clear_next_figure(game);
  initialize_points_to_next_level();
  select_next_figure(game);
}

void clear_game_board(GameInfo_t *game) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game->field[i][j] = 0;
    }
  }
}

void clear_next_figure(GameInfo_t *game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = 0;
    }
  }
}

void initialize_points_to_next_level() { points_to_next_level = 600; }

/********************************************************************************
 * Управление памятью
 ********************************************************************************/

int allocate_2d_array(int ***array, int rows, int cols) {
  if (rows == 0 || cols == 0) {
    *array = NULL;
    return 1;
  }

  int success = 0;
  *array = (int **)calloc(rows, sizeof(int *));
  if (*array == NULL) {
    success = 1;
  } else {
    for (int i = 0; i < rows && success == 0; i++) {
      (*array)[i] = (int *)calloc(cols, sizeof(int));
      if ((*array)[i] == NULL) {
        free_2d_array(array, i);
        success = 1;
      }
    }
  }

  if (success == 1) {
    *array = NULL;
  }

  return success;
}

void free_2d_array(int ***array, int rows) {
  if (array == NULL || *array == NULL) return;
  for (int i = 0; i < rows; i++) {
    free((*array)[i]);
    (*array)[i] = NULL;
  }
  free(*array);
  *array = NULL;
}

/********************************************************************************
 * Управление фигурами
 ********************************************************************************/

// Функция для выбора следующей фигуры
int select_next_figure(GameInfo_t *game) {
#if defined(__linux__)
  srand(time(NULL));  // Для Linux
  int fig_index = rand() % 7;
#elif defined(__APPLE__)
  srandom(time(NULL));  // Для MacOS
  int fig_index = random() % 7;
#endif

  // Копирование выбранной фигуры в массив `next`
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      game->next[i][j] = figures[fig_index][i][j];
    }
  }

  return fig_index;
}

void add_next_figure(GameInfo_t *game) {
  FigurePosition_t *figure_pos = current_figure_position();
  int n = 0;
  int start_col = (FIELD_WIDTH / 2) -
                  (FIGURE_WIDTH / 2);  // Центрирование фигуры по горизонтали
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      if (game->next[i][j] == 1) {
        figure_pos->y[n] = i;
        figure_pos->x[n] = start_col + j;
        game->field[i][start_col + j] = 1;
        n++;
      }
    }
  }
  clear_next_figure(game);
  select_next_figure(game);
}

int is_square_figure(FigurePosition_t *figure) {
  return (figure->x[0] == figure->x[1] && figure->x[2] == figure->x[3] &&
          figure->y[0] == figure->y[2] && figure->y[1] == figure->y[3]);
}

void update_figure_position(GameInfo_t *game, int dx, int dy) {
  FigurePosition_t *figure = current_figure_position();

  for (int i = 0; i < 4; i++) {
    game->field[figure->y[i]][figure->x[i]] = 0;
  }
  for (int i = 0; i < 4; i++) {
    figure->x[i] += dx;
    figure->y[i] += dy;
  }

  // Записываем фигуру обратно на поле в новом положении
  for (int i = 0; i < 4; i++) {
    game->field[figure->y[i]][figure->x[i]] = 1;
  }
}

void fix_figure(GameInfo_t *game) {
  FigurePosition_t *figure = current_figure_position();
  for (int i = 0; i < 4; i++) {
    game->field[figure->y[i]][figure->x[i]] = 2;
  }

  check_and_remove_full_lines(game);
}

void check_and_remove_full_lines(GameInfo_t *game) {
  int count = 0;
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    bool full_line = true;

    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] != 1 && game->field[i][j] != 2) {
        full_line = false;
        break;
      }
    }

    if (full_line) {
      count++;
      // Сдвигаем все линии выше текущей вниз на одну строку
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
          game->field[k][j] = game->field[k - 1][j];
        }
      }
      // Очистка верхней линии
      for (int j = 0; j < FIELD_WIDTH; j++) {
        game->field[0][j] = 0;
      }
      i++;
    }
  }
  update_score(game, count);
}

/********************************************************************************
 * Логика движения и взаимодействия
 ********************************************************************************/

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *gameInfo = game_info();

  switch (action) {
    case Left:
      if (can_move_left(gameInfo)) {
        update_figure_position(gameInfo, -1, 0);
      }
      break;
    case Right:
      if (can_move_right(gameInfo)) {
        update_figure_position(gameInfo, 1, 0);
      }
      break;
    case Down:
      handle_down_action(gameInfo, hold);
      break;
    default:
      if (can_move_down(gameInfo)) {
        update_figure_position(gameInfo, 0, 1);
      }
      break;
  }
}

void handle_down_action(GameInfo_t *gameInfo, bool hold) {
  if (hold) {
    while (can_move_down(gameInfo)) {
      update_figure_position(gameInfo, 0, 1);
      struct timespec req = {0, 5000000};
      nanosleep(&req, NULL);
    }
  } else {
    struct timespec req = {0, 500000000};
    nanosleep(&req, NULL);
    if (can_move_down(gameInfo)) {
      update_figure_position(gameInfo, 0, 1);
    }
  }
}

bool check_boundaries(int *newPositionsX, int *newPositionsY) {
  bool within_bounds = true;
  for (int i = 0; i < 4; i++) {
    if (newPositionsX[i] < 0 || newPositionsX[i] >= FIELD_WIDTH ||
        newPositionsY[i] >= FIELD_HEIGHT) {
      within_bounds = false;
      break;
    }
  }
  return within_bounds;
}

bool check_collisions(GameInfo_t *game, int *newPositionsX, int *newPositionsY,
                      FigurePosition_t *figure) {
  bool collision_free = true;
  for (int i = 0; i < 4 && collision_free; i++) {
    if (game->field[newPositionsY[i]][newPositionsX[i]] != 0) {
      bool isPartOfFigure = false;
      for (int j = 0; j < 4; j++) {
        if (i != j && newPositionsY[i] == figure->y[j] &&
            newPositionsX[i] == figure->x[j]) {
          isPartOfFigure = true;
          break;
        }
      }
      if (!isPartOfFigure) {
        collision_free = false;
      }
    }
  }
  return collision_free;
}

bool can_move(GameInfo_t *game, int dx, int dy) {
  FigurePosition_t *figure = current_figure_position();
  int newPositionsY[4];
  int newPositionsX[4];

  for (int i = 0; i < 4; i++) {
    newPositionsX[i] = figure->x[i] + dx;
    newPositionsY[i] = figure->y[i] + dy;
  }

  return check_boundaries(newPositionsX, newPositionsY) &&
         check_collisions(game, newPositionsX, newPositionsY, figure);
}

bool can_move_left(GameInfo_t *game) { return can_move(game, -1, 0); }

bool can_move_right(GameInfo_t *game) { return can_move(game, 1, 0); }

bool can_move_down(GameInfo_t *game) { return can_move(game, 0, 1); }

void rotate_figure(GameInfo_t *game) {
  FigurePosition_t *figure = current_figure_position();

  if (is_square_figure(figure)) {
    return;
  }

  FigurePosition_t temp_fig = *figure;
  int centerX = figure->x[1];
  int centerY = figure->y[1];

  perform_rotation(figure, &temp_fig, centerX, centerY);

  // Проверяем столкновение с границами и другими фигурами
  if (can_rotate_figure(game, &temp_fig)) {
    apply_rotation(game, figure, &temp_fig);
  }
}

void perform_rotation(FigurePosition_t *figure, FigurePosition_t *temp_fig,
                      int centerX, int centerY) {
  for (int i = 0; i < 4; i++) {
    int x = figure->x[i] - centerX;
    int y = figure->y[i] - centerY;

    temp_fig->x[i] = centerX - y;
    temp_fig->y[i] = centerY + x;
  }
}

bool can_rotate_figure(GameInfo_t *game, FigurePosition_t *temp_fig) {
  bool can_rotate = true;
  for (int i = 0; i < 4; i++) {
    if (temp_fig->x[i] < 0 || temp_fig->x[i] >= FIELD_WIDTH ||
        temp_fig->y[i] >= FIELD_HEIGHT || temp_fig->y[i] < 0 ||
        (temp_fig->y[i] >= 0 &&
         game->field[temp_fig->y[i]][temp_fig->x[i]] == 2)) {
      can_rotate = false;
      break;
    }
  }
  return can_rotate;
}

void apply_rotation(GameInfo_t *game, FigurePosition_t *figure,
                    FigurePosition_t *temp_fig) {
  for (int i = 0; i < 4; i++) {
    if (figure->y[i] >= 0) {
      game->field[figure->y[i]][figure->x[i]] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    figure->x[i] = temp_fig->x[i];
    figure->y[i] = temp_fig->y[i];
  }

  for (int i = 0; i < 4; i++) {
    if (figure->y[i] >= 0) {
      game->field[figure->y[i]][figure->x[i]] = 1;
    }
  }
}

/********************************************************************************
 * Обработка очков и уровней
 ********************************************************************************/

void update_score(GameInfo_t *game, int count) {
  int points = 0;
  switch (count) {
    case 1:
      points = 100;
      break;
    case 2:
      points = 300;
      break;
    case 3:
      points = 700;
      break;
    case 4:
      points = 1500;
      break;
  }

  game->score += points;
  points_to_next_level -= points;

  if (points_to_next_level <= 0) {
    points_to_next_level += 600;
    if (game->level < 10) {
      game->level += 1;
      game->speed = 1 + game->level;
    }
  }

  if (game->score > game->high_score) {
    game->high_score = game->score;
    save_high_score(game->high_score);
  }
}

int check_gameover(GameInfo_t *info) {
  int gameover = 0;
  for (int j = 0; j <= 9; j++) {
    if (info->field[0][j] == 2) {
      gameover = 1;
    }
  }
  return gameover;
}

int getScore() {
  GameInfo_t *gameInfo = game_info();
  return gameInfo->score;
}

int getLevel() {
  GameInfo_t *gameInfo = game_info();
  return gameInfo->level;
}

unsigned int get_speed_delay(GameInfo_t *game) {
  unsigned int base_delay = 500000000;
  unsigned int min_delay = 50000000;
  unsigned int delay = base_delay - (base_delay * 0.1 * (game->level - 1));
  if (delay < min_delay) {
    delay = min_delay;
  }
  return delay;
}

void save_high_score(int score) {
  FILE *file = fopen(SCORE_FILE_PATH, "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

int load_high_score() {
  int high_score = 0;
  FILE *file = fopen(SCORE_FILE_PATH, "r");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  } else {
    save_high_score(0);
  }
  return high_score;
}
