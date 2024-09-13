#include "../../gui/cli/snake/snake_game_view.h"
#include "snake_game_controller.h"
#include "snake_game_model.h"

void runSnake() {
  s21::SnakeGameModel model(10, 20);
  s21::SnakeGameView view(model);
  s21::SnakeGameController controller(model, view);
  controller.run();
}