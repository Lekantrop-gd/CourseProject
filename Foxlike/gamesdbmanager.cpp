#include "gamesdbmanager.h"
#include "qsqlerror.h"
#include <QDebug>
#include <QSqlQuery>

GamesDBManager* GamesDBManager::instance = nullptr;

GamesDBManager* GamesDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new GamesDBManager();
    }
    return instance;
}

bool GamesDBManager::inserGameIntoTable(const Game& game) {
    QSqlQuery query;
    query.prepare("INSERT INTO Games("
                  "id, "
                  "title, "
                  "shortDescription, "
                  "fullDescription, "
                  "price, "
                  "developer, "
                  "publisher, "
                  "releaseDate, "
                  "genre, "
                  "banner, "
                  "image, "
                  "icon) "
                  ""
                  "VALUES("
                  ":id, "
                  ":title, "
                  ":shortDescription, "
                  ":fullDescription, "
                  ":price, "
                  ":developer, "
                  ":publisher, "
                  ":releaseDate, "
                  ":genre, "
                  ":banner, "
                  ":image, "
                  ":icon)");

    query.bindValue(":id", 0);
    query.bindValue(":title", game.getTitle());
    query.bindValue(":shortDescription", game.getShortDescription());
    query.bindValue(":fullDescription", game.getFullDescription());
    query.bindValue(":price", game.getPrice());
    query.bindValue(":developer", game.getDeveloper());
    query.bindValue(":publisher", game.getPublisher());
    query.bindValue(":releaseDate", game.getReleaseDate());
    query.bindValue(":genre", game.getGenre());
    query.bindValue(":banner", game.getBanner());
    query.bindValue(":image", game.getImage());
    query.bindValue(":icon", game.getIcon());

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
}

QVector<Game> GamesDBManager::getAllGames()
{
    QSqlQuery query;

    QVector<Game> games;

    query.prepare("SELECT * FROM GAMES");

    while (query.next()) {
        Game game(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toFloat(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString(),
            query.value(11).toString()
            );

        games.push_back(game);
    }

    return games;
}

QVector<Game> GamesDBManager::getGames(QString keyWords)
{
    QSqlQuery query;

    QVector<Game> games;

    query.prepare("SELECT * FROM GAMES WHERE (title LIKE :keyWords OR shortDescription LIKE :keyWords OR fullDescription LIKE :keyWords)");
    query.bindValue(":keyWords", "%" + keyWords + "%");

    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }

    while (query.next()) {
        Game game(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toFloat(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString(),
            query.value(11).toString()
            );

        games.push_back(game);
    }

    return games;
}

QVector<Game> GamesDBManager::getGameByPriceLoweThan(int price)
{
    QSqlQuery query;

    QVector<Game> games;

    query.prepare("SELECT * FROM GAMES WHERE (price < :price)");
    query.bindValue(":price", "%" + QString::number(price) + "%");

    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }

    while (query.next()) {
        Game game(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toFloat(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toString(),
            query.value(11).toString()
            );

        games.push_back(game);
    }

    return games;
}

Game GamesDBManager::getGame(int id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }

    Game game(
        query.value(0).toInt(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toString(),
        query.value(4).toFloat(),
        query.value(5).toString(),
        query.value(6).toString(),
        query.value(7).toString(),
        query.value(8).toString(),
        query.value(9).toString(),
        query.value(10).toString(),
        query.value(11).toString()
        );

    return game;
}
