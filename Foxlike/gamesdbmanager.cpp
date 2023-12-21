#include "gamesdbmanager.h"
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
                  ":genre, "
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
    QSqlQuery query;

    query.prepare("DELETE FROM Games WHERE id = :id");
    query.bindValue(":id", gameId);

    Game game = getGameById(gameId);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    QFile::remove(pathToGamesImages + game.getBanner());
    QFile::remove(pathToGamesImages + game.getImage());
    QFile::remove(pathToGamesImages + game.getIcon());
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

    query.exec("SELECT * FROM GAMES WHERE status = 'confirmed'");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByKeyWords(QString keyWords)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE title LIKE :keyWords OR shortDescription LIKE :keyWords OR fullDescription LIKE :keyWords AND status = 'confirmed'");
    query.bindValue(":keyWords", "%" + keyWords + "%");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByGenre(QString genre)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE genre LIKE :genre AND status = 'confirmed'");
    query.bindValue(":genre", "%" + genre + "%");

    return prepareGames(std::move(query));
}

QVector<Game> GamesDBManager::getGamesByPrice(float maximumPrice)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE price < :price AND status = 'confirmed'");
    query.bindValue(":price", maximumPrice);

    return prepareGames(std::move(query));
}

Game GamesDBManager::getGameById(int id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM Games WHERE id = :id AND status = 'confirmed'");
    query.bindValue(":id", id);

    QVector<Game> games = prepareGames(std::move(query));

    if (games.size() != 0)
        return games[0];
}

QVector<QString> GamesDBManager::getAllGenres()
{
    QSqlQuery query;
    QVector<QString> genres;

    if (query.exec("SELECT DISTINCT genre FROM Games")) {
        while (query.next()) {
            genres.append(query.value(0).toString());
        }
    }
    else {
        query.lastError();
    }

    return genres;
}
