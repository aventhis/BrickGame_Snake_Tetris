#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include "gamewindow.h"
#include "snakeboard.h"
#include "gamechooser.h"

namespace s21 {

class SnakeWindow : public GameWindow
{
    Q_OBJECT
public:
    explicit SnakeWindow(QWidget *parent = nullptr);
    void onQuitGame();

protected:
    GameBoard* getBoard() const override;

private:
    SnakeBoard *board;
};

}

#endif // SNAKEWINDOW_H
