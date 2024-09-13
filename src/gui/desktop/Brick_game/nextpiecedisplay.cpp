#include "nextpiecedisplay.h"

NextPieceDisplay::NextPieceDisplay(QWidget *parent) : QWidget(parent) {
  setFixedSize(100, 100);  // Adjust size accordingly
}

void NextPieceDisplay::setNextPiece(int piece[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      nextPiece[i][j] = piece[i][j];
    }
  }
  update();  // Trigger a repaint
}

void NextPieceDisplay::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  drawNextFigure(painter);
}

void NextPieceDisplay::drawNextFigure(QPainter &painter) {
  int blockSize = 20;  // Size of each block

  // Calculate the top left position to center the 4x4 next piece grid
  int startX = (width() - 4 * blockSize) / 2;
  int startY = (height() - 4 * blockSize) / 2;

  painter.fillRect(rect(),
                   QColor("#ffffff"));  // Fill the background with white

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (nextPiece[i][j] == 1) {
        QRect rect(startX + j * blockSize, startY + i * blockSize, blockSize,
                   blockSize);
        painter.setBrush(QColor("#cc6666"));
        painter.drawRect(rect);
      }
    }
  }
}
