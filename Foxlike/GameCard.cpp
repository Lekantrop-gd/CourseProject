#include "GameCard.h"
#include <QMouseEvent>

GameCard::GameCard(Game game, QWidget *parent) : QWidget(parent), game(game)
{

}

void GameCard::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit clicked();
}
