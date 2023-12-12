#include "cardcreator.h"
#include "Config.h"

CardCreator::CardCreator()
{

}

GameCard* CardCreator::getGameCard(Game game)
{
    GameCard *cardWidget = new GameCard(game);
    cardWidget->setCursor(Qt::PointingHandCursor);
    cardWidget->setMaximumSize(330, 270);

    QPixmap gameBannerResource(pathToGamesBanners + game.getBanner());
    QLabel *gameBanner = new QLabel();
    gameBanner->setPixmap(gameBannerResource.scaled(320, 180));

    QLabel *gameTitle = new QLabel(game.getTitle());
    gameTitle->setStyleSheet("color: " + mainTextColor + "; font-size: 15px");

    QLabel *gameDescription = new QLabel(game.getShortDescription());
    gameDescription->setStyleSheet("color: " + shadedTextColor + ";");

    QLabel *gamePrice = new QLabel(QString::number(game.getPrice()) + "$");
    gamePrice->setStyleSheet("color: " + mainTextColor + "; font-size: 20px");

    QGridLayout *gridLayout = new QGridLayout(cardWidget);

    gridLayout->addWidget(gameBanner, 0, 0);
    gridLayout->addWidget(gameTitle, 1, 0);
    gridLayout->addWidget(gameDescription, 2, 0);
    gridLayout->addWidget(gamePrice, 3, 0);

    cardWidget->setLayout(gridLayout);
    cardWidget->setStyleSheet("QWidget:hover { border-radius: 10%; background-color: " + selectedBackgroundColor + "; }");

    return cardWidget;
}
