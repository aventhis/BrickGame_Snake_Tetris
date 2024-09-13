#include "cli.h"

void draw_field(GameInfo_t* game) {
  WINDOW* window = newwin(22, 23, 0, 0);
  werase(window);
  box(window, 0, 0);

  for (int i = 1; i < 21; i++) {
    for (int j = 2; j < 22; j += 2) {
      if (game->field[i - 1][(j - 2) / 2] == 1) {
        wattron(window, COLOR_PAIR(1));
        mvwaddch(window, i, j, ACS_CKBOARD);
        wattroff(window, COLOR_PAIR(1));
      } else if (game->field[i - 1][(j - 2) / 2] == 2) {
        wattron(window, COLOR_PAIR(2));
        mvwaddch(window, i, j, ACS_CKBOARD);
        wattroff(window, COLOR_PAIR(2));
      } else {
        mvwaddch(window, i, j, '.');
      }
    }
  }

  wrefresh(window);
  delwin(window);
}

void initializeColors() {
  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, -1);
  init_pair(2, COLOR_RED, -1);
  init_pair(3, COLOR_BLACK, -1);
  init_pair(4, COLOR_WHITE, -1);
}

void init_gui() {
  initscr();  // Инициализация ncurses
  cbreak();  // ввод символов обрабатывается немедленно
  noecho();  // Отключение вывода вводимых символов
  curs_set(0);           // Скрытие курсора
  keypad(stdscr, TRUE);  // Включение обработки функциональных клавиш
  initializeColors();

  nodelay(stdscr, TRUE);  // не держит ввод getch()
  scrollok(stdscr, TRUE);
}

void end_gui() { endwin(); }

UserAction_t getUserAction(int ch) {
  switch (ch) {
    case 'q':
    case 'Q':
      return Terminate;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case 'P':
    case 'p':
      return Action;
    case ' ':
      return Pause;
    case 13:
    case 10:
      return Start;
    default:
      return Start;
  }
}

void showWelcomeScreen() {
  clear();

  int height = 22;
  int width = 24;
  WINDOW* start_win = newwin(height, width, 0, 0);
  box(start_win, 0, 0);

  const char* title1 = "Welcome to";
  const char* title2 = "TETRIS";
  mvwprintw(start_win, height / 2 - 5, (width - strlen(title1)) / 2, "%s",
            title1);
  wattron(start_win, COLOR_PAIR(1));
  mvwprintw(start_win, height / 2 - 3, (width - strlen(title2)) / 2, "%s",
            title2);
  wattroff(start_win, COLOR_PAIR(1));
  const char* title3 = " Press: Enter to start";
  const char* title4 = "       'Q'  to quit";
  const char* pause_info = "        SPACE to pause";
  const char* action_info = "        'P'  to rotate";
  mvwprintw(start_win, height / 2 + 1, (width - strlen(title3)) / 2, "%s",
            title3);
  mvwprintw(start_win, height / 2 + 2, (width - strlen(title4)) / 2, "%s",
            title4);
  mvwprintw(start_win, height / 2 + 3, (width - strlen(pause_info)) / 2, "%s",
            pause_info);
  mvwprintw(start_win, height / 2 + 4, (width - strlen(action_info)) / 2, "%s",
            action_info);
  const char* control_info = "Use arrow keys to move";

  mvwprintw(start_win, height / 2 + 6, (width - 2) / 2 - 1, "< >");
  mvwprintw(start_win, height / 2 + 7, (width - 2) / 2, "v");

  mvwprintw(start_win, height / 2 + 9, (width - strlen(control_info)) / 2, "%s",
            control_info);

  keypad(start_win, TRUE);
  int ch;
  bool continueLoop = true;
  while (continueLoop) {
    ch = wgetch(start_win);
    switch (ch) {
      case '\n':
      case KEY_ENTER:
        continueLoop = false;
        break;
      case 'q':
      case 'Q':
        endwin();
        exit(0);
        break;
    }
  }

  delwin(start_win);
}

