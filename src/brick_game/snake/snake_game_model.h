#ifndef SNAKE_GAME_MODEL_H
#define SNAKE_GAME_MODEL_H

#include <cstdlib>  // Для функции rand()
#include <ctime>    // Для функции time()
#include <iostream>
#include <vector>

#include "../../gui/cli/snake/snake_game_view.h"
#include "../sharedfunction.h"

#define SCORE_FILE_PATH "/tmp/highscoresnake.txt"

namespace s21 {

/**
 * @file snake_game_model.h
 * @brief Header file for the model component of a snake game.
 *
 * This file contains the declaration of the SnakeGameModel class which
 * encapsulates all the logic specific to the state and behavior of the snake
 * game. It includes functionalities such as game initialization, movement and
 * growth of the snake, handling collisions, and score management.
 */

enum class Direction { Up, Down, Left, Right };

/**
 * @struct GameInfo_t
 * @brief Holds the state and configuration of the current game session.
 *
 * @var GameInfo_t::field
 * The game field where the snake moves, defined as a 10x20 grid.
 * @var GameInfo_t::score
 * Current score of the game.
 * @var GameInfo_t::high_score
 * Highest score achieved so far.
 * @var GameInfo_t::level
 * Current level of the game, affecting the game's difficulty.
 * @var GameInfo_t::speed
 * Speed of the game, affecting how fast the snake moves.
 * @var GameInfo_t::pause
 * Indicates whether the game is paused (1 - game is paused, 0 - game is
 * active).
 */
typedef struct {
  std::vector<std::vector<int>> field;  // Игровое поле размером 10x20
  int score;                            // Текущий счет
  int high_score;                       // Рекорд
  int level;  // Уровень сложности игры
  int speed;  // Скорость игры
  int pause;  // Состояние паузы (1 - игра на паузе, 0 - игра активна)
} GameInfo_t;

/**
 * @class SnakeGameModel
 * @brief Encapsulates the game logic for the Snake game.
 *
 * This class manages the state of the snake game, including the snake's
 * position, movement, apple generation, and collision handling. It also handles
 * score and level management based on the game's progress.
 */
// Сlass SnakeGameModel - logic for Snake
class SnakeGameModel {
 public:
  // Constructor to initialize the game grid
  void fsm_snake(GameState_t& state, UserAction_t& action, bool isTimerEvent);

  /**
   * Constructor that initializes the snake game model with a specific field
   * size.
   * @param width The width of the game field (typically 10).
   * @param height The height of the game field (typically 20).
   */
  SnakeGameModel(
      int wigth,
      int height);  // wigth и  height - размеры чисто игрового поля 10х20

  /**
   * Initializes the game field with given dimensions, setting up the initial
   * snake position and first apple.
   * @param width Width of the game field.
   * @param height Height of the game field.
   */
  void initializeGameField(int width, int height);

  /**
   * Resets the game to its initial state, clearing the field and resetting
   * scores.
   */
  void resetGame();

  /**
   * Places the initial snake on the game field at a default starting position.
   */
  void placeSnake();

  /**
   * Generates an apple on the game field at a random unoccupied position.
   */
  void generateApple();

  /**
   * Sets the current direction of the snake's movement.
   * @param dir The direction to set (Up, Down, Left, Right).
   */
  void setDirection(Direction dir);

  /**
   * Moves the snake in the current direction, updating its position on the game
   * field.
   */
  void moveSnake();

  /**
   * Calculates the new head position of the snake based on its current
   * direction.
   * @return A pair of integers representing the new head coordinates.
   */
  std::pair<int, int> calculateNewHead();

  /**
   * Handles any collisions that occur at the new head position, such as
   * collisions with the wall, self, or an apple.
   * @param new_head Coordinates of the new head position.
   */
  void handleCollision(std::pair<int, int> new_head);

  /**
   * Updates the game field to reflect the new position of the snake.
   * @param new_head Coordinates of the new head position.
   */
  void updateGameField(std::pair<int, int> new_head);

  /**
   * Increases the game's level, typically making the snake move faster.
   */
  void increaseLevel();

  /**
   * Restarts the game by resetting all game parameters and starting a new game
   * session.
   */
  void restartGame();

  /**
   * Retrieves the current game field.
   * @return A constant reference to the game field matrix.
   */
  std::vector<std::vector<int>> getField() const;

  /**
   * Retrieves the current score of the game.
   * @return Current score.
   */
  int getScore() const;

  /**
   * Retrieves the highest score recorded for the game.
   * @return Highest score.
   */
  int getHighScore() const;

  /**
   * Retrieves the current level of the game.
   * @return Current level.
   */
  int getLevel() const;

  /**
   * Checks if the game is over (i.e., collision with the wall or snake itself).
   * @return True if the game is over, otherwise false.
   */
  bool isGameOver();

  /**
   * Checks if the game has been won (usually a certain score or condition is
   * met).
   * @return True if the game has been won, otherwise false.
   */
  bool isGameWin();

  /**
   * Checks if a collision has occurred on the last move.
   * @return True if there was a collision, otherwise false.
   */
  bool isCollision();

  /**
   * Checks if the snake has eaten an apple on the last move.
   * @return True if an apple was eaten, otherwise false.
   */
  bool isAppleEaten();

  /**
   * Checks if the snake has reached the maximum possible size.
   * @return True if the snake is at maximum size, otherwise false.
   */
  bool isMaxSizeSnake();

  /**
   * Processes the action of the snake eating an apple, including growing the
   * snake and increasing the score.
   */
  void eatApple();

  /**
   * Handles a change in direction based on user input.
   * @param action The action representing the new direction.
   */
  void handleDirectionChange(UserAction_t action);

  /**
   * Saves the highest score to a file.
   * @param score The score to save.
   */
  void save_high_score(int score);

  /**
   * Loads the highest score from a file.
   * @return The highest score loaded from the file.
   */
  int load_high_score();

  /**
   * Updates the game score, typically after the snake eats an apple or achieves
   * a game milestone.
   */
  void update_score();

 private:
  GameInfo_t gameInfo_;
  // wigth_ и height_ - размеры игрового поля с границами 22х12
  int width_;
  int height_;
  std::vector<std::pair<int, int>> snake_;
  bool gameOver_;
  bool gameWin_;
  bool isCollision_;
  bool isAppleEaten_;
  Direction direction_;
};  // class SnakeGameModel

}  // namespace s21

#endif  // SNAKE_GAME_MODEL_H