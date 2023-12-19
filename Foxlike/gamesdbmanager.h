#ifndef GAMESDBMANAGER_H
#define GAMESDBMANAGER_H
#include "game.h"
#include <QVector>
#include <QSqlQuery>

class GamesDBManager
{
public:
    static GamesDBManager* getInstance();

    QVector<Game> getAllGames();
    QVector<Game> getGamesByKeyWords(QString keyWords);
    QVector<Game> getGamesByGenre(QString genre);
    QVector<Game> getGamesByPrice(float maximumPrice);
    Game getGameById(int id);
    QVector<QString> getAllGenres();

    bool inserGameIntoTable(const Game& game);
    void deleteGame(int gameId);

private:
    GamesDBManager() = default;

    static GamesDBManager* instance;

    QVector<Game> prepareGames(QSqlQuery query);
};

#endif // GAMESDBMANAGER_H
