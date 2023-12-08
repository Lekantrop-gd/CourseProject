#ifndef CARDCREATOR_H
#define CARDCREATOR_H
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <game.h>

class CardCreator
{
public:
    CardCreator();
    QWidget* getGameCard(Game game);
};

#endif // CARDCREATOR_H
