#ifndef GAMESDBMANAGER_H
#define GAMESDBMANAGER_H
#include "mysqldbmanager.h"
#include "game.h"

class GamesDBManager : public MySQLDBManager
{
public:
    static GamesDBManager* getInstance();

    QVector<Game> getAllGames();

    bool inserGameIntoTable(const Game& game);

private:
    static GamesDBManager* instance;
};

#endif // GAMESDBMANAGER_H
