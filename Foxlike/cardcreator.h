#ifndef CARDCREATOR_H
#define CARDCREATOR_H
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <game.h>
#include "GameCard.h"

class CardCreator
{
public:
    CardCreator();
    GameCard* getGameCard(Game game);
};

#endif // CARDCREATOR_H
