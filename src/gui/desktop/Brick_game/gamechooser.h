#ifndef GAMECHOOSER_H
#define GAMECHOOSER_H

#include <QWidget>
#include <QPushButton>



class GameChooser : public QWidget
{
    Q_OBJECT

public:
    explicit GameChooser(QWidget *parent = nullptr);

private slots:
    void openTetrix();
    void openSnake();
    void exitApplication();

private:
    QPushButton *tetrixButton;
    QPushButton *snakeButton;
    QPushButton *exitButton;
};


#endif // GAMECHOOSER_H
