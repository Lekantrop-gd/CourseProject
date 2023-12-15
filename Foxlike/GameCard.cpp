#include "GameCard.h"
#include "Config.h"
#include <QMouseEvent>
#include <QLabel>
#include <QGridLayout>

GameCard::GameCard(Game game, QWidget *parent) : QWidget(parent), game(game)
{
    this->setCursor(Qt::PointingHandCursor);
    this->setMaximumSize(sizeOfGameCard[0], sizeOfGameCard[1]);

    QPixmap gameBannerResource(pathToGamesBanners + game.getBanner());
    QLabel *gameBanner = new QLabel();
    gameBanner->setPixmap(gameBannerResource.scaled(320, 180));

    QLabel *gameTitle = new QLabel(game.getTitle());
    gameTitle->setStyleSheet("color: " + mainTextColor + "; font-size: 15px");

    QLabel *gameDescription = new QLabel(game.getShortDescription());
    gameDescription->setStyleSheet("color: " + shadedTextColor + ";");

    QLabel *gamePrice = new QLabel(QString::number(game.getPrice(), 'f', 2) + "$");
    gamePrice->setStyleSheet("color: " + mainTextColor + "; font-size: 20px");

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(gameBanner, 0, 0);
    gridLayout->addWidget(gameTitle, 1, 0);
    gridLayout->addWidget(gameDescription, 2, 0);
    gridLayout->addWidget(gamePrice, 3, 0);

    this->setLayout(gridLayout);
}

void GameCard::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit clicked(this->game);
}
