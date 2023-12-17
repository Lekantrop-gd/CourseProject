#include "purchasedgamesdbmanager.h"
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
    QVector<Game> games;

    query.prepare("SELECT gameId FROM PurchasedGames WHERE userId = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
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
