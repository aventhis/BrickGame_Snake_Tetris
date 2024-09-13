/**
 * @file cli.h
 * @brief Header file for the command line interface of the Tetris game.
 *
 * This file declares functions and includes necessary for creating a
 * command-line based graphical user interface using ncurses for the Tetris
 * game.
 */

#ifndef ClI_H
#define ClI_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BOARD_N 40   /**< Width of the game board */
#define BOARD_M 40   /**< Height of the game board */
#define HUD_WIDTH 20 /**< Width of the HUD (head-up display) */

#include "../../../brick_game/tetris/game_logic.h"

/**
 * @brief Captures user input and translates it into game actions.
 *
 * @param ch Character code of the pressed key.
 * @return Corresponding action based on the user input.
 */
UserAction_t getUserAction(int ch);

/**
 * @brief Initializes the graphical user interface using ncurses library.
 */
void init_gui();

/**
 * @brief Cleans up and shuts down the ncurses user interface.
 */
void end_gui();

/**
 * @brief Initializes color pairs for use in the ncurses interface.
 */
void initializeColors();

/**
 * @brief Draws the game board on the screen.
 *
 * @param game Pointer to the current game information structure.
 */
void draw_field(GameInfo_t *game);

/**
 * @brief Displays the game over screen.
 */
void showGameOverScreen();

/**
 * @brief Displays the welcome screen at the start of the game.
 */
void showWelcomeScreen();

/**
 * @brief Updates the information panel to show scores, levels, and other game
 * stats.
 *
 * @param game Pointer to the current game information structure.
 */
void updateInfoPanel(GameInfo_t *game);

/**
 * @brief Draws the next figure preview in the specified window.
 *
 * @param win Pointer to the ncurses window where the next figure will be drawn.
 * @param game Pointer to the current game information structure.
 */
void drawNextFigure(WINDOW *win, GameInfo_t *game);

/**
 * @brief Pauses the game and displays a pause screen.
 */
void pauseGame();

#endif