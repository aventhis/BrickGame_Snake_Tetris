#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include "gameboard.h"
#include "../../../brick_game/tetris/game_logic.h"

class QLabel;

namespace s21 {

class TetrixBoard : public GameBoard
{
    Q_OBJECT

public:
    explicit TetrixBoard(QWidget *parent = nullptr);
    void start() override;

    void checkGameOver();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void drawNextFigure(QPainter &painter);
    void updateGame(bool isTimerEvent);
    void updateScore(int lines);

//    QLabel *gameOverLabel;
};

}

#endif
