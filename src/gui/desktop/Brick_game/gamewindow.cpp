#include "gamewindow.h"

#include <QtWidgets>

#include "gameboard.h"

namespace s21 {

GameWindow::GameWindow(QWidget *parent) : QWidget{parent} {
  setStyleSheet("background-color: #efebe7; color: black;");

  // Buttons
  startButton = new QPushButton(tr("START"));
  quitButton = new QPushButton(tr("QUIT"));
  pauseButton = new QPushButton(tr("PAUSE"));
  pauseButton->setEnabled(false);  // Initially disable the pause button

  // Create pause label and hide it initially
  pauseLabel = new QLabel(tr("PAUSE"));
  pauseLabel->setAlignment(Qt::AlignCenter);
  pauseLabel->setStyleSheet(
      "font-size: 32px; font-weight: bold ; color: #cc6666;");
  pauseLabel->setVisible(false);

  // Create game over label and hide it initially
  gameOverLabel = new QLabel(tr("GAME OVER"));
  gameOverLabel->setAlignment(Qt::AlignCenter);
  gameOverLabel->setStyleSheet(
      "font-size: 32px; font-weight: bold; color: #cc6666;");
  gameOverLabel->setVisible(false);

  mainLayout = new QGridLayout(this);
  resize(600, 600);  // Adjust size as needed
}

QLabel *GameWindow::createHeaderLabel(const QString &text) {
  QLabel *label = new QLabel(text);
  label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
  label->setStyleSheet("font-size: 18px; font-weight: bold; color: #534d48;");
  return label;
}

void GameWindow::updateScoreLabel(int score) {
  scoreLabel->setText(QString::number(score));
}

void GameWindow::updateLevelLabel(int level) {
  levelLabel->setText(QString::number(level));
}

void GameWindow::updateHighScoreLabel(int highScore) {
  highScoreLabel->setText(QString::number(highScore));
}

QLabel *GameWindow::createValueLabel(bool small) {
  QLabel *label = new QLabel("0");  // Default value
  label->setAlignment(Qt::AlignCenter);
  if (small) {
    label->setMinimumSize(50, 20);  // Smaller size for values
    label->setStyleSheet(
        "font-size: 14px; color: black; background-color: white; border: 0.5px "
        "solid grey;");
  } else {
    label->setMinimumSize(80, 30);  // Standard size
    label->setStyleSheet(
        "font-size: 18px; color: black; background-color: white; border: 0.5px "
        "solid grey;");
  }
  return label;
}

void GameWindow::connectButtons() {
  connect(startButton, &QPushButton::clicked, this, [this]() {
    getBoard()->start();
    pauseButton->setEnabled(
        true);  // Enable the pause button when the game starts
    gameOverLabel->setVisible(false);  // Hide game over label when game starts
  });

  connect(quitButton, &QPushButton::clicked, this, [this]() {
    emit quitGame();  // Отправляем сигнал, вместо выхода из приложения
  });

  connect(pauseButton, &QPushButton::clicked, this, [this]() {
    if (getBoard()->gameIsStarted()) {
      if (getBoard()->isPausedpush()) {
        getBoard()->pause();
        pauseButton->setText(tr("PAUSE"));
        pauseLabel->setVisible(false);
      } else {
        getBoard()->pause();
        pauseButton->setText(tr("RESUME"));
        pauseLabel->setVisible(true);
      }
    }
  });

  // Connect signals for updating the UI based on game changes
  connect(getBoard(), &GameBoard::scoreChanged, this,
          &GameWindow::updateScoreLabel);
  connect(getBoard(), &GameBoard::levelChanged, this,
          &GameWindow::updateLevelLabel);
  connect(getBoard(), &GameBoard::highScoreChanged, this,
          &GameWindow::updateHighScoreLabel);
  connect(getBoard(), &GameBoard::gameOverOccurred, this, [this]() {
    gameOverLabel->setVisible(true);
    pauseButton->setEnabled(
        false);  // Disable the pause button when the game is over
  });
}

void GameWindow::setupLayout(const std::vector<QWidget *> &additionalWidgets) {
  // Derived classes should create specific labels and pass them to this
  // function
  mainLayout->addWidget(getBoard(), 0, 0, 10,
                        0);  // Game board spans most of the window

  // Configure right panel for labels
  mainLayout->addWidget(createHeaderLabel(tr("LEVEL")), 0, 1);
  mainLayout->addWidget(levelLabel, 1, 1);
  mainLayout->addWidget(createHeaderLabel(tr("SCORE")), 2, 1);
  mainLayout->addWidget(scoreLabel, 3, 1);
  mainLayout->addWidget(createHeaderLabel(tr("HIGH SCORE")), 4, 1);
  mainLayout->addWidget(highScoreLabel, 5, 1);

  // Add any additional widgets
  int row = 6;
  for (auto widget : additionalWidgets) {
    mainLayout->addWidget(widget, row++, 1);
  }

  // Configure bottom panel for buttons
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(startButton);
  buttonLayout->addWidget(pauseButton);
  buttonLayout->addWidget(quitButton);
  mainLayout->addLayout(buttonLayout, 10, 0, 1, 2);  // Span across two columns

  mainLayout->addWidget(pauseLabel, 4, 0, 2, 2);
  mainLayout->addWidget(gameOverLabel, 4, 0, 2, 2);
}

}  // namespace s21
