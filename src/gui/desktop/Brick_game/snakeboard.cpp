#include "snakeboard.h"

using namespace s21;

SnakeBoard::SnakeBoard(QWidget *parent)
    : GameBoard(parent), isMoving(false), model_(10, 20) {}

void SnakeBoard::start() {
  if (isPaused) return;

  initStart();

  model_.restartGame();
  updateTimerInterval();
  updateGame(false);
}

void SnakeBoard::checkGameOver() {
  if (model_.isCollision()) initGameOver();
}

void SnakeBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent(event);
  QPainter painter(this);

  int boardWidth = width() / model_.getField()[0].size();
  int boardHeight = height() / model_.getField().size();
  int cellSize = qMin(boardWidth, boardHeight);

  drawBackground(painter, QColor("#efebe7"));

  const auto &field = model_.getField();
  for (int y = 0; y < field.size(); ++y) {
    for (int x = 0; x < field[y].size(); ++x) {
      int drawX = x * cellSize;
      int drawY = y * cellSize;
      //            || field[y][x] == s21::SnakeBody BDECB6 cc6666 красный
      if (field[y][x] == SnakeHead) {
        drawSquare(painter, drawX, drawY, QColor("#4CAF50"));
      } else if (field[y][x] == SnakeBody) {
        drawSquare(painter, drawX, drawY, QColor("#8BC34A"));
      }

      else if (field[y][x] == Apple) {
        drawSquare(painter, drawX, drawY, QColor("#FF5722"));
      } else if (field[y][x] == Border) {  // #808080
        drawSquare(painter, drawX, drawY, QColor("#FFFFFF"));
      }
    }
  }
}

void SnakeBoard::keyPressEvent(QKeyEvent *event) {
  if (!isStarted || isPaused || event->isAutoRepeat()) {
    QFrame::keyPressEvent(event);
    return;
  }

  UserAction_t action = getUserAction(event->key());
  if (action == Terminate) {
    QApplication::quit();
  } else if (action == Pause) {
    pauseGame();
  } else {
    userAction = action;
    isMoving = true;
    startTimer(fastInterval);
    updateGame(false);
  }
}

void SnakeBoard::keyReleaseEvent(QKeyEvent *event) {
  if (event->isAutoRepeat()) {
    QFrame::keyReleaseEvent(event);
    return;
  }

  if (getUserAction(event->key()) == userAction) {
    isMoving = false;
    updateTimerInterval();
  }
}

void SnakeBoard::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timer.timerId()) {
    updateGame(true);
  } else {
    QFrame::timerEvent(event);
  }
}

void SnakeBoard::updateGame(bool isTimerEvent) {
  model_.fsm_snake(gameState, userAction, isTimerEvent);
  emit scoreChanged(model_.getScore());
  emit levelChanged(model_.getLevel());
  emit highScoreChanged(model_.getHighScore());

  update();
  if (!isTimerEvent && !isMoving) {
    userAction = Start;
  }
  checkGameOver();
}

void SnakeBoard::updateTimerInterval() {
  int levelBasedInterval =
      normalInterval /
      std::pow(1.2, model_.getLevel());  // Ускорение на 20% за уровень
  if (levelBasedInterval < fastInterval) {
    levelBasedInterval = fastInterval;  // Убедимся, что не опускаемся ниже
                                        // минимального интервала
  }
  startTimer(levelBasedInterval);
}
