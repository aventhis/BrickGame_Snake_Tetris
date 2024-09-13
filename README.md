# BrickGame Snake

## Introduction

`BrickGame Snake` is a C++ project that implements the Snake game using object-oriented programming principles. The game includes a library for game logic and a desktop graphical interface for user interaction. The project also follows the MVC pattern to separate concerns between the game logic and interface.

## Features

- Classic Snake game mechanics.
- Uses a finite-state machine to formalize game logic.
- Implements MVC pattern for clear separation between logic, view, and controller.
- Supports scoring and game record tracking.
- Level mechanics that increase the speed of the snake as the player progresses.

## Project Structure

- **Library**: The game logic is located in the `src/brick_game/snake` folder.
- **Desktop GUI**: The user interface is located in the `src/gui/desktop` folder.
- **Console Interface**: Supports the Snake game from the BrickGame v1.0 project.

## Game Mechanics

1. **Snake Movement**: The snake moves one block automatically when the game timer expires.
2. **Apples**: The snake's length increases by one when it consumes an apple.
3. **Winning Condition**: The player wins when the snake reaches a length of 200 units.
4. **Losing Condition**: The player loses when the snake crashes into itself or the field boundary.
5. **Controls**: The player can change the snake's direction using the arrow keys and speed up its movement by pressing the action key.

## Bonus Features

### Scoring and Game Record

- The game tracks the player's score, with one point awarded per apple.
- The highest score is saved between sessions.

### Level Mechanics

- The snake's speed increases with each new level (every 5 points), up to a maximum of 10 levels.

## Makefile Targets

- **make all**: Build the entire project, including the game logic and GUI.
- **make clean**: Remove all compiled object files and executables.
- **make test**: Compile and run unit tests to verify the game logic.
- **make install**: Install the game on your system.
- **make uninstall**: Remove the game from your system.
- **make dist**: Create a distributable package of the project.
- **make dvi**: Generate the project documentation.
- **make gcov_report**: Generate a code coverage report in HTML format.

