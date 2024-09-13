#include "tetrixboard.h"

using namespace s21;

TetrixBoard::TetrixBoard(QWidget *parent) : GameBoard(parent) {
  initialize_game(game_info());
}

void TetrixBoard::start() {
  if (isPaused) return;

  initStart();

  startTimer(fastInterval);
  initialize_game_start(game_info());
  updateGame(false);
}

void TetrixBoard::checkGameOver() {
  GameInfo_t *game = game_info();
  if (check_gameover(game)) initGameOver();
}

void TetrixBoard::drawNextFigure(QPainter &painter) {
  GameInfo_t *game = game_info();
  int startX = width() - 185;  // Adjust this value to align with your layout
  int startY = 450;            // This should start right under the "Next" label

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (game->next[i][j] == 1) {
        painter.setBrush(QColor("#cc6666"));
        drawSquare(painter, startX + j * 20, startY + i * 20,
                   QColor("#cc6666"));
      }
    }
  }
}

void TetrixBoard::paintEvent(QPaintEvent *event) {
  QFrame::paintEvent(event);
  QPainter painter(this);

  int boardWidth = width() / FIELD_WIDTH;
  int boardHeight = height() / FIELD_HEIGHT;
  int cellSize = qMin(boardWidth, boardHeight);

  drawBackground(painter, QColor("#efebe7"));

  GameInfo_t *game = game_info();

  QPen pen(Qt::black, 0);
  painter.setPen(pen);
  painter.drawRect(0, 0, FIELD_WIDTH * cellSize, FIELD_HEIGHT * cellSize);

  // Draw the cells
  for (int i = 0; i < FIELD_WIDTH; ++i) {
    for (int j = 0; j < FIELD_HEIGHT; ++j) {
      int x = i * cellSize;
      int y = j * cellSize;

      if (game->field[j][i] == 1) {
        painter.setBrush(QColor("#cc6666"));
        painter.drawRect(x, y, cellSize, cellSize);
      } else if (game->field[j][i] == 2) {
        painter.setBrush(QColor("#66cc66"));
        painter.drawRect(x, y, cellSize, cellSize);
      }
    }
  }

  // Draw the next figure
  drawNextFigure(painter);
}

void TetrixBoard::keyPressEvent(QKeyEvent *event) {
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
    updateGame(false);
  }
}

void TetrixBoard::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timer.timerId()) {
    userAction = Down;
    updateGame(true);
  } else {
    QFrame::timerEvent(event);
  }
}

void TetrixBoard::updateGame(bool isTimerEvent) {
  fsm(&gameState, &userAction, isTimerEvent);
  emit scoreChanged(getScore());
  emit levelChanged(getLevel());
  emit highScoreChanged(load_high_score());

  unsigned int delay = get_speed_delay(game_info());

  timer.start(delay / 1000000,
              this);  // Convert nanoseconds to milliseconds for QTimer
  update();
  if (!isTimerEvent) {
    userAction = Start;
  }
  checkGameOver();
}
