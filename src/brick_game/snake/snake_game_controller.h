#ifndef SNAKE_GAME_CONTROLLER_H
#define SNAKE_GAME_CONTROLLER_H

#include <unistd.h>  // для usleep()

#include "snake_game_model.h"

namespace s21 {

// Forward declaration
class SnakeGameModel;
class SnakeGameView;

/**
 * @file snake_game_controller.h
 * @brief Header file for the controller component of a snake game.
 *
 * This file contains the declaration of the SnakeGameController class, which
 * integrates the model and view components of the snake game. It manages the
 * game loop, handles user inputs, and updates the game state accordingly.
 */

/**
 * @class SnakeGameController
 * @brief Manages the interactions between the game's view and model.
 *
 * This class functions as the central controller for the snake game, handling
 * the main game loop, user input, and game state updates. It uses instances of
 * SnakeGameModel for game logic and SnakeGameView for displaying the game.
 *
 * @var SnakeGameController::model_
 * Reference to the SnakeGameModel object representing the game's logic and
 * state.
 *
 * @var SnakeGameController::view_
 * Reference to the SnakeGameView object for rendering the game's visuals.
 */

// Сlass SnakeGameController - View+Model
class SnakeGameController {
 public:
  /**
   * Constructs a new SnakeGameController object.
   * @param model Reference to the game's model.
   * @param view Reference to the game's view.
   */
  explicit SnakeGameController(SnakeGameModel& model, SnakeGameView& view);

  /**
   * Starts the main game loop, processing input and rendering the game until it
   * ends.
   */
  void run();

 private:
  /**
   * Initializes the game's graphical user interface.
   */
  void init_gui();

  /**
   * Processes user input to determine the next action.
   * @param ch The input character code.
   * @return UserAction_t The action determined from the input.
   */
  UserAction_t getUserAction(int ch);

  /**
   * Updates the game state based on the current model state.
   */
  void updateCurrentState();
  SnakeGameModel& model_;
  SnakeGameView& view_;
};  // class SnakeGameController

}  // namespace s21

#endif  // SNAKE_GAME_CONTROLLER_H