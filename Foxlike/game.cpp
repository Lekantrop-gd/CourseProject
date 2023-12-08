#include "game.h"

QString Game::getBanner() const
{
    return banner;
}

QString Game::getTitle() const
{
    return title;
}

float Game::getPrice() const
{
    return price;
}

QString Game::getShortDescription() const
{
    return shortDescription;
}

QString Game::getFullDescription() const
{
    return fullDescription;
}

QString Game::getImage() const
{
    return image;
}

QString Game::getIcon() const
{
    return icon;
}

QString Game::getDeveloper() const
{
    return developer;
}

QString Game::getPublisher() const
{
    return publisher;
}

QString Game::getReleaseDate() const
{
    return releaseDate;
}

QString Game::getGenre() const
{
    return genre;
}

Game::Game(int id, const QString &title, const QString &shortDescription, const QString &fullDescription, float price, const QString &developer, const QString &publisher, const QString &releaseDate, const QString &genre, const QString &banner, const QString &image, const QString &icon) : id(id),
    title(title),
    shortDescription(shortDescription),
    fullDescription(fullDescription),
    price(price),
    developer(developer),
    publisher(publisher),
    releaseDate(releaseDate),
    genre(genre),
    banner(banner),
    image(image),
    icon(icon)
{}
