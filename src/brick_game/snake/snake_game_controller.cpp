#include "snake_game_controller.h"

namespace s21 {

SnakeGameController::SnakeGameController(SnakeGameModel& model,
                                         SnakeGameView& view)
    : model_(model), view_(view) {}

void SnakeGameController::run() {
  GameState_t state = START;
  init_gui();
  view_.updateInfoPanel();
  view_.showWelcomeScreen();
  while (true) {
    int ch = getch();
    UserAction_t action = getUserAction(ch);
    if (action == Terminate) {
      break;
    }
    if (action == Pause) {
      view_.pauseGame();
      continue;
    }

    model_.fsm_snake(state, action, false);
    if (state == GAMEOVER) {
      if (model_.isGameOver())
        view_.showGameOverScreen();  // show gameover
      else if (model_.isGameWin())
        view_.showGameWinScreen();  // show gamewin
      model_.restartGame();
    }
    view_.drawField();
    view_.updateInfoPanel();
    timeout(550 - (model_.getLevel() - 1) * 50);
    usleep(10000);  // Задержка для сглаживания анимации
  }
  endwin();  // Завершение работы с ncurses
}

void SnakeGameController::init_gui() {
  initscr();  // Инициализация ncurses
  cbreak();  // ввод символов обрабатывается немедленно
  noecho();  // Отключение вывода вводимых символов
  curs_set(0);           // Скрытие курсора
  keypad(stdscr, TRUE);  // Включение обработки функциональных клавиш
  timeout(400);
}

UserAction_t SnakeGameController::getUserAction(int ch) {
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

}  // namespace s21
