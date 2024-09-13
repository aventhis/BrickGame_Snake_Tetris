#ifndef SNAKE_GAME_VIEW_H
#define SNAKE_GAME_VIEW_H

#include <ncurses.h>
#include <cstring>

namespace s21 {

// Forward declaration
class SnakeGameModel;

typedef enum {
    Field,
    SnakeHead,
    SnakeBody,
    Apple,
    Border,
} FieldView;



// Сlass SnakeGameView - view for Snake in terminal
class SnakeGameView {
public:
    explicit SnakeGameView(SnakeGameModel& model);
    
    void showWelcomeScreen() const;
    void showGameOverScreen() const;
    void showGameWinScreen() const;
    void pauseGame() const;
    void updateInfoPanel();

    void drawField() const;
    
private:
    SnakeGameModel& model_;
    void printElement(WINDOW* win, int element) const;
    void initializeColors() const;

}; // class SnakeGameView

} // namespace s21

#endif // SNAKE_GAME_VIEW_H
