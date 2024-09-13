#include "snakewindow.h"

#include "snakeboard.h"

using namespace s21;

SnakeWindow::SnakeWindow(QWidget *parent)
    : GameWindow(parent), board(new SnakeBoard) {
  levelLabel = createValueLabel(true);  // Smaller size
  scoreLabel = createValueLabel(true);
  highScoreLabel = createValueLabel(true);

  connectButtons();
  setupLayout();  // Call the new setupLayout function

  // Подписываемся на сигнал quitGame
  connect(this, &GameWindow::quitGame, this, &SnakeWindow::onQuitGame);
}

GameBoard *SnakeWindow::getBoard() const { return board; }

void SnakeWindow::onQuitGame() {
  // Прячем текущее окно
  this->hide();
  // Создаем и показываем виджет выбора игры
  GameChooser *chooser = new GameChooser();
  chooser->show();
}
