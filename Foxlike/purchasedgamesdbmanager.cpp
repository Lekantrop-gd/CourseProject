#include "purchasedgamesdbmanager.h"
#include "gamesdbmanager.h"
#include <QSqlQuery>

PurchasedGamesDBManager* PurchasedGamesDBManager::instance = nullptr;

PurchasedGamesDBManager* PurchasedGamesDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new PurchasedGamesDBManager();
    }
    return instance;
}

QVector<Game> PurchasedGamesDBManager::getGamesOfUserById(int id)
{
    QSqlQuery query;
    GamesDBManager *gamesDBManager = GamesDBManager::getInstance();
    QVector<Game> games;

    query.prepare("SELECT gameId FROM PurchasedGames WHERE userId = :id AND status = 'confirmed'");
    query.bindValue(":id", id);

    if (query.exec()) {
        while (query.next()) {
            games.push_back(gamesDBManager->getGameById(query.value(0).toInt()));
        }
    }

    return games;
}
