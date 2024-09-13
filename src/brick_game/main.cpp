/**
 * @mainpage Brick Game Documentation
 *
 * Welcome to the documentation of the Tetris and Snake game
 * Collection.
 *
 * @section sec_controls Controls
 * - **Left Arrow**: Move left
 * - **Right Arrow**: Move right
 * - **P**: Rotate block clockwise - Tetris
 * - **Up Arrow**: Move Up
 * - **Down Arrow**: 
    - Speed up block descent
    - Tetris Move Down
 * - **Space**: Pause/unpause the game
 */

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include "tetris/tetris_main.h"
#include "snake/snake_main.h"

void showMainMenu() {
    clear();
    printw("Welcome to the Game!\n\n");
    printw("Choose a game to play:\n");
    printw("1. Tetris\n");
    printw("2. Snake\n");
    printw("3. Quit\n");
    refresh();
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (true) {
        showMainMenu();
        int choice = getch();
        switch (choice) {
            case '1':
                runTetris();
                break;
            case '2':
                runSnake();
                break;
            case '3':
                endwin();
                return 0;
            default:
                break;
        }
    }

    endwin();
    return 0;
}