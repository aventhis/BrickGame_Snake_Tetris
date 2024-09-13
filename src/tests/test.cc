#include <gtest/gtest.h>
#include "../brick_game/snake/snake_game_model.h"

namespace s21 {

class SnakeGameModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = new SnakeGameModel(10, 20);
        model->resetGame();
    }

    void TearDown() override {
        delete model;
    }

    SnakeGameModel* model;
};

// Test for initialization
TEST_F(SnakeGameModelTest, InitializeGameField) {
    EXPECT_EQ(model->getField().size(), static_cast<size_t>(22)); // height + 2
    EXPECT_EQ(model->getField()[0].size(), static_cast<size_t>(12)); // width + 2
}

// Test for resetting the game
TEST_F(SnakeGameModelTest, ResetGame) {
    model->resetGame();
    EXPECT_EQ(model->getScore(), 0);
    EXPECT_EQ(model->getLevel(), 1);
    EXPECT_EQ(model->getField()[11][6], SnakeHead); // check if snake head is placed correctly
    EXPECT_EQ(model->getField()[11][7], SnakeBody); // check if snake body is placed correctly
    EXPECT_EQ(model->getField()[11][8], SnakeBody); // check if snake body is placed correctly
    EXPECT_EQ(model->getField()[11][9], SnakeBody); // check if snake body is placed correctly
}

// Test for placing snake
TEST_F(SnakeGameModelTest, PlaceSnake) {
    model->resetGame();
    auto field = model->getField();
    EXPECT_EQ(field[11][6], SnakeHead);
    EXPECT_EQ(field[11][7], SnakeBody);
    EXPECT_EQ(field[11][8], SnakeBody);
    EXPECT_EQ(field[11][9], SnakeBody);
}

// Test for generating apple
TEST_F(SnakeGameModelTest, GenerateApple) {
    model->resetGame();
    bool appleGenerated = false;
    auto field = model->getField();
    for (int y = 1; y < 21; ++y) {
        for (int x = 1; x < 11; ++x) {
            if (field[y][x] == Apple) {
                appleGenerated = true;
                break;
            }
        }
        if (appleGenerated) break;
    }
    EXPECT_TRUE(appleGenerated);
}


// // Test for moving snake
// TEST_F(SnakeGameModelTest, MoveSnake) {
//     model->resetGame();
//     model->setDirection(Direction::Right);
//     model->moveSnake();
//     auto field = model->getField();
//     EXPECT_EQ(field[11][6], SnakeBody); // old head becomes body
//     EXPECT_EQ(field[11][7], SnakeBody);
//     EXPECT_EQ(field[11][8], SnakeBody);
//     EXPECT_EQ(field[11][9], SnakeBody);
//     EXPECT_EQ(field[11][10], SnakeHead); // new head
// }

// Test for handling collision with walls
TEST_F(SnakeGameModelTest, CollisionWithWall) {
    model->resetGame();
    model->setDirection(Direction::Up);
    for (int i = 0; i < 11; ++i) {
        model->moveSnake();
    }
    EXPECT_TRUE(model->isCollision());
    EXPECT_TRUE(model->isGameOver());
}

// Test for eating apple
TEST_F(SnakeGameModelTest, EatApple) {
    model->resetGame();
    auto field = model->getField();
    for (int y = 1; y < 21; ++y) {
        for (int x = 1; x < 11; ++x) {
            if (field[y][x] == Apple) {
                field[y][x] = SnakeHead;
                model->eatApple();
                EXPECT_EQ(model->getScore(), 1);
                EXPECT_TRUE(model->isAppleEaten());
                return;
            }
        }
    }
}

// Test for increasing level
TEST_F(SnakeGameModelTest, IncreaseLevel) {
    model->resetGame();
    for (int i = 0; i < 5; ++i) {
        model->eatApple();
    }
    EXPECT_EQ(model->getLevel(), 2);
    EXPECT_EQ(model->getScore(), 5);
}

// Test for snake collision with itself
TEST_F(SnakeGameModelTest, SnakeCollisionWithItself) {
    model->resetGame();
    model->setDirection(Direction::Right);
    for (int i = 0; i < 3; ++i) {
        model->moveSnake();
    }
    model->setDirection(Direction::Down);
    model->moveSnake();
    model->setDirection(Direction::Left);
    for (int i = 0; i < 3; ++i) {
        model->moveSnake();
    }
    EXPECT_TRUE(model->isCollision());
    EXPECT_TRUE(model->isGameOver());
}

}  // namespace s21

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
