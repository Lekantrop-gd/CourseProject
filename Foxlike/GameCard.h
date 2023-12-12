#ifndef GAMECARD_H
#define GAMECARD_H
#include <QWidget>
#include "game.h"

class GameCard : public QWidget
{
    Q_OBJECT

signals:
    void clicked();

public:
    GameCard(Game game, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Game game;
};

#endif // GAMECARD_H
