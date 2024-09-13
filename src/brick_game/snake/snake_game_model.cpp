#include "snake_game_model.h"

namespace s21 {

SnakeGameModel::SnakeGameModel(int width, int height) {
  srand(time(nullptr));
  initializeGameField(width, height);
}

void SnakeGameModel::initializeGameField(int width, int height) {
  width_ = width + 2;
  height_ = height + 2;
  gameInfo_.field.resize(height_, std::vector<int>(width_, 0));
  for (int x = 0; x < width_; ++x) {
    gameInfo_.field[0][x] = gameInfo_.field[height_ - 1][x] = Border;
  }
  for (int y = 0; y < height_; ++y) {
    gameInfo_.field[y][0] = gameInfo_.field[y][width_ - 1] = Border;
  }
  resetGame();
  // gameInfo_.high_score = load_high_score();
}

void SnakeGameModel::resetGame() {
  // restartGame();
  snake_.clear();
  gameInfo_.score = 0;
  gameInfo_.level = 1;
  gameInfo_.speed = 1;
  gameInfo_.high_score = load_high_score();
  gameOver_ = false;
  gameWin_ = false;
  isCollision_ = false;
  isAppleEaten_ = false;
  direction_ = Direction::Left;

  placeSnake();
  generateApple();
}

void SnakeGameModel::placeSnake() {
  int snake_y = height_ / 2;
  int snake_x = width_ / 2;
  snake_.push_back({snake_y, snake_x});  // Head
  gameInfo_.field[snake_y][snake_x] = SnakeHead;
  for (int i = 1; i <= 3; ++i) {
    snake_.push_back({snake_y, snake_x + i});  // Body segments
    gameInfo_.field[snake_y][snake_x + i] = SnakeBody;
  }
}

void SnakeGameModel::generateApple() {
  int x, y;
  int freeField = (width_ - 2) * (height_ - 2) - snake_.size();
  if (freeField > 0) {
    do {
      x = rand() % (width_ - 2) + 1;
      y = rand() % (height_ - 2) + 1;
    } while (gameInfo_.field[y][x] !=
             Field);  // Проверяем, что выбранная ячейка пуста
    gameInfo_.field[y][x] = Apple;
  } else
    gameWin_ = true;
}

void SnakeGameModel::setDirection(Direction dir) {
  if (direction_ != dir &&
      ((direction_ == Direction::Up && dir != Direction::Down) ||
       (direction_ == Direction::Down && dir != Direction::Up) ||
       (direction_ == Direction::Left && dir != Direction::Right) ||
       (direction_ == Direction::Right && dir != Direction::Left))) {
    direction_ = dir;
  }
}

void SnakeGameModel::moveSnake() {
  if (gameOver_) return;
  isAppleEaten_ = false;
  std::pair<int, int> new_head = calculateNewHead();
  // обработка столкновения
  handleCollision(new_head);
  if (gameOver_) {
    update_score();
    return;
  }
  // движение и съедение яблока
  updateGameField(new_head);
}

std::pair<int, int> SnakeGameModel::calculateNewHead() {
  auto head = snake_.front();
  switch (direction_) {
    case Direction::Up:
      head.first--;
      break;
    case Direction::Down:
      head.first++;
      break;
    case Direction::Left:
      head.second--;
      break;
    case Direction::Right:
      head.second++;
      break;
  }
  return head;
}

void SnakeGameModel::handleCollision(std::pair<int, int> new_head) {
  if (new_head.second < 1 || new_head.first < 1 ||
      new_head.second >= width_ - 1 || new_head.first >= height_ - 1 ||
      gameInfo_.field[new_head.first][new_head.second] == SnakeBody) {
    gameOver_ = true;
    isCollision_ = true;
    return;
  }
}

void SnakeGameModel::eatApple() {
  // перед генерацией нового яблока проверить на наличие пустового места
  isAppleEaten_ = true;
  // если не осталось то win
  generateApple();
  gameInfo_.score++;
  update_score();
  increaseLevel();
  if (snake_.size() >= 200) {
    gameWin_ = true;
    gameOver_ = true;
  }
}

void SnakeGameModel::updateGameField(std::pair<int, int> new_head) {
  // Обновление головы
  gameInfo_.field[snake_.front().first][snake_.front().second] = SnakeBody;
  snake_.insert(snake_.begin(), new_head);

  // змейка съедает яблоко
  if (gameInfo_.field[new_head.first][new_head.second] == Apple) {
    eatApple();
  } else {
    // Удаление хвоста
    auto tail = snake_.back();
    gameInfo_.field[tail.first][tail.second] = 0;
    snake_.pop_back();
  }
  gameInfo_.field[new_head.first][new_head.second] = SnakeHead;
}

void SnakeGameModel::increaseLevel() {
  if (gameInfo_.score % 5 == 0 && gameInfo_.score != 0 &&
      gameInfo_.level != 10) {
    gameInfo_.level++;
    gameInfo_.speed++;
  }
}

void SnakeGameModel::restartGame() {
  gameInfo_.field.clear();
  initializeGameField(width_ - 2, height_ - 2);
}

std::vector<std::vector<int>> SnakeGameModel::getField() const {
  return gameInfo_.field;
}

int SnakeGameModel::getScore() const { return gameInfo_.score; }

int SnakeGameModel::getHighScore() const { return gameInfo_.high_score; }

int SnakeGameModel::getLevel() const { return gameInfo_.level; }

bool SnakeGameModel::isGameOver() { return gameOver_; }

bool SnakeGameModel::isGameWin() { return gameWin_; }

bool SnakeGameModel::isCollision() { return isCollision_; }

bool SnakeGameModel::isAppleEaten() { return isAppleEaten_; }

bool SnakeGameModel::isMaxSizeSnake() {
  if (snake_.size() >= 200) {
    gameWin_ = true;
  }
  return gameWin_;
}

void SnakeGameModel::handleDirectionChange(UserAction_t action) {
  switch (action) {
    case Up:
      // if (!hold)
      setDirection(Direction::Up);
      break;
    case Down:
      // if (!hold)
      setDirection(Direction::Down);
      break;
    case Left:
      // if (!hold)
      setDirection(Direction::Left);
      break;
    case Right:
      // if (!hold)
      setDirection(Direction::Right);
      break;
    case Action:
      break;
    default:
      break;
  }
}

void SnakeGameModel::save_high_score(int score) {
  FILE *file = fopen(SCORE_FILE_PATH, "w");
  if (file != NULL) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

int SnakeGameModel::load_high_score() {
  int high_score = 0;
  FILE *file = fopen(SCORE_FILE_PATH, "r");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  } else {
    save_high_score(0);
  }
  return high_score;
}

void SnakeGameModel::update_score() {
  if (gameInfo_.score > gameInfo_.high_score) {
    gameInfo_.high_score = gameInfo_.score;
    save_high_score(gameInfo_.high_score);
  }
}

}  // namespace s21
