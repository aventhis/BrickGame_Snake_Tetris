#include "snake_game_view.h"

#include <ncurses.h>

#include "../../../brick_game/snake/snake_game_model.h"

namespace s21 {

SnakeGameView::SnakeGameView(SnakeGameModel& model) : model_(model) {}

void SnakeGameView::initializeColors() const {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Змейка
  init_pair(2, COLOR_RED, COLOR_BLACK);    // Яблоко
  init_pair(3, COLOR_BLACK, COLOR_BLACK);  // Стенка
  init_pair(0, COLOR_WHITE, COLOR_WHITE);  // Поле
}

void SnakeGameView::drawField() const {
  initializeColors();
  const auto& field = model_.getField();
  WINDOW* window = newwin(
      field.size(), field[0].size() * 2, 0,
      0);  // Создание нового окна с размером, соответствующим размеру поля
  wclear(window);  // Очистка окна

  int display_x;
  for (size_t y = 0; y < field.size(); y++) {
    for (size_t x = 0; x < field[y].size(); x++) {
      display_x = x * 2;  // Удваиваем x для визуального отображения
      wmove(window, y, display_x);
      printElement(window, field[y][x]);  // Модифицировать printElement, чтобы
                                          // принимала WINDOW* как аргумент
    }
  }
  wrefresh(window);  // Обновление окна
  delwin(window);  // Удаление окна после использования
}

void SnakeGameView::printElement(WINDOW* win, int element) const {
  // initializeColors();
  switch (element) {
    case Field:
      wattron(win, COLOR_PAIR(0));
      waddch(win, ' ');
      wattroff(win, COLOR_PAIR(0));
      break;
    case SnakeHead:
      wattron(win, COLOR_PAIR(1));
      waddch(win, '"');  // Используем шахматную доску для тела змейки
      waddch(win, ' ');  // Используем блок для головы змейки
      wattroff(win, COLOR_PAIR(1));
      break;
    case SnakeBody:
      wattron(win, COLOR_PAIR(1));
      waddch(win, '#');  // Используем шахматную доску для тела змейки
      waddch(win, ' ');
      wattroff(win, COLOR_PAIR(1));
      break;
    case Apple:
      wattron(win, COLOR_PAIR(2));
      waddch(win, ACS_DIAMOND);  // Используем алмаз для яблока
      wattroff(win, COLOR_PAIR(2));
      break;
    case Border:
      wattron(win, COLOR_PAIR(3));
      waddch(win, '|');
      waddch(win, '|');
      wattroff(win, COLOR_PAIR(3));
      break;
  }
}

void SnakeGameView::updateInfoPanel() {
  // Определение размеров и положения панели информации
  int info_width = 30;
  int info_height = 10;
  int info_x =
      model_.getField()[0].size() * 2 + 3;  // Смещение справа от игрового поля
  int info_y = 1;

  // Создание и настройка окна для информационной панели
  WINDOW* info_win = newwin(info_height, info_width, info_y, info_x);
  box(info_win, 0, 0);  // Добавление рамки для визуального выделения

  // Вывод информации о игре
  mvwprintw(info_win, 1, 1, "Score: %d", model_.getScore());
  mvwprintw(info_win, 2, 1, "Level: %d", model_.getLevel());
  mvwprintw(info_win, 3, 1, "High Score: %d", model_.getHighScore());

  // Обновление окна
  wrefresh(info_win);

  // Освобождение ресурсов окна
  delwin(info_win);
}

void SnakeGameView::showWelcomeScreen() const {
  clear();  // Очищаем экран

  int height = 22;
  int width = 24;
  WINDOW* start_win = newwin(height, width, 0, 0);
  box(start_win, 0, 0);  // Добавление рамки
  // Вывод текста

  const char* title1 = "Welcome to";
  const char* title2 = "SNAKE GAME";
  mvwprintw(start_win, height / 2 - 5, (width - strlen(title1)) / 2, "%s",
            title1);
  mvwprintw(start_win, height / 2 - 3, (width - strlen(title2)) / 2, "%s",
            title2);

  const char* title3 = " Press: Enter to start";
  const char* title4 = "       'Q'  to quit";
  const char* pause_info = "        SPACE to pause";
  mvwprintw(start_win, height / 2 + 1, (width - strlen(title3)) / 2, "%s",
            title3);
  mvwprintw(start_win, height / 2 + 2, (width - strlen(title4)) / 2, "%s",
            title4);
  mvwprintw(start_win, height / 2 + 3, (width - strlen(pause_info)) / 2, "%s",
            pause_info);

  const char* control_info = "Use arrow keys to move";
  mvwprintw(start_win, height / 2 + 5, (width - 2) / 2, "^");
  mvwprintw(start_win, height / 2 + 6, (width - 2) / 2 - 1, "< >");
  mvwprintw(start_win, height / 2 + 7, (width - 2) / 2, "v");

  mvwprintw(start_win, height / 2 + 9, (width - strlen(control_info)) / 2, "%s",
            control_info);

  keypad(start_win, TRUE);  // Включение обработки функциональных клавиш в окне
  int ch;
  bool continueLoop = true;
  while (continueLoop) {
    ch = wgetch(start_win);
    switch (ch) {
      case '\n':  // Enter
      case KEY_ENTER:
        continueLoop = false;  // Выход из цикла
        break;
      case 'q':
      case 'Q':
        endwin();  // Завершаем ncurses
        exit(0);   // Выход из программы
        break;
    }
  }

  delwin(start_win);  // Удаление окна
}

void SnakeGameView::showGameOverScreen() const {
  clear();  // Очищаем экран
  int height = 22;
  int width = 24;
  WINDOW* gameover_win = newwin(height, width, 0, 0);
  box(gameover_win, 0, 0);  // Добавление рамки

  // Вывод текста
  const char* title1 = "Game Over";
  const char* title2 = "Press Enter to restart";
  const char* title3 = "Press 'Q' to quit";
  mvwprintw(gameover_win, height / 2 - 3, (width - strlen(title1)) / 2, "%s",
            title1);
  mvwprintw(gameover_win, height / 2 + 1, (width - strlen(title2)) / 2, "%s",
            title2);
  mvwprintw(gameover_win, height / 2 + 2, (width - strlen(title3)) / 2, "%s",
            title3);

  keypad(gameover_win,
         TRUE);  // Включение обработки функциональных клавиш в окне
  int ch;
  bool continueLoop = true;
  while (continueLoop) {
    ch = wgetch(gameover_win);
    switch (ch) {
      case '\n':  // Enter
      case KEY_ENTER:
        continueLoop = false;  // Выход из цикла
        break;
      case 'q':
      case 'Q':
        endwin();  // Завершаем ncurses
        exit(0);   // Выход из программы
        break;
    }
  }

  delwin(gameover_win);  // Удаление окна
}

void SnakeGameView::showGameWinScreen() const {
  clear();  // Очищаем экран
  int height = 22;
  int width = 24;
  WINDOW* gamewin_win = newwin(height, width, 0, 0);
  box(gamewin_win, 0, 0);  // Добавление рамки

  // Вывод текста
  const char* title1 = "You Win!";
  const char* title2 = "Press Enter to restart";
  const char* title3 = "Press 'Q' to quit";
  mvwprintw(gamewin_win, height / 2 - 3, (width - strlen(title1)) / 2, "%s",
            title1);
  mvwprintw(gamewin_win, height / 2 + 1, (width - strlen(title2)) / 2, "%s",
            title2);
  mvwprintw(gamewin_win, height / 2 + 2, (width - strlen(title3)) / 2, "%s",
            title3);

  keypad(gamewin_win,
         TRUE);  // Включение обработки функциональных клавиш в окне
  int ch;
  bool continueLoop = true;
  while (continueLoop) {
    ch = wgetch(gamewin_win);
    switch (ch) {
      case '\n':  // Enter
      case KEY_ENTER:
        continueLoop = false;  // Выход из цикла
        break;
      case 'q':
      case 'Q':
        endwin();  // Завершаем ncurses
        exit(0);   // Выход из программы
        break;
    }
  }

  delwin(gamewin_win);  // Удаление окна
}

void SnakeGameView::pauseGame() const {
  int height = 5;
  int width = 18;  // Сделаем окно шире
  // Определяем центр игрового поля
  int field_height = model_.getField().size();
  int field_width = model_.getField()[0].size() * 2;
  int start_y = (field_height - height - 2) / 2 +
                1;  // +1 для корректировки относительно рамки
  int start_x = (field_width - width - 2) / 2 +
                1;  // +1 для корректировки относительно рамки

  WINDOW* pause_win = newwin(height, width, start_y, start_x);
  box(pause_win, 0, 0);
  mvwprintw(pause_win, height / 2, (width - 6) / 2,
            "PAUSED");  // Центрируем текст "PAUSED"
  wrefresh(pause_win);

  // Ждем, пока пользователь не нажмет пробел снова для продолжения
  while (true) {
    int ch = getch();
    if (ch == ' ') {
      break;
    } else if (ch == 'q' || ch == 'Q') {
      endwin();  // Завершаем ncurses
      exit(0);   // Выход из программы
      break;
    }
  }

  delwin(pause_win);
}

}  // namespace s21
