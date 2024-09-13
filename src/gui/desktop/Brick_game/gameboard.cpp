#include "gameboard.h"

using namespace s21;

GameBoard::GameBoard(QWidget *parent)
    : QFrame{parent},
      isStarted(false),
      isPaused(false),
      gameover(false),
      gameState(START),
      normalInterval(500),
      fastInterval(100) {
  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setFocusPolicy(
      Qt::StrongFocus);  // Убедитесь, что виджет может принимать фокус
  setStyleSheet("background-color: #efebe7;");
}

bool GameBoard::gameIsStarted() const { return isStarted; }

bool GameBoard::isPausedpush() const { return isPaused; }

void GameBoard::drawSquare(QPainter &painter, int x, int y, QColor color) {
  QRect rect(x, y, 20, 20);
  QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
  gradient.setColorAt(0, color.lighter(150));
  gradient.setColorAt(1, color.darker(150));

  painter.fillRect(rect, gradient);
  painter.drawRect(rect);
}

void GameBoard::pause() {
  if (!isStarted && gameover) return;

  isPaused = !isPaused;
  if (isPaused) {
    timer.stop();
  } else {
    timer.start(100, this);
  }
  update();
}

void GameBoard::pauseGame() {
  if (isPaused) {
    timer.start(100, this);
  } else {
    timer.stop();
  }
  isPaused = !isPaused;
}

void GameBoard::drawBackground(QPainter &painter, QColor color) {
  painter.fillRect(0, 0, width(), height(), color);
}

UserAction_t GameBoard::getUserAction(int ch) {
  switch (ch) {
    case Qt::Key_Q:
    case Qt::Key_Escape:
      return Terminate;
    case Qt::Key_Up:
      return Up;
    case Qt::Key_Down:
      return Down;
    case Qt::Key_Left:
      return Left;
    case Qt::Key_Right:
      return Right;
    case Qt::Key_P:
      return Action;
    case Qt::Key_Space:
      return Pause;
    case Qt::Key_Return:
    case Qt::Key_Enter:
      return Start;
    default:
      return Start;
  }
}

void GameBoard::initStart() {
  isStarted = true;
  isPaused = false;
  userAction = Start;
  gameState = START;
}

void GameBoard::initGameOver() {
  gameover = true;
  isStarted = false;
  emit gameOverOccurred();
}

void GameBoard::startTimer(int interval) {
  timer.stop();
  timer.start(interval, this);
}
