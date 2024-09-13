#include "game_logic.h"

void fsm(GameState_t* state, UserAction_t* action, bool isTimerEvent) {
  GameInfo_t* game = game_info();
  switch (*state) {
    case START:
      if (*action == Start) {
        initialize_game_start(game);
        *state = SPAWN;
      }
      break;
    case SPAWN:
      add_next_figure(game);
      *state = MOVING;
      break;
    case MOVING:
      if (*action == Action) {
        *state = SHIFTING;
      } else {
        if (isTimerEvent) {
          // Таймерное событие - двигаем фигуру вниз
          userInput(Down, false);
        } else {
          // Событие от пользователя
          userInput(*action, true);
        }
        // userInput(*action, false);
        if (!can_move_down(game)) *state = ATTACHING;
      }
      break;
    case SHIFTING:
      rotate_figure(game);
      *state = MOVING;
      break;
    case ATTACHING:
      fix_figure(game);
      if (check_gameover(game)) {
        *state = GAMEOVER;
      } else {
        *state = SPAWN;
      }
      break;
    case GAMEOVER:
      *state = START;
      break;
  }
}
