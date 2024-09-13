#ifndef SHARED_FUNCTION_h
#define SHARED_FUNCTION_h

/**
 * @enum UserAction_t
 * @brief Enumerates possible user actions in the game.
 */
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

// /**
//  * @enum GameState_t
//  * @brief Represents the state of the game at any given time.
//  */
typedef enum {
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    ATTACHING,
    GAMEOVER
} GameState_t;

#endif