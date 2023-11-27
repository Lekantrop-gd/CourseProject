#ifndef CARDCREATOR_H
#define CARDCREATOR_H
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QSizePolicy>


class CardCreator
{
public:
    CardCreator();
    QWidget* getGameCard(QString image, QString title, QString description, QString price);
};

#endif // CARDCREATOR_H
