#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file game_logic.h
 * @brief Header file for the game logic of a Tetris-like game.
 *
 * This file contains definitions of structures and functions used to manage
 * the state and behavior of the Tetris game. It handles game initialization,
 * user input, game state updates, collision detection, and score management.
 */
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../sharedfunction.h"

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10
#define FIGURE_HEIGHT 4
#define FIGURE_WIDTH 4
#define NUM_FIGURES 7
#define SCORE_FILE_PATH "/tmp/highscore.txt"

/**
 * @struct FigurePosition_t
 * @brief Holds all relevant information about a Tetris figure's position and
 * type.
 *
 * @var FigurePosition_t::x
 * Array storing x-coordinates of each block in the figure.
 * @var FigurePosition_t::y
 * Array storing y-coordinates of each block in the figure.
 * @var FigurePosition_t::rotation_index
 * Current rotation index of the figure.
 * @var FigurePosition_t::figure_type
 * Type of the figure, usually an index referring to a set of predefined shapes.
 */
typedef struct {
  int x[4];
  int y[4];
  int rotation_index;
  int figure_type;
} FigurePosition_t;

/**
 * @struct GameInfo_t
 * @brief Holds the state and configuration of the current game session.
 *
 * @var GameInfo_t::field
 * The game field where the Tetris blocks are placed.
 * @var GameInfo_t::next
 * The next Tetris figure to be played.
 * @var GameInfo_t::score
 * Current score of the game.
 * @var GameInfo_t::high_score
 * Highest score achieved so far.
 * @var GameInfo_t::level
 * Current level of the game.
 * @var GameInfo_t::speed
 * Speed of the game, affecting how fast figures fall.
 * @var GameInfo_t::pause
 * Indicates whether the game is paused.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * Returns the current position of the active Tetris figure.
 */
FigurePosition_t *current_figure_position(void);

/**
 * Updates and returns the current state of the game.
 */
GameInfo_t updateCurrentState();

/**
 * Returns a pointer to the current game information structure.
 */
GameInfo_t *game_info();

/**
 * Returns the current game score.
 */
int getScore();

/**
 * Returns the current game level.
 */
int getLevel();

extern int figures[NUM_FIGURES][FIGURE_HEIGHT][FIGURE_WIDTH];

/**
 * Initializes the points necessary for the next level.
 */
void initialize_points_to_next_level();

/**
 * Handles user input based on the action type and whether it should be held.
 * @param action The action performed by the user.
 * @param hold Indicates whether the action is a continuous hold.
 */
void userInput(UserAction_t action, bool hold);

/**
 * Handles the down action, whether it's a quick drop or continuous down
 * movement.
 * @param gameInfo Current state of the game.
 * @param hold Indicates if the down action should be fast or continuous.
 */
void handle_down_action(GameInfo_t *gameInfo, bool hold);

/**
 * Finite state machine to manage game states transitions based on user actions
 * and game conditions.
 * @param state Pointer to the current game state.
 * @param action Pointer to the user action that may trigger a state change.
 */
void fsm(GameState_t *state, UserAction_t *action, bool isTimerEvent);

/**
 * Allocates a 2D array dynamically.
 * @param array Reference to the pointer that will store the allocated array.
 * @param rows Number of rows to allocate.
 * @param cols Number of columns to allocate.
 * @return Returns 0 if successful, or 1 if there was an error.
 */
int allocate_2d_array(int ***array, int rows, int cols);

/**
 * Frees a dynamically allocated 2D array.
 * @param array Reference to the array to be freed.
 * @param rows Number of rows in the array.
 */
void free_2d_array(int ***array, int rows);

/**
 * Initializes the game, setting up the initial state and allocating memory for
 * the game field.
 * @param game Pointer to the game information structure to initialize.
 */
void initialize_game(GameInfo_t *game);

/**
 * Starts the game, initializing game-specific configurations and clearing the
 * game board.
 * @param game Pointer to the game information structure.
 */
void initialize_game_start(GameInfo_t *game);

/**
 * Clears the game board to its initial state with all cells set to zero.
 * @param game Pointer to the game information structure.
 */
void clear_game_board(GameInfo_t *game);

/**
 * Clears the representation of the next figure.
 * @param game Pointer to the game information structure.
 */
void clear_next_figure(GameInfo_t *game);

/**
 * Selects the next figure randomly and updates the game state accordingly.
 * @param game Pointer to the game information structure.
 * @return Index of the chosen figure.
 */
int select_next_figure(GameInfo_t *game);

/**
 * Adds the next figure to the game field at the starting position.
 * @param game Pointer to the game information structure.
 */
void add_next_figure(GameInfo_t *game);

/**
 * Checks if the current figure is a square shape, which does not require
 * rotation.
 * @param figure Pointer to the figure position structure.
 * @return Returns 1 if the figure is square, otherwise 0.
 */
