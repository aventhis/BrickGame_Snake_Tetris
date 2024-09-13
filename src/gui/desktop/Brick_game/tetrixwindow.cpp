#include "tetrixwindow.h"

#include "tetrixboard.h"

using namespace s21;

TetrixWindow::TetrixWindow(QWidget *parent)
    : GameWindow(parent), board(new TetrixBoard) {
  levelLabel = createValueLabel(true);  // Smaller size
  scoreLabel = createValueLabel(true);
  highScoreLabel = createValueLabel(true);

  nextPieceHeaderLabel = createHeaderLabel(tr("NEXT FIGURE"));

  connectButtons();
  setupLayout({nextPieceHeaderLabel});  // Call the new setupLayout function
                                        // with additional widget

  // Подписываемся на сигнал quitGame
  connect(this, &GameWindow::quitGame, this, &TetrixWindow::onQuitGame);
}

GameBoard *TetrixWindow::getBoard() const { return board; }

void TetrixWindow::onQuitGame() {
  // Прячем текущее окно
  this->hide();
  // Создаем и показываем виджет выбора игры
  GameChooser *chooser = new GameChooser();
  chooser->show();
}
