#ifndef NEXTPIECEDISPLAY_H
#define NEXTPIECEDISPLAY_H

#include <QWidget>
#include <QPainter>

class NextPieceDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit NextPieceDisplay(QWidget *parent = nullptr);

    void setNextPiece(int piece[4][4]);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int nextPiece[4][4] = {{0}};
    void drawNextFigure(QPainter &painter);
};

#endif // NEXTPIECEDISPLAY_H
