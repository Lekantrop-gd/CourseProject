#include "cardcreator.h"
#include "Config.h"

CardCreator::CardCreator()
{

}

QWidget* CardCreator::getGameCard(QString pathToImage, QString title, QString description, QString price)
{
    QWidget *cardWidget = new QWidget();
    cardWidget->setCursor(Qt::PointingHandCursor);
    cardWidget->setMaximumSize(330, 270);

    QPixmap gameImageResource(pathToImage);
    QLabel *gameImage = new QLabel();
    gameImage->setPixmap(gameImageResource.scaled(320, 180));

    QLabel *gameTitle = new QLabel(title);
    gameTitle->setStyleSheet("color: " + mainTextColor + "; font-size: 15px");

    QLabel *gameDescription = new QLabel(description);
    gameDescription->setStyleSheet("color: " + shadedTextColor + ";");

    QLabel *gamePrice = new QLabel(price);
    gamePrice->setStyleSheet("color: " + mainTextColor + "; font-size: 20px");

    QGridLayout *gridLayout = new QGridLayout(cardWidget);

    gridLayout->addWidget(gameImage, 0, 0);
    gridLayout->addWidget(gameTitle, 1, 0);
    gridLayout->addWidget(gameDescription, 2, 0);
    gridLayout->addWidget(gamePrice, 3, 0);

    cardWidget->setLayout(gridLayout);
    cardWidget->setStyleSheet("QWidget:hover { border-radius: 10%; background-color: " + selectedBackgroundColor + "; }");

    return cardWidget;
}
