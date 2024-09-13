#include "gamechooser.h"

#include <QtWidgets>

#include "snakewindow.h"
#include "tetrixwindow.h"

GameChooser::GameChooser(QWidget *parent) : QWidget(parent) {
  setWindowTitle(tr("Brick Game"));
  setFixedSize(600, 600);                       // Set fixed window size
  setStyleSheet("background-color: #D6D1C9;");  // Set background color

  QLabel *titleLabel = new QLabel(tr("Brick Game"));
  titleLabel->setAlignment(Qt::AlignCenter);
  titleLabel->setStyleSheet(
      "font-size: 24px; font-weight: bold; color: #000000;");

  QLabel *descriptionLabel = new QLabel(tr("Choose a game to play:"));
  descriptionLabel->setAlignment(Qt::AlignCenter);
  descriptionLabel->setStyleSheet("font-size: 18px; color: #000000;");

  tetrixButton = new QPushButton(tr("Tetrix"));
  tetrixButton->setStyleSheet(
      "padding: 10px; font-size: 18px; background-color: #D3D3D3; color: "
      "#000000;");

  snakeButton = new QPushButton(tr("Snake"));
  snakeButton->setStyleSheet(
      "padding: 10px; font-size: 18px; background-color: #D3D3D3; color: "
      "#000000;");

  exitButton = new QPushButton(tr("Exit"));
  exitButton->setStyleSheet(
      "padding: 10px; font-size: 18px; background-color: #D3D3D3; color: "
      "#000000;");

  connect(tetrixButton, &QPushButton::clicked, this, &GameChooser::openTetrix);
  connect(snakeButton, &QPushButton::clicked, this, &GameChooser::openSnake);
  connect(exitButton, &QPushButton::clicked, this,
          &GameChooser::exitApplication);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSpacing(30);
  layout->addWidget(titleLabel);
  layout->addWidget(descriptionLabel);
  layout->addWidget(tetrixButton);
  layout->addWidget(snakeButton);
  layout->addWidget(exitButton);
  layout->setAlignment(Qt::AlignCenter);
  setLayout(layout);
}

void GameChooser::openTetrix() {
  s21::TetrixWindow *tetrixWindow = new s21::TetrixWindow;
  tetrixWindow->show();
  this->close();
}

void GameChooser::openSnake() {
  s21::SnakeWindow *snakeWindow = new s21::SnakeWindow;
  snakeWindow->show();
  this->close();
}

void GameChooser::exitApplication() { QApplication::quit(); }