int is_square_figure(FigurePosition_t *figure);

/**
 * Updates the position of the current figure on the game field.
 * @param game Pointer to the game information structure.
 * @param dx Horizontal displacement.
 * @param dy Vertical displacement.
 */
void update_figure_position(GameInfo_t *game, int dx, int dy);

/**
 * Fixes the current figure in its position on the game field, making it part of
 * the permanent structure.
 * @param game Pointer to the game information structure.
 */
void fix_figure(GameInfo_t *game);

/**
 * Checks if a move is possible in the specified direction.
 * @param game Pointer to the game information structure.
 * @param dx Horizontal displacement.
 * @param dy Vertical displacement.
 * @return Returns true if the move is possible, otherwise false.
 */
bool can_move(GameInfo_t *game, int dx, int dy);

/**
 * Checks if moving the figure to the specified coordinates will result in a
 * collision.
 * @param game Pointer to the game information structure.
 * @param newPositionsX Array of new x-coordinates for the figure.
 * @param newPositionsY Array of new y-coordinates for the figure.
 * @param figure Pointer to the current figure position.
 * @return Returns true if there is no collision, otherwise false.
 */
bool check_collisions(GameInfo_t *game, int *newPositionsX, int *newPositionsY,
                      FigurePosition_t *figure);

/**
 * Checks if the specified positions are within the game field boundaries.
 * @param newPositionsX Array of x-coordinates to check.
 * @param newPositionsY Array of y-coordinates to check.
 * @return Returns true if all positions are within bounds, otherwise false.
 */
bool check_boundaries(int *newPositionsX, int *newPositionsY);

/**
 * Checks if the current figure can be moved downwards without collisions.
 * @param game Pointer to the game information structure.
 * @return Returns true if the figure can be moved down, otherwise false.
 */
bool can_move_down(GameInfo_t *game);

/**
 * Checks if the current figure can be moved left without collisions.
 * @param game Pointer to the game information structure.
 * @return Returns true if the figure can be moved left, otherwise false.
 */
bool can_move_left(GameInfo_t *game);

/**
 * Checks if the current figure can be moved right without collisions.
 * @param game Pointer to the game information structure.
 * @return Returns true if the figure can be moved right, otherwise false.
 */
bool can_move_right(GameInfo_t *game);

/**
 * Rotates the current figure if possible according to game rules and checks.
 * @param game Pointer to the game information structure.
 */
void rotate_figure(GameInfo_t *game);

/**
 * Performs the rotation of the figure around a center point.
 * @param figure Pointer to the current figure position to rotate.
 * @param temp_fig Pointer to a temporary figure position that will hold the new
 * positions.
 * @param centerX The x-coordinate of the rotation center.
 * @param centerY The y-coordinate of the rotation center.
 */
void perform_rotation(FigurePosition_t *figure, FigurePosition_t *temp_fig,
                      int centerX, int centerY);

/**
 * Determines if the rotated figure can be placed without causing a collision or
 * boundary breach.
 * @param game Pointer to the game information structure.
 * @param temp_fig Pointer to the figure position after rotation.
 * @return Returns true if the figure can be rotated without issues, otherwise
 * false.
 */
bool can_rotate_figure(GameInfo_t *game, FigurePosition_t *temp_fig);

/**
 * Applies the rotation to the figure on the game field, updating its position
 * to the rotated coordinates.
 * @param game Pointer to the game information structure.
 * @param figure Pointer to the original figure position.
 * @param temp_fig Pointer to the figure position after rotation which will be
 * applied if valid.
 */
void apply_rotation(GameInfo_t *game, FigurePosition_t *figure,
                    FigurePosition_t *temp_fig);

/**
 * Checks if the game is over based on the state of the top row of the game
 * field.
 * @param info Pointer to the game information structure.
 * @return Returns 1 if the game is over, otherwise 0.
 */
int check_gameover(GameInfo_t *info);

/**
 * Checks for and removes complete lines from the game field, updating the score
 * accordingly.
 * @param game Pointer to the game information structure.
 */
void check_and_remove_full_lines(GameInfo_t *game);

/**
 * Updates the game score based on the number of lines cleared.
 * @param game Pointer to the game information structure.
 * @param count Number of lines cleared in the last move.
 */
void update_score(GameInfo_t *game, int count);

/**
 * Calculates the delay between figure drops based on the current game level.
 * @param game Pointer to the game information structure.
 * @return Returns the delay in microseconds.
 */
unsigned int get_speed_delay(GameInfo_t *game);

/**
 * Saves the highest score achieved to a file.
 * @param score Score to save as the highest score.
 */
void save_high_score(int score);

/**
 * Loads the highest score from a file.
 * @return Returns the highest score read from the file.
 */
int load_high_score();
#endif

#ifdef __cplusplus
}
#endif