#ifndef GAMESDBMANAGER_H
#define GAMESDBMANAGER_H
#include "mysqldbmanager.h"
#include "game.h"
#include <QVector>
#include <QSqlQuery>

class GamesDBManager : public MySQLDBManager
{
public:
    static GamesDBManager* getInstance();

    QVector<Game> getAllGames();
    QVector<Game> getGamesByKeyWords(QString keyWords);
    QVector<Game> getGamesByGenre(QString genre);
    QVector<Game> getGamesByPrice(float maximumPrice);

    bool inserGameIntoTable(const Game& game);
    void deleteGame(int gameId);
    int getLastGameId();

private:
    static GamesDBManager* instance;

    QVector<Game> prepareGames(QSqlQuery query);
};

#endif // GAMESDBMANAGER_H
