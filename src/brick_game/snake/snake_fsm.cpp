#include "snake_game_model.h"

namespace s21 {

void SnakeGameModel::fsm_snake(GameState_t& state, UserAction_t& action,
                               bool isTimerEvent) {
  isTimerEvent = false;
  if (isTimerEvent) {
  }
  switch (state) {
    case START:
      if (action == Start) state = SPAWN;
      break;
    case SPAWN:
      state = MOVING;
      break;
    case MOVING:
      handleDirectionChange(action);
      moveSnake();
      if (isCollision() || isMaxSizeSnake()) state = GAMEOVER;
      break;
    case SHIFTING:
      break;
    case ATTACHING:  // Winning after eating
      break;
    case GAMEOVER:
      state = START;
      break;
  }
}

}  // namespace s21