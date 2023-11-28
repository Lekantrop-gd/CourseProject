#include "cardcreator.h"

CardCreator::CardCreator()
{

}

QWidget* CardCreator::getGameCard(QString image, QString title, QString description, QString price)
{
    QWidget *cardWidget = new QWidget();
    cardWidget->setCursor(Qt::PointingHandCursor);
    cardWidget->setMaximumSize(320, 240);

    QPixmap gameImageResource(image);
    QLabel *gameImage = new QLabel();
    gameImage->setPixmap(gameImageResource.scaled(320, 180));

    QLabel *gameTitle = new QLabel(title);
    gameTitle->setStyleSheet("color: rgb(200, 200, 200); font-size: 15px");

    QLabel *gameDescription = new QLabel(description);
    gameDescription->setStyleSheet("color: rgb(150, 150, 150)");

    QLabel *gamePrice = new QLabel(price);
    gamePrice->setStyleSheet("color: rgb(200, 200, 200); font-size: 20px");

    QGridLayout *gridLayout = new QGridLayout(cardWidget);

    gridLayout->addWidget(gameImage, 0, 0);
    gridLayout->addWidget(gameTitle, 1, 0);
    gridLayout->addWidget(gameDescription, 2, 0);
    gridLayout->addWidget(gamePrice, 3, 0);

    cardWidget->setLayout(gridLayout);

    return cardWidget;
}
