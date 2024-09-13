#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

namespace s21 {

class GameBoard;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

    QLabel *createHeaderLabel(const QString &text);
    QLabel *createValueLabel(bool small);
    void updateScoreLabel(int score);
    void updateLevelLabel(int level);
    void updateHighScoreLabel(int highScore);

protected:
    virtual GameBoard* getBoard() const = 0;
    void connectButtons();
    void setupLayout(const std::vector<QWidget*>& additionalWidgets = {}); // New function to setup layout

    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *highScoreLabel;
    QLabel *pauseLabel;
    QLabel *gameOverLabel;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *quitButton;
    QGridLayout *mainLayout; // Main layout for the window

signals:
    void quitGame();  // Сигнал для выхода из игры
};

}

#endif // GAMEWINDOW_H
