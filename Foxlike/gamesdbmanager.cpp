#include "gamesdbmanager.h"
#include "purchasedgamesdbmanager.h"
#include "qsqlerror.h"
#include "Config.h"
#include <QDebug>
#include <QSqlQuery>
#include <QFile>

GamesDBManager* GamesDBManager::instance = nullptr;

GamesDBManager* GamesDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new GamesDBManager();
    }
    return instance;
}

bool GamesDBManager::inserGameIntoTable(const Game& game) {
    QSqlQuery query;
    bool genreExists = false;

    query.exec("SELECT genre FROM Genres");
    while (query.next()) {
        if (query.value(0) == game.getGenre()) {
            genreExists = true;
        }
    }

    if (!genreExists) {
        query.prepare("INSERT INTO Genres(genre) VALUES(:genre)");
        query.bindValue(":genre", game.getGenre());

        if (!query.exec()) {
            qDebug() << query.lastError().text();
            return false;
        }
    }

    query.prepare("INSERT INTO Games("
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
                  ":title, "
                  ":shortDescription, "
                  ":fullDescription, "
                  ":price, "
                  ":developer, "
                  ":publisher, "
                  ":releaseDate, "
                  "(SELECT genreId FROM Genres WHERE genre = :genre), "
                  ":banner, "
                  ":image, "
                  ":icon)");

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

bool GamesDBManager::deleteGame(int gameId)
{
    PurchasedGamesDBManager *purchaseDBManager = PurchasedGamesDBManager::getInstance();

    QSqlQuery query;

    Game game = getGameById(gameId);

    query.exec("SET foreign_key_checks = 0");

    query.prepare("DELETE FROM Games WHERE id = :id");
    query.bindValue(":id", gameId);

    if (!purchaseDBManager->deletePurchaseByGameId(gameId) || !query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    QFile::remove(pathToGamesImages + game.getBanner());
    QFile::remove(pathToGamesImages + game.getImage());
    QFile::remove(pathToGamesImages + game.getIcon());

    query.exec("SET foreign_key_checks = 1");

    return true;
}

QVector<Game> GamesDBManager::prepareGames(QSqlQuery query)
{
    QVector<Game> games;

    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }
    else {
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
    }

    return games;
}

QVector<Game> GamesDBManager::getAllGames()
{
    QSqlQuery query;

    query.exec("SELECT * FROM GAMES WHERE status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByKeyWords(QString keyWords)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE title LIKE :keyWords OR shortDescription LIKE :keyWords OR fullDescription LIKE :keyWords AND status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");
    query.bindValue(":keyWords", "%" + keyWords + "%");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByGenre(QString genre)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE genre = (SELECT genreId FROM GENRES WHERE genre LIKE :genre) AND status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");
    query.bindValue(":genre", "%" + genre + "%");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByPrice(float maximumPrice)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE price < :price AND status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");
    query.bindValue(":price", maximumPrice);

    return prepareGames(std::move(query));
}

Game GamesDBManager::getGameById(int id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM Games WHERE id = :id AND status = (SELECT statusId FROM Statuses WHERE status = 'confirmed')");
    query.bindValue(":id", id);

    QVector<Game> games = prepareGames(std::move(query));

    if (games.size() != 0)
        return games[0];
}

QVector<QString> GamesDBManager::getAllGenres()
{
    QSqlQuery query;
    QVector<QString> genres;

    if (query.exec("SELECT genre FROM Genres")) {
        while (query.next()) {
            genres.append(query.value(0).toString());
        }
    }
    else {
        query.lastError();
    }

    return genres;
}
