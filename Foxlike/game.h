#ifndef GAME_H
#define GAME_H
#include<QString>
#include<QVector>

class Game
{
public:
    Game(int id, const QString &title, const QString &shortDescription, const QString &fullDescription, float price, const QString &developer, const QString &publisher, const QString &releaseDate, const QString &genre, const QString &banner, const QString &image, const QString &icon);

    QString getBanner() const;

    QString getTitle() const;

    float getPrice() const;

    QString getShortDescription() const;

    QString getFullDescription() const;

    QString getImage() const;

    QString getIcon() const;

    QString getDeveloper() const;

    QString getPublisher() const;

    QString getReleaseDate() const;

    QString getGenre() const;

private:
    int id;
    QString title;
    QString shortDescription;
    QString fullDescription;
    float price;
    QString developer;
    QString publisher;
    QString releaseDate;
    QString genre;
    QString banner;
    QString image;
    QString icon;
};

#endif // GAME_H
