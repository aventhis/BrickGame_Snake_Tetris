#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include "gamewindow.h"
#include "tetrixboard.h"
#include "gamechooser.h"

namespace s21 {

class TetrixWindow : public GameWindow
{
    Q_OBJECT
public:
    explicit TetrixWindow(QWidget *parent = nullptr);
    void onQuitGame();

protected:
    GameBoard* getBoard() const override;

private:
    TetrixBoard *board;
    QLabel *nextPieceHeaderLabel;
};

}

#endif // TETRIXWINDOW_H
