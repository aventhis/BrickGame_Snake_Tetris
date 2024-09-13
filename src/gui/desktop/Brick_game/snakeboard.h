#ifndef SNAKEBOARD_H
#define SNAKEBOARD_H

#include "gameboard.h"
#include "../../../brick_game/snake/snake_game_model.h"

namespace s21 {

class SnakeBoard : public GameBoard {
    Q_OBJECT

public:
    explicit SnakeBoard(QWidget *parent = nullptr);
    void start() override;

    void checkGameOver();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:

    void updateGame(bool isTimerEvent);
    bool isMoving;

    SnakeGameModel model_;

    void updateTimerInterval();
};

}

#endif // SNAKEBOARD_H
