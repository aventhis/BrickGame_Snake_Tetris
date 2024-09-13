#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QtWidgets>
#include <QFrame>
#include <QBasicTimer>
#include <QColor>
#include "../../../brick_game/sharedfunction.h"

namespace s21 {

class GameBoard : public  QFrame
{
    Q_OBJECT
public:
    GameBoard(QWidget *parent = nullptr);

    bool gameIsStarted() const;
    bool isPausedpush() const;
    void pause();
    virtual void start() = 0;

protected:
    bool isStarted;


    bool isPaused;
    void pauseGame();

    bool gameover;

    QBasicTimer timer;

    void drawSquare(QPainter &painter, int x, int y, QColor color);
    void drawBackground(QPainter &painter, QColor color);

    UserAction_t getUserAction(int ch);
    UserAction_t userAction;
    GameState_t gameState;

    int score; // Добавляем переменную для хранения счета
    int level;
    int highScore;

    void initStart();
    void initGameOver();

    int normalInterval;
    int fastInterval;
    void startTimer(int interval);

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void highScoreChanged(int highScore);
    void gameOverOccurred();
};

}

#endif // GAMEBOARD_H