void showGameOverScreen() {
  clear();
  int height = 22;
  int width = 24;
  WINDOW* gameover_win = newwin(height, width, 0, 0);
  box(gameover_win, 0, 0);  // Добавление рамки

  // Вывод текста
  const char* title1 = "Game Over";
  const char* title2 = "Press Enter to restart";
  const char* title3 = "Press 'Q' to quit";
  wattron(gameover_win, COLOR_PAIR(2));
  mvwprintw(gameover_win, height / 2 - 3, (width - strlen(title1)) / 2, "%s",
            title1);
  wattroff(gameover_win, COLOR_PAIR(2));
  mvwprintw(gameover_win, height / 2 + 1, (width - strlen(title2)) / 2, "%s",
            title2);
  mvwprintw(gameover_win, height / 2 + 2, (width - strlen(title3)) / 2, "%s",
            title3);

  keypad(gameover_win, TRUE);
  int ch;
  bool continueLoop = true;
  while (continueLoop) {
    ch = wgetch(gameover_win);
    switch (ch) {
      case '\n':
      case KEY_ENTER:
        continueLoop = false;
        break;
      case 'q':
      case 'Q':
        endwin();
        exit(0);
        break;
    }
  }

  delwin(gameover_win);
}

void pauseGame() {
  int height = 5;
  int width = 17;
  int field_height = 22;
  int field_width = 23;
  int start_y = (field_height - height) / 2;
  int start_x = (field_width - width) / 2;

  WINDOW* pause_win = newwin(height, width, start_y, start_x);
  box(pause_win, 0, 0);
  mvwprintw(pause_win, height / 2, (width - 6) / 2, "PAUSED");
  wrefresh(pause_win);

  while (true) {
    int ch = getch();
    if (ch == ' ') {
      break;
    } else if (ch == 'q' || ch == 'Q') {
      endwin();
      exit(0);
      break;
    }
  }

  delwin(pause_win);
}

void drawNextFigure(WINDOW* win, GameInfo_t* game) {
  box(win, 0, 0);
  mvwprintw(win, 1, 2, "Next Figure:");

  // Определяем координаты для центрирования фигуры
  int starty = (getmaxy(win) - 2) / 2;
  int startx = (getmaxx(win) - 8) / 2;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->next[i][j] == 1) {
        wattron(win, COLOR_PAIR(1));
        mvwaddch(win, starty + i, startx + j * 2, ACS_CKBOARD);
        wattroff(win, COLOR_PAIR(1));
      } else {
        mvwaddch(win, starty + i, startx + j * 2, ' ');
      }
    }
  }

  wrefresh(win);
}

// Определение функции updateInfoPanel
void updateInfoPanel(GameInfo_t* game) {
  int info_width = 30;
  int info_height = 10;
  int info_x = 23 + 3;
  int info_y = 0;

  WINDOW* info_win = newwin(info_height, info_width, info_y, info_x);
  box(info_win, 0, 0);

  mvwprintw(info_win, 1, 2, "Score: %d", getScore());
  mvwprintw(info_win, 3, 2, "Level: %d", getLevel());
  mvwprintw(info_win, 5, 2, "High Score: %d", load_high_score());

  wrefresh(info_win);
  delwin(info_win);

  int next_width = 30;
  int next_height = 10;
  int next_x = 23 + 3;
  int next_y = info_y + info_height + 2;

  WINDOW* next_win = newwin(next_height, next_width, next_y, next_x);
  drawNextFigure(next_win, game);

  wrefresh(next_win);
  delwin(next_win);
}

// вариант полей №2
// for (int y = 0; y < 23; ++y) {
//   mvwaddch(window, y, 0, '|');
//   mvwaddch(window, y, 22, '|');
// }

// for (int y = 1; y < 21; ++y) {
//   mvwaddch(window, y, 1, '|');
//   mvwaddch(window, y, 21, '|');
// }

// // Отрисовка горизонтальных границ
// for (int x = 0; x < 23; ++x) {
//   mvwaddch(window, 0, x, '|ƒ');
//   mvwaddch(window, 21, x, '|');
// }
// wattroff(window, COLOR_PAIR(5)); // Отключение атрибута цвета
