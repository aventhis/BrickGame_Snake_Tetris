#include "../../gui/cli/tetris/cli.h"
#include "game_logic.h"

void runTetris() {
  init_gui();
  GameInfo_t *gameInfo = game_info();
  GameState_t state = START;
  showWelcomeScreen();
  initialize_game(gameInfo);
  while (true) {
    int ch = getch();
    UserAction_t action = getUserAction(ch);
    flushinp();
    if (action == Terminate) {
      break;
    }
    if (action == Pause) {
      pauseGame();  // Вызываем функцию паузы
      continue;  // Возвращаемся в начало цикла после паузы
    }

    fsm(&state, &action, false);
    updateInfoPanel(gameInfo);
    draw_field(gameInfo);

    if (state == GAMEOVER) {
      showGameOverScreen();
    }
    unsigned int delay =
        get_speed_delay(gameInfo);  // получаем задержку в наносекундах

    // Создаем структуру timespec для задержки
    struct timespec req = {0, delay};
    nanosleep(&req, NULL);  // Используем nanosleep вместо usleep
  }
  end_gui();
}